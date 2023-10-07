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
    {"limit", (std::max)(1, (std::min)(100, limit))},
    {"timeout", timeout},
    {"allowed_updates", allowedUpdates.empty() ? "[]" : nl::json{allowedUpdates}.dump()},
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

bool Api::setMyCommands(const std::vector<Ptr<BotCommand>>& commands, const Ptr<BotCommandScope>& scope,
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
  data.parts.emplace_back("chat_id", std::to_string(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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
  data.parts.emplace_back("chat_id", std::to_string(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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
  data.parts.emplace_back("chat_id", std::to_string(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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
  if(progressCallback) {
    cpr::ProgressCallback pCallback{[&progressCallback](cpr::cpr_off_t downloadTotal,
                                                        cpr::cpr_off_t downloadNow,
                                                        [[maybe_unused]] cpr::cpr_off_t uploadTotal,
                                                        [[maybe_unused]] cpr::cpr_off_t uploadNow,
                                                        [[maybe_unused]] std::intptr_t userdata) -> bool {
                                      return progressCallback(downloadTotal, downloadNow);
                                    }, 0};
    session.SetProgressCallback(pCallback);
  }
  cpr::Response res = session.Get();
  if (res.status_code == cpr::status::HTTP_OK) {
    return res.text;
  }
  throw Exception("Failed to download file " + filePath + " with status code: " + std::to_string(res.status_code));
}
