#include <tgbotxx/Api.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
#include <utility>
using namespace tgbotxx;

Api::Api(const std::string& token) : m_token(token) {}

nl::json Api::sendRequest(const std::string& endpoint, const cpr::Multipart& data) const {
  cpr::Session session{}; // Note: Why not have one session as a class member to use for all requests ?
                          // You can initiate multiple concurrent requests to the Telegram API, which means
                          // You can call sendMessage while getUpdates long polling is still pending, and you can't do that with a single cpr::Session instance.
  bool hasFiles = std::any_of(data.parts.begin(), data.parts.end(), [](const cpr::Part& part) noexcept { return part.is_file; });
  if (hasFiles) // Files can take longer to upload
    session.SetTimeout(FILES_UPLOAD_TIMEOUT);
  else
    session.SetTimeout(TIMEOUT);
  session.SetConnectTimeout(CONNECT_TIMEOUT);
  session.SetHeader(cpr::Header{
    {"Connection", "close"}, // disable keep-alive
    {"Accept", "application/json"},
    {"User-Agent", "tgbotxx/" TGBOTXX_VERSION},
    {"Content-Type", "application/x-www-form-urlencoded"},
  });
  std::ostringstream url{};
  url << BASE_URL << "/bot" << m_token << '/' << endpoint; // Note: token should have a prefix botTOKEN.
  session.SetUrl(cpr::Url{url.str()});
  bool isMultipart = not data.parts.empty();
  if (isMultipart) {
    session.SetMultipart(data);
    session.UpdateHeader(cpr::Header{{{"Content-Type", "multipart/form-data"}}});
  }

  cpr::Response res = isMultipart ? session.Post() : session.Get();
  if (res.status_code == 0) [[unlikely]] {
    throw Exception(endpoint + ": Failed to connect to Telegram API with status code: 0. Perhaps you are not connected to the internet?");
  }
  if (!res.text.compare(0, 6, "<html>")) [[unlikely]] {
    throw Exception(endpoint + ": Failed to get a JSON response from Telegram API. Did you enter the correct bot token?");
  }

  try {
    nl::json response = nl::json::parse(res.text);
    if (response["ok"].get<bool>()) {
      return response["result"];
    } else {
      std::string desc = response["description"];
      if (response["error_code"] == cpr::status::HTTP_NOT_FOUND) {
        desc += ". Did you enter the correct bot token?";
      }
      throw Exception(desc);
    }
  } catch (const nl::json::exception& e) {
    throw Exception(endpoint + ": Failed to parse JSON response: " + res.text + "\nreason: " + e.what());
  } catch (const Exception&) {
    std::rethrow_exception(std::current_exception()); // rethrow e
  } catch (const std::exception&) {
    std::rethrow_exception(std::current_exception()); // rethrow e
  }
}

Ptr<User> Api::getMe() const {
  nl::json json = sendRequest("getMe");
  Ptr<User> me(new User(json));
  return me;
}

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  cpr::Multipart data{};
  if (dropPendingUpdates)
    data.parts.emplace_back("drop_pending_updates", dropPendingUpdates);
  return sendRequest("deleteWebhook", data);
}

/// Called every LONG_POOL_TIMEOUT seconds
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, std::int32_t timeout,
                                         const std::vector<std::string>& allowedUpdates) const {
  cpr::Multipart data = {
    {"offset", offset},
    {"limit", std::max<std::int32_t>(1, std::min<std::int32_t>(100, limit))},
    {"timeout", timeout},
    {"allowed_updates", nl::json(allowedUpdates).dump()},
  };
  nl::json updatesJson = sendRequest("getUpdates", data);
  std::vector<Ptr<Update>> updates;
  updates.reserve(updatesJson.size());
  for (const nl::json& updateObj: updatesJson) {
    Ptr<Update> update(new Update(updateObj));
    updates.push_back(std::move(update));
  }
  return updates;
}

bool Api::setMyCommands(const std::vector<Ptr<BotCommand>>& commands,
                        const Ptr<BotCommandScope>& scope,
                        const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(3);

  nl::json commandsJson = nl::json::array();
  for (const Ptr<BotCommand>& command: commands)
    commandsJson.push_back(command->toJson());
  data.parts.emplace_back("commands", commandsJson.dump());
  if (scope) {
    data.parts.emplace_back("scope", scope->toJson().dump());
  }
  if (not languageCode.empty()) {
    data.parts.emplace_back("language_code", languageCode);
  }

  return sendRequest("setMyCommands", data);
}

std::vector<Ptr<BotCommand>> Api::getMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  std::vector<Ptr<BotCommand>> commands;
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (scope)
    data.parts.emplace_back("scope", scope->toJson().dump());
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);

  nl::json commandsJson = sendRequest("getMyCommands", data);
  if (commandsJson.empty()) return commands;
  commands.reserve(commandsJson.size());
  for (const nl::json& commandObj: commandsJson) {
    Ptr<BotCommand> cmd(new BotCommand(commandObj));
    commands.push_back(std::move(cmd));
  }
  return commands;
}

bool Api::logOut() const {
  return sendRequest("logOut");
}

bool Api::close() const {
  return sendRequest("close");
}

Ptr<Message> Api::sendMessage(std::int64_t chatId, const std::string& text, std::int32_t messageThreadId,
                              const std::string& parseMode, const std::vector<Ptr<MessageEntity>>& entities,
                              bool disableWebPagePreview, bool disableNotification, bool protectContent,
                              std::int32_t replyToMessageId, bool allowSendingWithoutReply,
                              const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("chat_id", std::to_string(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("text", text);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not entities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: entities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("entities", entitiesArray.dump());
  }
  if (disableWebPagePreview)
    data.parts.emplace_back("disable_web_page_preview", disableWebPagePreview);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendMessage", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<MessageId> Api::copyMessage(std::int64_t chatId, std::int64_t fromChatId, std::int32_t messageId,
                                std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification,
                                bool protectContent, std::int32_t replyToMessageId, bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {

  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", std::to_string(chatId));          // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", std::to_string(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit fromChatId to 32bit integer gets overflown and sends wrong fromChatId which causes Bad Request: chat not found
  data.parts.emplace_back("message_id", messageId);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json msgIdJson = sendRequest("copyMessage", data);
  Ptr<MessageId> messageIdObj(new MessageId(msgIdJson));
  return messageIdObj;
}

Ptr<Message> Api::forwardMessage(std::int64_t chatId, std::int64_t fromChatId, std::int32_t messageId, std::int32_t messageThreadId,
                                 bool disableNotification, bool protectContent) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("chat_id", std::to_string(chatId));          // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", std::to_string(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit fromChatId to 32bit integer gets overflown and sends wrong fromChatId which causes Bad Request: chat not found
  data.parts.emplace_back("message_id", messageId);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);

  nl::json sentMessageObj = sendRequest("sendMessage", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendPhoto(std::int64_t chatId, std::variant<cpr::File, std::string> photo,
                            std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification, bool protectContent,
                            std::int32_t replyToMessageId, bool allowSendingWithoutReply, const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (photo.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(photo);
    data.parts.emplace_back("photo", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(photo);
    data.parts.emplace_back("photo", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendPhoto", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendAudio(std::int64_t chatId,
                            std::variant<cpr::File, std::string> audio,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::int32_t duration,
                            const std::string& performer,
                            const std::string& title,
                            std::optional<std::variant<cpr::File, std::string>> thumbnail,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (audio.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(audio);
    data.parts.emplace_back("audio", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(audio);
    data.parts.emplace_back("audio", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (duration)
    data.parts.emplace_back("duration", duration);
  if (not performer.empty())
    data.parts.emplace_back("performer", performer);
  if (not title.empty())
    data.parts.emplace_back("title", title);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendAudio", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}
Ptr<Message> Api::sendDocument(std::int64_t chatId,
                               std::variant<cpr::File, std::string> document,
                               std::int32_t messageThreadId,
                               std::optional<std::variant<cpr::File, std::string>> thumbnail,
                               const std::string& caption,
                               const std::string& parseMode,
                               const std::vector<Ptr<MessageEntity>>& captionEntities,
                               bool disableNotification,
                               bool protectContent,
                               std::int32_t replyToMessageId,
                               bool allowSendingWithoutReply,
                               const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (document.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(document);
    data.parts.emplace_back("document", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(document);
    data.parts.emplace_back("document", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendDocument", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<File> Api::getFile(const std::string& fileId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("file_id", fileId);
  nl::json fileObj = sendRequest("getFile", data);
  Ptr<File> file(new File(fileObj));
  return file;
}

std::string Api::downloadFile(const std::string& filePath, const std::function<bool(cpr::cpr_off_t, cpr::cpr_off_t)>& progressCallback) const {
  std::ostringstream oss;
  oss << BASE_URL << "/file/bot" << m_token << "/" << filePath;

  cpr::Session session{};
  session.SetUrl(cpr::Url{oss.str()});
  session.SetTimeout(FILES_UPLOAD_TIMEOUT);
  session.SetConnectTimeout(CONNECT_TIMEOUT);
  session.SetAcceptEncoding({cpr::AcceptEncodingMethods::deflate, cpr::AcceptEncodingMethods::gzip, cpr::AcceptEncodingMethods::zlib});
  if (progressCallback) {
    cpr::ProgressCallback pCallback{[&progressCallback](cpr::cpr_off_t downloadTotal,
                                                        cpr::cpr_off_t downloadNow,
                                                        [[maybe_unused]] cpr::cpr_off_t uploadTotal,
                                                        [[maybe_unused]] cpr::cpr_off_t uploadNow,
                                                        [[maybe_unused]] std::intptr_t userdata) -> bool {
                                      return progressCallback(downloadTotal, downloadNow);
                                    },
                                    0};
    session.SetProgressCallback(pCallback);
  }
  cpr::Response res = session.Get();
  if (res.status_code == cpr::status::HTTP_OK) {
    return res.text;
  }
  throw Exception("Failed to download file " + filePath + " with status code: " + std::to_string(res.status_code));
}

Ptr<Message> Api::sendVideo(std::int64_t chatId,
                            std::variant<cpr::File, std::string> video,
                            std::int32_t messageThreadId,
                            std::int32_t duration,
                            std::int32_t width,
                            std::int32_t height,
                            std::optional<std::variant<cpr::File, std::string>> thumbnail,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            bool hasSpoiler,
                            bool supportsStreaming,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (video.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(video);
    data.parts.emplace_back("video", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(video);
    data.parts.emplace_back("video", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (duration)
    data.parts.emplace_back("duration", duration);
  if (width)
    data.parts.emplace_back("width", width);
  if (height)
    data.parts.emplace_back("height", height);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (hasSpoiler)
    data.parts.emplace_back("has_spoiler", hasSpoiler);
  if (supportsStreaming)
    data.parts.emplace_back("supports_streaming", supportsStreaming);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVideo", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendAnimation(std::int64_t chatId,
                                std::variant<cpr::File, std::string> animation,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t width,
                                std::int32_t height,
                                std::optional<std::variant<cpr::File, std::string>> thumbnail,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities,
                                bool hasSpoiler,
                                bool disableNotification,
                                bool protectContent,
                                std::int32_t replyToMessageId,
                                bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(16);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (animation.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(animation);
    data.parts.emplace_back("animation", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(animation);
    data.parts.emplace_back("animation", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (duration)
    data.parts.emplace_back("duration", duration);
  if (width)
    data.parts.emplace_back("width", width);
  if (height)
    data.parts.emplace_back("height", height);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (hasSpoiler)
    data.parts.emplace_back("has_spoiler", hasSpoiler);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendAnimation", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendVoice(std::int64_t chatId,
                            std::variant<cpr::File, std::string> voice,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::int32_t duration,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (voice.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(voice);
    data.parts.emplace_back("voice", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(voice);
    data.parts.emplace_back("voice", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (duration)
    data.parts.emplace_back("duration", duration);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVoice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendVideoNote(std::int64_t chatId,
                                std::variant<cpr::File, std::string> videoNote,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t length,
                                std::optional<std::variant<cpr::File, std::string>> thumbnail,
                                bool disableNotification,
                                bool protectContent,
                                std::int32_t replyToMessageId,
                                bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (videoNote.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(videoNote);
    data.parts.emplace_back("video_note", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(videoNote);
    data.parts.emplace_back("video_note", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (duration)
    data.parts.emplace_back("duration", duration);
  if (length)
    data.parts.emplace_back("length", duration);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVideoNote", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

std::vector<Ptr<Message>> Api::sendMediaGroup(std::int64_t chatId,
                                              const std::vector<Ptr<InputMedia>>& media,
                                              std::int32_t messageThreadId,
                                              bool disableNotification,
                                              bool protectContent,
                                              std::int32_t replyToMessageId,
                                              bool allowSendingWithoutReply) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (media.size() > 10 or media.size() < 2)
    throw Exception("Api::sendMediaGroup(): media must include 2-10 items. See https://core.telegram.org/bots/api#sendmediagroup");
  nl::json mediaJson = nl::json::array();
  for (const Ptr<InputMedia>& m: media)
    mediaJson.push_back(m->toJson());
  data.parts.emplace_back("media", mediaJson.dump());
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);

  nl::json sentMessagesArray = sendRequest("sendMediaGroup", data);
  std::vector<Ptr<Message>> sentMessages;
  sentMessages.reserve(sentMessagesArray.size());
  for (const nl::json& msgObj: sentMessagesArray) {
    Ptr<Message> msg(new Message(msgObj));
    sentMessages.push_back(std::move(msg));
  }
  return sentMessages;
}

Ptr<Message> Api::sendLocation(std::int64_t chatId,
                               float latitude,
                               float longitude,
                               std::int32_t messageThreadId,
                               float horizontalAccuracy,
                               std::int32_t livePeriod,
                               std::int32_t heading,
                               std::int32_t proximityAlertRadius,
                               bool disableNotification,
                               bool protectContent,
                               std::int32_t replyToMessageId,
                               bool allowSendingWithoutReply,
                               const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(13);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("latitude", latitude);
  data.parts.emplace_back("longitude", longitude);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (horizontalAccuracy != 0.0f)
    data.parts.emplace_back("horizontal_accuracy", horizontalAccuracy);
  if (livePeriod)
    data.parts.emplace_back("live_period", livePeriod);
  if (heading)
    data.parts.emplace_back("heading", heading);
  if (proximityAlertRadius)
    data.parts.emplace_back("proximity_alert_radius", proximityAlertRadius);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendLocation", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendVenue(std::int64_t chatId,
                            float latitude,
                            float longitude,
                            const std::string& title,
                            const std::string& address,
                            std::int32_t messageThreadId,
                            const std::string& foursquareId,
                            const std::string& foursquareType,
                            const std::string& googlePlaceId,
                            const std::string& googlePlaceType,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("latitude", latitude);
  data.parts.emplace_back("longitude", longitude);
  data.parts.emplace_back("title", title);
  data.parts.emplace_back("address", address);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not foursquareId.empty())
    data.parts.emplace_back("foursquare_id", foursquareId);
  if (not foursquareType.empty())
    data.parts.emplace_back("foursquare_type", foursquareType);
  if (not googlePlaceId.empty())
    data.parts.emplace_back("google_place_id", googlePlaceId);
  if (not googlePlaceType.empty())
    data.parts.emplace_back("google_place_type", googlePlaceType);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVenue", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendContact(std::int64_t chatId,
                              const std::string& phoneNumber,
                              const std::string& firstName,
                              const std::string& lastName,
                              const std::string& vcard,
                              std::int32_t messageThreadId,
                              bool disableNotification,
                              bool protectContent,
                              std::int32_t replyToMessageId,
                              bool allowSendingWithoutReply,
                              const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("phone_number", phoneNumber);
  data.parts.emplace_back("first_name", firstName);
  if (not lastName.empty())
    data.parts.emplace_back("last_name", lastName);
  if (not vcard.empty())
    data.parts.emplace_back("vcard", vcard);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendContact", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendPoll(std::int64_t chatId,
                           const std::string& question,
                           const std::vector<std::string>& options,
                           bool isAnonymous,
                           const std::string& type,
                           bool allowsMultipleAnswers,
                           std::int32_t correctOptionId,
                           const std::string& explanation,
                           const std::string& explanationParseMode,
                           const std::vector<Ptr<MessageEntity>>& explanationEntities,
                           std::int32_t openPeriod,
                           std::int32_t closeDate,
                           bool isClosed,
                           std::int32_t messageThreadId,
                           bool disableNotification,
                           bool protectContent,
                           std::int32_t replyToMessageId,
                           bool allowSendingWithoutReply,
                           const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(19);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("question", question);
  data.parts.emplace_back("options", nl::json(options).dump());
  if (not isAnonymous)
    data.parts.emplace_back("is_anonymous", isAnonymous);
  if (not type.empty())
    data.parts.emplace_back("type", type);
  if (allowsMultipleAnswers)
    data.parts.emplace_back("allows_multiple_answers", allowsMultipleAnswers);
  if (correctOptionId >= 0)
    data.parts.emplace_back("correct_option_id", correctOptionId);
  if (not explanation.empty())
    data.parts.emplace_back("explanation", explanation);
  if (not explanationParseMode.empty())
    data.parts.emplace_back("explanation_parse_mode", explanationParseMode);
  if (not explanationEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: explanationEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("explanation_entities", entitiesArray.dump());
  }
  if (openPeriod)
    data.parts.emplace_back("open_period", openPeriod);
  if (closeDate)
    data.parts.emplace_back("close_date", closeDate);
  if (isClosed)
    data.parts.emplace_back("is_closed", isClosed);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendPoll", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendDice(std::int64_t chatId,
                           const std::string& emoji,
                           std::int32_t messageThreadId,
                           bool disableNotification,
                           bool protectContent,
                           std::int32_t replyToMessageId,
                           bool allowSendingWithoutReply,
                           const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (not emoji.empty())
    data.parts.emplace_back("emoji", emoji);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyToMessageId)
    data.parts.emplace_back("reply_to_message_id", replyToMessageId);
  if (allowSendingWithoutReply)
    data.parts.emplace_back("allow_sending_without_reply", allowSendingWithoutReply);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendDice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

bool Api::sendChatAction(std::int64_t chatId,
                         const std::string& action,
                         std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("action", action);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);

  return sendRequest("sendChatAction", data);
}

Ptr<UserProfilePhotos> Api::getUserProfilePhotos(std::int64_t userId,
                                                 std::int32_t offset,
                                                 std::int32_t limit) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (offset)
    data.parts.emplace_back("offset", offset);
  if (limit)
    data.parts.emplace_back("limit", limit);

  nl::json userProfilePhotosObj = sendRequest("getUserProfilePhotos", data);
  Ptr<UserProfilePhotos> userProfilePhotos(new UserProfilePhotos(userProfilePhotosObj));
  return userProfilePhotos;
}

bool Api::banChatMember(std::int64_t chatId,
                        std::int64_t userId,
                        std::time_t untilDate,
                        bool revokeMessages) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (untilDate)
    data.parts.emplace_back("until_date", untilDate);
  if (revokeMessages)
    data.parts.emplace_back("revoke_messages", revokeMessages);

  return sendRequest("banChatMember", data);
}

bool Api::unbanChatMember(std::int64_t chatId,
                          std::int64_t userId,
                          bool onlyIfBanned) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (onlyIfBanned)
    data.parts.emplace_back("only_if_banned", onlyIfBanned);

  return sendRequest("unbanChatMember", data);
}

bool Api::restrictChatMember(std::int64_t chatId,
                             std::int64_t userId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions,
                             std::time_t untilDate) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.parts.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
  if (untilDate)
    data.parts.emplace_back("until_date", untilDate);

  return sendRequest("restrictChatMember", data);
}

bool Api::promoteChatMember(std::int64_t chatId,
                            std::int64_t userId,
                            bool isAnonymous,
                            bool canManageChat,
                            bool canDeleteMessages,
                            bool canManageVideoChats,
                            bool canRestrictMembers,
                            bool canPromoteMembers,
                            bool canChangeInfo,
                            bool canInviteUsers,
                            bool canPostMessages,
                            bool canEditMessages,
                            bool canPinMessages,
                            bool canPostStories,
                            bool canEditStories,
                            bool canDeleteStories,
                            bool canManageTopics) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (isAnonymous)
    data.parts.emplace_back("is_anonymous", isAnonymous);
  if (canManageChat)
    data.parts.emplace_back("can_manage_chat", canManageChat);
  if (canDeleteMessages)
    data.parts.emplace_back("can_delete_messages", canDeleteMessages);
  if (canManageVideoChats)
    data.parts.emplace_back("can_manage_video_chats", canManageVideoChats);
  if (canRestrictMembers)
    data.parts.emplace_back("can_restrict_members", canRestrictMembers);
  if (canPromoteMembers)
    data.parts.emplace_back("can_promote_members", canPromoteMembers);
  if (canChangeInfo)
    data.parts.emplace_back("can_change_info", canChangeInfo);
  if (canInviteUsers)
    data.parts.emplace_back("can_invite_users", canInviteUsers);
  if (canPostMessages)
    data.parts.emplace_back("can_post_messages", canPostMessages);
  if (canEditMessages)
    data.parts.emplace_back("can_edit_messages", canEditMessages);
  if (canPinMessages)
    data.parts.emplace_back("can_pin_messages", canPinMessages);
  if (canPostStories)
    data.parts.emplace_back("can_post_stories", canPostStories);
  if (canEditStories)
    data.parts.emplace_back("can_edit_stories", canEditStories);
  if (canDeleteStories)
    data.parts.emplace_back("can_delete_stories", canDeleteStories);
  if (canManageTopics)
    data.parts.emplace_back("can_manage_topics", canManageTopics);
  return sendRequest("promoteChatMember", data);
}

bool Api::setChatAdministratorCustomTitle(std::int64_t chatId,
                                          std::int64_t userId,
                                          const std::string& customTitle) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("custom_title", customTitle);
  return sendRequest("setChatAdministratorCustomTitle", data);
}

bool Api::banChatSenderChat(std::int64_t chatId,
                            std::int64_t senderChatId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("banChatSenderChat", data);
}

bool Api::unbanChatSenderChat(std::int64_t chatId,
                              std::int64_t senderChatId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("unbanChatSenderChat", data);
}

bool Api::setChatPermissions(std::int64_t chatId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.parts.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
  return sendRequest("setChatPermissions", data);
}

std::string Api::exportChatInviteLink(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("exportChatInviteLink", data);
}

Ptr<ChatInviteLink> Api::createChatInviteLink(std::int64_t chatId,
                                              const std::string& name,
                                              std::time_t expireDate,
                                              std::int32_t memberLimit,
                                              bool createsJoinRequest) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (not name.empty())
    data.parts.emplace_back("name", name);
  if (expireDate)
    data.parts.emplace_back("expire_date", expireDate);
  if (memberLimit)
    data.parts.emplace_back("member_limit", memberLimit);
  if (createsJoinRequest)
    data.parts.emplace_back("creates_join_request", createsJoinRequest);

  nl::json chatInviteLinkObj = sendRequest("createChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::editChatInviteLink(std::int64_t chatId,
                                            const std::string& inviteLink,
                                            const std::string& name,
                                            std::time_t expireDate,
                                            std::int32_t memberLimit,
                                            bool createsJoinRequest) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("invite_link", inviteLink);
  if (not name.empty())
    data.parts.emplace_back("name", name);
  if (expireDate)
    data.parts.emplace_back("expire_date", expireDate);
  if (memberLimit)
    data.parts.emplace_back("member_limit", memberLimit);
  if (createsJoinRequest)
    data.parts.emplace_back("creates_join_request", createsJoinRequest);

  nl::json chatInviteLinkObj = sendRequest("editChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::revokeChatInviteLink(std::int64_t chatId,
                                              const std::string& inviteLink) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("invite_link", inviteLink);

  nl::json chatInviteLinkObj = sendRequest("revokeChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

bool Api::approveChatJoinRequest(std::int64_t chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  return sendRequest("approveChatJoinRequest", data);
}

bool Api::declineChatJoinRequest(std::int64_t chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  return sendRequest("declineChatJoinRequest", data);
}

bool Api::setChatPhoto(std::int64_t chatId, const cpr::File& photo) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("photo", cpr::Files{photo});
  return sendRequest("setChatPhoto", data);
}

bool Api::deleteChatPhoto(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("deleteChatPhoto", data);
}

bool Api::setChatTitle(std::int64_t chatId, const std::string& title) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("title", title);
  return sendRequest("setChatTitle", data);
}

bool Api::setChatDescription(std::int64_t chatId, const std::string& description) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (not description.empty())
    data.parts.emplace_back("description", description);
  return sendRequest("setChatDescription", data);
}

bool Api::pinChatMessage(std::int64_t chatId,
                         std::int32_t messageId,
                         bool disableNotification) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  return sendRequest("pinChatMessage", data);
}

bool Api::unpinChatMessage(std::int64_t chatId, std::int32_t messageId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  return sendRequest("unpinChatMessage", data);
}

bool Api::unpinAllChatMessages(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("unpinAllChatMessages", data);
}


bool Api::leaveChat(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("leaveChat", data);
}

Ptr<Chat> Api::getChat(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));

  nl::json chatObj = sendRequest("getChat", data);
  Ptr<Chat> chat(new Chat(chatObj));
  return chat;
}

std::vector<Ptr<ChatMember>> Api::getChatAdministrators(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));

  nl::json chatMembersArray = sendRequest("getChatAdministrators", data);
  std::vector<Ptr<ChatMember>> chatMembers;
  chatMembers.reserve(chatMembersArray.size());
  for (const nl::json& chatMemberObj: chatMembersArray) {
    Ptr<ChatMember> chatMember(new ChatMember(chatMemberObj));
    chatMembers.push_back(std::move(chatMember));
  }
  return chatMembers;
}

std::int32_t Api::getChatMemberCount(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("getChatMemberCount", data);
}

Ptr<ChatMember> Api::getChatMember(std::int64_t chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));

  nl::json chatMemberObj = sendRequest("getChatMember", data);
  Ptr<ChatMember> chatMember(new ChatMember(chatMemberObj));
  return chatMember;
}

bool Api::setChatStickerSet(std::int64_t chatId, const std::string& stickerSetName) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("sticker_set_name", stickerSetName);
  return sendRequest("setChatStickerSet", data);
}

bool Api::deleteChatStickerSet(std::int64_t chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  return sendRequest("deleteChatStickerSet", data);
}

std::vector<Ptr<Sticker>> Api::getForumTopicIconStickers() const {
  nl::json stickersArray = sendRequest("getForumTopicIconStickers");
  std::vector<Ptr<Sticker>> stickers;
  stickers.reserve(stickersArray.size());
  for (const nl::json& stickerObj: stickersArray) {
    Ptr<Sticker> sticker(new Sticker(stickerObj));
    stickers.push_back(std::move(sticker));
  }
  return stickers;
}

Ptr<ForumTopic> Api::createForumTopic(std::int64_t chatId,
                                      const std::string& name,
                                      std::int32_t iconColor,
                                      const std::string& iconCustomEmojiId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("name", name);
  if (iconColor)
    data.parts.emplace_back("icon_color", iconColor);
  if (not iconCustomEmojiId.empty())
    data.parts.emplace_back("icon_custom_emoji_id", iconCustomEmojiId);

  nl::json forumTopicObj = sendRequest("createForumTopic", data);
  Ptr<ForumTopic> forumTopic(new ForumTopic(forumTopicObj));
  return forumTopic;
}
