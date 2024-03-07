#include <chrono>
#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Exception.hpp>
/// Objects
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <tgbotxx/objects/BotDescription.hpp>
#include <tgbotxx/objects/BotName.hpp>
#include <tgbotxx/objects/BotShortDescription.hpp>
#include <tgbotxx/objects/CallbackGame.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>
#include <tgbotxx/objects/ChatInviteLink.hpp>
#include <tgbotxx/objects/ChatJoinRequest.hpp>
#include <tgbotxx/objects/ChatLocation.hpp>
#include <tgbotxx/objects/ChatMember.hpp>
#include <tgbotxx/objects/ChatMemberUpdated.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/ChatPhoto.hpp>
#include <tgbotxx/objects/ChatShared.hpp>
#include <tgbotxx/objects/ChosenInlineResult.hpp>
#include <tgbotxx/objects/Contact.hpp>
#include <tgbotxx/objects/Dice.hpp>
#include <tgbotxx/objects/Document.hpp>
#include <tgbotxx/objects/EncryptedCredentials.hpp>
#include <tgbotxx/objects/EncryptedPassportElement.hpp>
#include <tgbotxx/objects/File.hpp>
#include <tgbotxx/objects/ForumTopic.hpp>
#include <tgbotxx/objects/ForumTopicClosed.hpp>
#include <tgbotxx/objects/ForumTopicCreated.hpp>
#include <tgbotxx/objects/ForumTopicEdited.hpp>
#include <tgbotxx/objects/ForumTopicReopened.hpp>
#include <tgbotxx/objects/Game.hpp>
#include <tgbotxx/objects/GeneralForumTopicHidden.hpp>
#include <tgbotxx/objects/GeneralForumTopicUnhidden.hpp>
#include <tgbotxx/objects/IReplyMarkup.hpp>
#include <tgbotxx/objects/InlineKeyboardButton.hpp>
#include <tgbotxx/objects/InlineKeyboardMarkup.hpp>
#include <tgbotxx/objects/InlineQuery.hpp>
#include <tgbotxx/objects/InlineQueryResult.hpp>
#include <tgbotxx/objects/InlineQueryResultsButton.hpp>
#include <tgbotxx/objects/InputMedia.hpp>
#include <tgbotxx/objects/InputSticker.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/KeyboardButton.hpp>
#include <tgbotxx/objects/KeyboardButtonPollType.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestChat.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestUser.hpp>
#include <tgbotxx/objects/LabeledPrice.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/MenuButton.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/MessageAutoDeleteTimerChanged.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/MessageId.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>
#include <tgbotxx/objects/PassportData.hpp>
#include <tgbotxx/objects/PassportFile.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/PollOption.hpp>
#include <tgbotxx/objects/PreCheckoutQuery.hpp>
#include <tgbotxx/objects/ProximityAlertTriggered.hpp>
#include <tgbotxx/objects/ReplyKeyboardMarkup.hpp>
#include <tgbotxx/objects/ReplyKeyboardRemove.hpp>
#include <tgbotxx/objects/ReplyParameters.hpp>
#include <tgbotxx/objects/SentWebAppMessage.hpp>
#include <tgbotxx/objects/ShippingAddress.hpp>
#include <tgbotxx/objects/ShippingOption.hpp>
#include <tgbotxx/objects/ShippingQuery.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/StickerSet.hpp>
#include <tgbotxx/objects/Story.hpp>
#include <tgbotxx/objects/SuccessfulPayment.hpp>
#include <tgbotxx/objects/SwitchInlineQueryChosenChat.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/UserProfilePhotos.hpp>
#include <tgbotxx/objects/UserShared.hpp>
#include <tgbotxx/objects/Venue.hpp>
#include <tgbotxx/objects/Video.hpp>
#include <tgbotxx/objects/VideoChatEnded.hpp>
#include <tgbotxx/objects/VideoChatParticipantsInvited.hpp>
#include <tgbotxx/objects/VideoChatScheduled.hpp>
#include <tgbotxx/objects/VideoChatStarted.hpp>
#include <tgbotxx/objects/VideoNote.hpp>
#include <tgbotxx/objects/Voice.hpp>
#include <tgbotxx/objects/WebAppData.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>
#include <tgbotxx/objects/WebhookInfo.hpp>
#include <tgbotxx/objects/WriteAccessAllowed.hpp>

#include <utility>
using namespace tgbotxx;

/// Static declarations
const std::string Api::DEFAULT_API_URL = "https://api.telegram.org";                           /// Telegram Api Url (Use api()->setUrl("http..") to set your self-hosted url)
const cpr::ConnectTimeout Api::DEFAULT_CONNECT_TIMEOUT = std::chrono::milliseconds(20 * 1000); /// 20s (Telegram server can take up to 20s to connect with us)
const cpr::Timeout Api::DEFAULT_TIMEOUT = std::chrono::seconds(60 + 10);                       /// 70s (Telegram server can take up to 70s to reply us (should be longer than long poll timeout)).
const cpr::Timeout Api::DEFAULT_LONG_POLL_TIMEOUT = std::chrono::seconds(60);                  /// 60s (long polling getUpdates() every 60 seconds) Telegram's guidelines recommended a timeout between 30 and 90 seconds for long polling.
const cpr::Timeout Api::DEFAULT_UPLOAD_FILES_TIMEOUT = std::chrono::seconds(15 * 60);          /// 15min (Files can take longer time to upload. Setting a shorter timeout will stop the request even if the file isn't fully uploaded)
const cpr::Timeout Api::DEFAULT_DOWNLOAD_FILES_TIMEOUT = std::chrono::seconds(30 * 60);        /// 30min (Files can take longer time to download. Setting a shorter timeout will stop the request even if the file isn't fully downloaded)

Api::Api(const std::string& token) : m_token(token) {}

nl::json Api::sendRequest(const std::string& endpoint, const cpr::Multipart& data) const {
  cpr::Session session{}; // Note: Why not have one session as a class member to use for all requests ?
                          // You can initiate multiple concurrent requests to the Telegram API, which means
                          // You can call sendMessage while getUpdates long polling is still pending, and you can't do that with a single cpr::Session instance.
  bool hasFiles = std::any_of(data.parts.begin(), data.parts.end(), [](const cpr::Part& part) noexcept { return part.is_file; });
  session.SetConnectTimeout(m_connectTimeout);
  session.SetTimeout(hasFiles ? m_uploadFilesTimeout : m_timeout); // Files can take longer to upload
  session.SetHeader(cpr::Header{
    {"Connection", "close"}, // disable keep-alive
    {"Accept", "application/json"},
    {"User-Agent", "tgbotxx/" TGBOTXX_VERSION},
    {"Content-Type", "application/x-www-form-urlencoded"},
  });
  std::ostringstream url{};
  url << m_apiUrl << "/bot" << m_token << '/' << endpoint; // Note: token should have a prefix botTOKEN.
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

bool Api::logOut() const {
  return sendRequest("logOut");
}

bool Api::close() const {
  return sendRequest("close");
}

Ptr<Message> Api::sendMessage(const std::variant<std::int64_t, std::string>& chatId, const std::string& text, std::int32_t messageThreadId,
                              const std::string& parseMode, const std::vector<Ptr<MessageEntity>>& entities,
                              bool disableWebPagePreview, bool disableNotification, bool protectContent,
                              std::int32_t replyToMessageId, bool allowSendingWithoutReply,
                              const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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

Ptr<MessageId> Api::copyMessage(const std::variant<std::int64_t, std::string>& chatId, const std::variant<std::int64_t, std::string>& fromChatId, std::int32_t messageId,
                                std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification,
                                bool protectContent, std::int32_t replyToMessageId, bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));              // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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

Ptr<Message> Api::forwardMessage(const std::variant<std::int64_t, std::string>& chatId, const std::variant<std::int64_t, std::string>& fromChatId, std::int32_t messageId, std::int32_t messageThreadId,
                                 bool disableNotification, bool protectContent) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));              // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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

Ptr<Message> Api::sendPhoto(const std::variant<std::int64_t, std::string>& chatId, const std::variant<cpr::File, std::string>& photo,
                            std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification, bool protectContent,
                            std::int32_t replyToMessageId, bool allowSendingWithoutReply, const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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

Ptr<Message> Api::sendAudio(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& audio,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::int32_t duration,
                            const std::string& performer,
                            const std::string& title,
                            const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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
Ptr<Message> Api::sendDocument(const std::variant<std::int64_t, std::string>& chatId,
                               const std::variant<cpr::File, std::string>& document,
                               std::int32_t messageThreadId,
                               const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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
  std::ostringstream oss{};
  oss << m_apiUrl << "/file/bot" << m_token << "/" << filePath;

  cpr::Session session{};
  session.SetUrl(cpr::Url{oss.str()});
  session.SetConnectTimeout(m_connectTimeout);
  session.SetTimeout(m_downloadFilesTimeout);
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

Ptr<Message> Api::sendVideo(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& video,
                            std::int32_t messageThreadId,
                            std::int32_t duration,
                            std::int32_t width,
                            std::int32_t height,
                            const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<Message> Api::sendAnimation(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<cpr::File, std::string>& animation,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t width,
                                std::int32_t height,
                                const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<Message> Api::sendVoice(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& voice,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<Message> Api::sendVideoNote(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<cpr::File, std::string>& videoNote,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t length,
                                const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                                bool disableNotification,
                                bool protectContent,
                                std::int32_t replyToMessageId,
                                bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

std::vector<Ptr<Message>> Api::sendMediaGroup(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::vector<Ptr<InputMedia>>& media,
                                              std::int32_t messageThreadId,
                                              bool disableNotification,
                                              bool protectContent,
                                              std::int32_t replyToMessageId,
                                              bool allowSendingWithoutReply) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (media.size() > 10 or media.size() < 2)
    throw Exception("Api::sendMediaGroup(): media must include 2-10 items. See https://core.telegram.org/bots/api#sendmediagroup");
  nl::json mediaJson = nl::json::array();
  // Handle local media files if available, see https://core.telegram.org/bots/api#inputmediaphoto
  for (const Ptr<InputMedia>& m: media) {
    nl::json mJson = m->toJson();
    switch (m->media.index()) {
      case 0: // cpr::File (Local File)
      {
        const cpr::File& file = std::get<cpr::File>(m->media);
        std::string fileKey = StringUtils::random(8);
        mJson["media"] = "attach://" + fileKey;
        data.parts.emplace_back(fileKey, cpr::Files{file});
        break;
      }
      case 1: // std::string (URL, File ID)
      {
        // do nothing as toJson will export the "media": "URL or file ID" object.
        break;
      }
    }
    mediaJson.push_back(mJson);
  }
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

Ptr<Message> Api::sendLocation(const std::variant<std::int64_t, std::string>& chatId,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("latitude", std::to_string(latitude));
  data.parts.emplace_back("longitude", std::to_string(longitude));
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

Ptr<Message> Api::sendVenue(const std::variant<std::int64_t, std::string>& chatId,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("latitude", std::to_string(latitude));
  data.parts.emplace_back("longitude", std::to_string(longitude));
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

Ptr<Message> Api::sendContact(const std::variant<std::int64_t, std::string>& chatId,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<Message> Api::sendPoll(const std::variant<std::int64_t, std::string>& chatId,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<Message> Api::sendDice(const std::variant<std::int64_t, std::string>& chatId,
                           const std::string& emoji,
                           std::int32_t messageThreadId,
                           bool disableNotification,
                           bool protectContent,
                           std::int32_t replyToMessageId,
                           bool allowSendingWithoutReply,
                           const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

bool Api::sendChatAction(const std::variant<std::int64_t, std::string>& chatId,
                         const std::string& action,
                         std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

bool Api::banChatMember(const std::variant<std::int64_t, std::string>& chatId,
                        std::int64_t userId,
                        std::time_t untilDate,
                        bool revokeMessages) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (untilDate)
    data.parts.emplace_back("until_date", untilDate);
  if (revokeMessages)
    data.parts.emplace_back("revoke_messages", revokeMessages);

  return sendRequest("banChatMember", data);
}

bool Api::unbanChatMember(const std::variant<std::int64_t, std::string>& chatId,
                          std::int64_t userId,
                          bool onlyIfBanned) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (onlyIfBanned)
    data.parts.emplace_back("only_if_banned", onlyIfBanned);

  return sendRequest("unbanChatMember", data);
}

bool Api::restrictChatMember(const std::variant<std::int64_t, std::string>& chatId,
                             std::int64_t userId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions,
                             std::time_t untilDate) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.parts.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
  if (untilDate)
    data.parts.emplace_back("until_date", untilDate);

  return sendRequest("restrictChatMember", data);
}

bool Api::promoteChatMember(const std::variant<std::int64_t, std::string>& chatId,
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
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

bool Api::setChatAdministratorCustomTitle(const std::variant<std::int64_t, std::string>& chatId,
                                          std::int64_t userId,
                                          const std::string& customTitle) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("custom_title", customTitle);
  return sendRequest("setChatAdministratorCustomTitle", data);
}

bool Api::banChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                            std::int64_t senderChatId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("banChatSenderChat", data);
}

bool Api::unbanChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                              std::int64_t senderChatId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("unbanChatSenderChat", data);
}

bool Api::setChatPermissions(const std::variant<std::int64_t, std::string>& chatId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.parts.emplace_back("use_independent_chat_permissions", useIndependentChatPermissions);
  return sendRequest("setChatPermissions", data);
}

std::string Api::exportChatInviteLink(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("exportChatInviteLink", data);
}

Ptr<ChatInviteLink> Api::createChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::string& name,
                                              std::time_t expireDate,
                                              std::int32_t memberLimit,
                                              bool createsJoinRequest) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<ChatInviteLink> Api::editChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                            const std::string& inviteLink,
                                            const std::string& name,
                                            std::time_t expireDate,
                                            std::int32_t memberLimit,
                                            bool createsJoinRequest) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<ChatInviteLink> Api::revokeChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::string& inviteLink) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("invite_link", inviteLink);

  nl::json chatInviteLinkObj = sendRequest("revokeChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

bool Api::approveChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  return sendRequest("approveChatJoinRequest", data);
}

bool Api::declineChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  return sendRequest("declineChatJoinRequest", data);
}

bool Api::setChatPhoto(const std::variant<std::int64_t, std::string>& chatId, const cpr::File& photo) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("photo", cpr::Files{photo});
  return sendRequest("setChatPhoto", data);
}

bool Api::deleteChatPhoto(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("deleteChatPhoto", data);
}

bool Api::setChatTitle(const std::variant<std::int64_t, std::string>& chatId, const std::string& title) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("title", title);
  return sendRequest("setChatTitle", data);
}

bool Api::setChatDescription(const std::variant<std::int64_t, std::string>& chatId, const std::string& description) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (not description.empty())
    data.parts.emplace_back("description", description);
  return sendRequest("setChatDescription", data);
}

bool Api::pinChatMessage(const std::variant<std::int64_t, std::string>& chatId,
                         std::int32_t messageId,
                         bool disableNotification) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  return sendRequest("pinChatMessage", data);
}

bool Api::unpinChatMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  return sendRequest("unpinChatMessage", data);
}

bool Api::unpinAllChatMessages(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("unpinAllChatMessages", data);
}


bool Api::leaveChat(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("leaveChat", data);
}

Ptr<Chat> Api::getChat(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));

  nl::json chatObj = sendRequest("getChat", data);
  Ptr<Chat> chat(new Chat(chatObj));
  return chat;
}

std::vector<Ptr<ChatMember>> Api::getChatAdministrators(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));

  nl::json chatMembersArray = sendRequest("getChatAdministrators", data);
  std::vector<Ptr<ChatMember>> chatMembers;
  chatMembers.reserve(chatMembersArray.size());
  for (const nl::json& chatMemberObj: chatMembersArray) {
    Ptr<ChatMember> chatMember(new ChatMember(chatMemberObj));
    chatMembers.push_back(std::move(chatMember));
  }
  return chatMembers;
}

std::int32_t Api::getChatMemberCount(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("getChatMemberCount", data);
}

Ptr<ChatMember> Api::getChatMember(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));

  nl::json chatMemberObj = sendRequest("getChatMember", data);
  Ptr<ChatMember> chatMember(new ChatMember(chatMemberObj));
  return chatMember;
}

bool Api::setChatStickerSet(const std::variant<std::int64_t, std::string>& chatId, const std::string& stickerSetName) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("sticker_set_name", stickerSetName);
  return sendRequest("setChatStickerSet", data);
}

bool Api::deleteChatStickerSet(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
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

Ptr<ForumTopic> Api::createForumTopic(const std::variant<std::int64_t, std::string>& chatId,
                                      const std::string& name,
                                      std::int32_t iconColor,
                                      const std::string& iconCustomEmojiId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("name", name);
  if (iconColor)
    data.parts.emplace_back("icon_color", iconColor);
  if (not iconCustomEmojiId.empty())
    data.parts.emplace_back("icon_custom_emoji_id", iconCustomEmojiId);

  nl::json forumTopicObj = sendRequest("createForumTopic", data);
  Ptr<ForumTopic> forumTopic(new ForumTopic(forumTopicObj));
  return forumTopic;
}

bool Api::editForumTopic(const std::variant<std::int64_t, std::string>& chatId,
                         std::int32_t messageThreadId,
                         const std::string& name,
                         const std::optional<std::string>& iconCustomEmojiId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not name.empty())
    data.parts.emplace_back("name", name);
  if (iconCustomEmojiId.has_value()) {
    data.parts.emplace_back("icon_custom_emoji_id", *iconCustomEmojiId);
  }
  return sendRequest("editForumTopic", data);
}

bool Api::closeForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_thread_id", messageThreadId);
  return sendRequest("closeForumTopic", data);
}

bool Api::reopenForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_thread_id", messageThreadId);
  return sendRequest("reopenForumTopic", data);
}

bool Api::deleteForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_thread_id", messageThreadId);
  return sendRequest("deleteForumTopic", data);
}

bool Api::unpinAllForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_thread_id", messageThreadId);
  return sendRequest("unpinAllForumTopicMessages", data);
}

bool Api::editGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId, const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("name", name);
  return sendRequest("editGeneralForumTopic", data);
}

bool Api::closeGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("closeGeneralForumTopic", data);
}

bool Api::reopenGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("reopenGeneralForumTopic", data);
}

bool Api::hideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("hideGeneralForumTopic", data);
}

bool Api::unhideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("unhideGeneralForumTopic", data);
}

bool Api::unpinAllGeneralForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  return sendRequest("unpinAllGeneralForumTopicMessages", data);
}

bool Api::answerCallbackQuery(const std::string& callbackQueryId,
                              const std::string& text,
                              bool showAlert,
                              const std::string& url,
                              std::int32_t cacheTime) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("callback_query_id", callbackQueryId);
  if (not text.empty())
    data.parts.emplace_back("text", text);
  if (showAlert)
    data.parts.emplace_back("show_alert", showAlert);
  if (not url.empty())
    data.parts.emplace_back("url", url);
  if (cacheTime)
    data.parts.emplace_back("cache_time", cacheTime);
  return sendRequest("answerCallbackQuery", data);
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
  if (scope)
    data.parts.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.parts.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);


  return sendRequest("setMyCommands", data);
}

bool Api::deleteMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (scope)
    data.parts.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.parts.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);
  return sendRequest("deleteMyCommands", data);
}

std::vector<Ptr<BotCommand>> Api::getMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  std::vector<Ptr<BotCommand>> commands;
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (scope)
    data.parts.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.parts.emplace_back("scope", defScope->toJson().dump());
  }
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

bool Api::setMyName(const std::string& name, const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (not name.empty())
    data.parts.emplace_back("name", name);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);
  return sendRequest("setMyName", data);
}

Ptr<BotName> Api::getMyName(const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);

  nl::json botNameObj = sendRequest("getMyName", data);
  ;
  return makePtr<BotName>(botNameObj);
}

bool Api::setMyDescription(const std::string& description, const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (not description.empty())
    data.parts.emplace_back("description", description);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);
  return sendRequest("setMyDescription", data);
}

Ptr<BotDescription> Api::getMyDescription(const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);

  nl::json botDescObj = sendRequest("getMyDescription", data);
  ;
  return makePtr<BotDescription>(botDescObj);
}

bool Api::setMyShortDescription(const std::string& shortDescription, const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (not shortDescription.empty())
    data.parts.emplace_back("short_description", shortDescription);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);
  return sendRequest("setMyShortDescription", data);
}

Ptr<BotShortDescription> Api::getMyShortDescription(const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);

  nl::json botShortDescObj = sendRequest("getMyShortDescription", data);
  return makePtr<BotShortDescription>(botShortDescObj);
}

bool Api::setChatMenuButton(const std::variant<std::int64_t, std::string>& chatId, const Ptr<tgbotxx::MenuButton>& menuButton) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  std::string chatIdStr = chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId);
  if (not chatIdStr.empty())
    data.parts.emplace_back("chat_id", chatIdStr);
  if (menuButton)
    data.parts.emplace_back("menu_button", menuButton->toJson().dump());
  else {
    auto defMenuButton = makePtr<MenuButtonDefault>();
    data.parts.emplace_back("menu_button", defMenuButton->toJson().dump());
  }
  return sendRequest("setChatMenuButton", data);
}

Ptr<MenuButton> Api::getChatMenuButton(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  std::string chatIdStr = chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId);
  if (not chatIdStr.empty())
    data.parts.emplace_back("chat_id", chatIdStr);
  nl::json chatMenuObj = sendRequest("getChatMenuButton", data);
  std::string type = chatMenuObj["type"].get<std::string>();
  if (type == "web_app")
    return makePtr<MenuButtonWebApp>(chatMenuObj);
  else if (type == "commands")
    return makePtr<MenuButtonCommands>(chatMenuObj);
  // (type == "default")
  return makePtr<MenuButtonDefault>(chatMenuObj);
}

bool Api::setMyDefaultAdministratorRights(const Ptr<tgbotxx::ChatAdministratorRights>& rights, bool forChannels) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (rights)
    data.parts.emplace_back("rights", rights->toJson().dump());
  if (forChannels)
    data.parts.emplace_back("for_channels", forChannels);
  return sendRequest("setMyDefaultAdministratorRights", data);
}

Ptr<ChatAdministratorRights> Api::getMyDefaultAdministratorRights(bool forChannels) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  if (forChannels)
    data.parts.emplace_back("for_channels", forChannels);
  nl::json chatAdministratorRightsObj = sendRequest("getMyDefaultAdministratorRights", data);
  return makePtr<ChatAdministratorRights>(chatAdministratorRightsObj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  if (dropPendingUpdates)
    data.parts.emplace_back("drop_pending_updates", dropPendingUpdates);
  return sendRequest("deleteWebhook", data);
}

/// Called every LONG_POOL_TIMEOUT seconds
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, const std::vector<std::string>& allowedUpdates) const {
  std::vector<Ptr<Update>> updates;
  cpr::Multipart data = {
    {"offset", offset},
    {"limit", std::max<std::int32_t>(1, std::min<std::int32_t>(100, limit))},
    {"timeout", static_cast<std::int32_t>(std::chrono::duration_cast<std::chrono::seconds>(m_longPollTimeout.ms).count())},
    {"allowed_updates", nl::json(allowedUpdates).dump()},
  };
  nl::json updatesJson = sendRequest("getUpdates", data);
  updates.reserve(updatesJson.size());
  for (const nl::json& updateObj: updatesJson) {
    Ptr<Update> update(new Update(updateObj));
    updates.push_back(std::move(update));
  }
  return updates;
}


bool Api::setWebhook(const std::string& url,
                     const std::optional<cpr::File>& certificate,
                     const std::string& ipAddress,
                     std::int32_t maxConnections,
                     const std::vector<std::string>& allowedUpdates,
                     bool dropPendingUpdates,
                     const std::string& secretToken) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("url", url);
  if (certificate.has_value())
    data.parts.emplace_back("certificate", cpr::Files{*certificate});
  if (not ipAddress.empty())
    data.parts.emplace_back("ip_address", ipAddress);
  if (maxConnections != 40)
    data.parts.emplace_back("max_connections", std::max<std::int32_t>(1, std::min<std::int32_t>(100, maxConnections)));
  if (not allowedUpdates.empty())
    data.parts.emplace_back("allowed_updates", nl::json(allowedUpdates).dump());
  if (dropPendingUpdates)
    data.parts.emplace_back("drop_pending_updates", dropPendingUpdates);
  if (!secretToken.empty()) {
    data.parts.emplace_back("secret_token", secretToken);
  }
  return sendRequest("setWebhook", data);
}

Ptr<WebhookInfo> Api::getWebhookInfo() const {
  nl::json webhookInfoObj = sendRequest("getWebhookInfo");
  return makePtr<WebhookInfo>(webhookInfoObj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

Ptr<Message> Api::editMessageText(const std::string& text,
                                  const std::variant<std::int64_t, std::string>& chatId,
                                  std::int32_t messageId,
                                  const std::string& inlineMessageId,
                                  const std::string& parseMode,
                                  const std::vector<Ptr<MessageEntity>>& entities,
                                  bool disableWebPagePreview,
                                  const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  data.parts.emplace_back("text", text);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageText", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}

Ptr<Message> Api::editMessageCaption(const std::variant<std::int64_t, std::string>& chatId,
                                     std::int32_t messageId,
                                     const std::string& inlineMessageId,
                                     const std::string& caption,
                                     const std::string& parseMode,
                                     const std::vector<Ptr<MessageEntity>>& captionEntities,
                                     const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
  if (not caption.empty())
    data.parts.emplace_back("caption", caption);
  if (not parseMode.empty())
    data.parts.emplace_back("parse_mode", parseMode);
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("entities", entitiesArray.dump());
  }
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageCaption", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}


Ptr<Message> Api::editMessageMedia(const Ptr<InputMedia>& media,
                                   const std::variant<std::int64_t, std::string>& chatId,
                                   std::int32_t messageId,
                                   const std::string& inlineMessageId,
                                   const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("media", media->toJson().dump());
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageMedia", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}

Ptr<Message> Api::editMessageLiveLocation(float latitude,
                                          float longitude,
                                          const std::variant<std::int64_t, std::string>& chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          float horizontalAccuracy,
                                          std::int32_t heading,
                                          std::int32_t proximityAlertRadius,
                                          const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(9);
  data.parts.emplace_back("latitude", std::to_string(latitude));
  data.parts.emplace_back("longitude", std::to_string(longitude));
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
  if (horizontalAccuracy != 0.0f)
    data.parts.emplace_back("horizontal_accuracy", horizontalAccuracy);
  if (heading)
    data.parts.emplace_back("heading", heading);
  if (proximityAlertRadius)
    data.parts.emplace_back("proximity_alert_radius", proximityAlertRadius);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageLiveLocation", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}


Ptr<Message> Api::stopMessageLiveLocation(const std::variant<std::int64_t, std::string>& chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("stopMessageLiveLocation", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}


Ptr<Message> Api::editMessageReplyMarkup(const std::variant<std::int64_t, std::string>& chatId,
                                         std::int32_t messageId,
                                         const std::string& inlineMessageId,
                                         const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageReplyMarkup", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    return nullptr;
  }
}

Ptr<Poll> Api::stopPoll(const std::variant<std::int64_t, std::string>& chatId,
                        std::int32_t messageId,
                        const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json pollObj = sendRequest("stopPoll", data);
  Ptr<Poll> poll(new Poll(pollObj));
  return poll;
}

bool Api::deleteMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_id", messageId);
  return sendRequest("deleteMessage", data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
bool Api::answerInlineQuery(const std::string& inlineQueryId,
                            const std::vector<Ptr<InlineQueryResult>>& results,
                            std::int32_t cacheTime,
                            bool isPersonal,
                            const std::string& nextOffset,
                            const Ptr<InlineQueryResultsButton>& button) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("inline_query_id", inlineQueryId);
  nl::json resultsArray = nl::json::array();
  for (const Ptr<InlineQueryResult>& result: results)
    resultsArray.push_back(result->toJson());
  data.parts.emplace_back("results", resultsArray.dump());
  if (cacheTime)
    data.parts.emplace_back("cache_time", cacheTime);
  if (isPersonal)
    data.parts.emplace_back("is_personal", isPersonal);
  if (not nextOffset.empty())
    data.parts.emplace_back("next_offset", nextOffset);
  if (button)
    data.parts.emplace_back("button", button->toJson().dump());

  return sendRequest("answerInlineQuery", data);
}

Ptr<SentWebAppMessage> Api::answerWebAppQuery(const std::string& webAppQueryId, const Ptr<InlineQueryResult>& result) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("web_app_query_id", webAppQueryId);
  data.parts.emplace_back("result", result->toJson().dump());

  nl::json sendWebAppMsgObj = sendRequest("answerWebAppQuery", data);
  Ptr<SentWebAppMessage> ret(new SentWebAppMessage(sendWebAppMsgObj));
  return ret;
}


/////////////////////////////////////////////////////////////////////////////////////////////////

Ptr<Message> Api::sendSticker(const std::variant<std::int64_t, std::string>& chatId,
                              const std::variant<cpr::File, std::string>& sticker,
                              std::int32_t messageThreadId,
                              const std::string& emoji,
                              bool disableNotification,
                              bool protectContent,
                              const Ptr<tgbotxx::ReplyParameters>& replyParameters,
                              const Ptr<tgbotxx::IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  if (sticker.index() == 0) /* cpr::File */ {
    const cpr::File& file = std::get<cpr::File>(sticker);
    data.parts.emplace_back("sticker", cpr::Files{file});
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(sticker);
    data.parts.emplace_back("sticker", fileIdOrUrl);
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not emoji.empty())
    data.parts.emplace_back("emoji", emoji);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendSticker", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<StickerSet> Api::getStickerSet(const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("name", name);

  nl::json stickerSetObj = sendRequest("getStickerSet", data);
  Ptr<StickerSet> stickerSet(new StickerSet(stickerSetObj));
  return stickerSet;
}

std::vector<Ptr<Sticker>> Api::getCustomEmojiStickers(const std::vector<std::string>& customEmojiIds) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("custom_emoji_ids", nl::json(customEmojiIds).dump());
  nl::json stickersArray = sendRequest("getCustomEmojiStickers", data);

  std::vector<Ptr<Sticker>> result;
  result.reserve(stickersArray.size());
  for (const nl::json& stickerObj: stickersArray) {
    Ptr<Sticker> sticker = makePtr<Sticker>(stickerObj);
    result.push_back(std::move(sticker));
  }
  return result;
}

Ptr<File> Api::uploadStickerFile(std::int64_t userId,
                                 const cpr::File& sticker,
                                 const std::string& stickerFormat) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("sticker", cpr::Files{sticker});
  data.parts.emplace_back("sticker_format", stickerFormat);

  nl::json fileObj = sendRequest("uploadStickerFile", data);
  Ptr<File> file(new File(fileObj));
  return file;
}

bool Api::createNewStickerSet(std::int64_t userId,
                              const std::string& name,
                              const std::string& title,
                              const std::vector<Ptr<InputSticker>>& stickers,
                              const std::string& stickerFormat,
                              const std::string& stickerType,
                              bool needsRepainting) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("name", name);
  data.parts.emplace_back("title", title);
  nl::json stickersJson = nl::json::array();
  for (const Ptr<InputSticker>& inputSticker: stickers)
    stickersJson.push_back(inputSticker->toJson());
  data.parts.emplace_back("stickers", stickersJson.dump());
  data.parts.emplace_back("sticker_format", stickerFormat);
  data.parts.emplace_back("sticker_type", stickerType);
  if (needsRepainting)
    data.parts.emplace_back("needs_repainting", needsRepainting);

  return sendRequest("createNewStickerSet", data);
}

bool Api::addStickerToSet(std::int64_t userId,
                          const std::string& name,
                          const Ptr<tgbotxx::InputSticker>& sticker) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("name", name);
  data.parts.emplace_back("sticker", sticker->toJson().dump());
  return sendRequest("addStickerToSet", data);
}

bool Api::setStickerPositionInSet(const std::string& sticker, std::int32_t position) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("sticker", sticker);
  data.parts.emplace_back("position", position);
  return sendRequest("setStickerPositionInSet", data);
}

bool Api::deleteStickerFromSet(const std::string& sticker) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("sticker", sticker);
  return sendRequest("deleteStickerFromSet", data);
}

bool Api::setStickerEmojiList(const std::string& sticker, const std::vector<std::string>& emojiList) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("sticker", sticker);
  data.parts.emplace_back("emoji_list", nl::json(emojiList).dump());
  return sendRequest("setStickerEmojiList", data);
}

bool Api::setStickerKeywords(const std::string& sticker, const std::vector<std::string>& keywords) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("sticker", sticker);
  if (not keywords.empty()) {
    data.parts.emplace_back("keywords", nl::json(keywords).dump());
  }
  return sendRequest("setStickerKeywords", data);
}

bool Api::setStickerMaskPosition(const std::string& sticker,
                                 const Ptr<tgbotxx::MaskPosition>& maskPosition) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("sticker", sticker);
  if (maskPosition) {
    data.parts.emplace_back("mask_position", maskPosition->toJson().dump());
  }
  return sendRequest("setStickerMaskPosition", data);
}

bool Api::setStickerSetTitle(const std::string& name, const std::string& title) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("name", name);
  data.parts.emplace_back("title", title);
  return sendRequest("setStickerSetTitle", data);
}

bool Api::setStickerSetThumbnail(const std::string& name,
                                 const std::string& title,
                                 const std::optional<std::variant<cpr::File, std::string>>& thumbnail) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("name", name);
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
  return sendRequest("setStickerSetTitle", data);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Api::setUrl(const std::string& url) noexcept {
  m_apiUrl = url;
}
const std::string& Api::getUrl() const noexcept {
  return m_apiUrl;
}

void Api::setLongPollTimeout(const cpr::Timeout& longPollTimeout) {
  if (longPollTimeout.ms > m_timeout.ms)
    throw Exception("Api::setLongPollTimeout: Long poll timeout should always be shorter than api request timeout."
                    " Otherwise the api request will time out before long polling finishes.");
  m_longPollTimeout = longPollTimeout;
}
cpr::Timeout Api::getLongPollTimeout() const noexcept { return m_longPollTimeout; }

void Api::setConnectTimeout(const cpr::ConnectTimeout& timeout) noexcept {
  m_connectTimeout = timeout;
}
cpr::ConnectTimeout Api::getConnectTimeout() const noexcept { return m_connectTimeout; }

void Api::setTimeout(const cpr::Timeout& timeout) {
  if (timeout.ms <= m_longPollTimeout.ms)
    throw Exception("Api::setTimeout: Api request timeout should always be longer than long poll timeout."
                    " Otherwise the api request will time out before long polling finishes.");
  m_timeout = timeout;
}
cpr::Timeout Api::getTimeout() const noexcept { return m_timeout; }

void Api::setUploadFilesTimeout(const cpr::Timeout& timeout) noexcept {
  m_uploadFilesTimeout = timeout;
}
cpr::Timeout Api::getUploadFilesTimeout() const noexcept { return m_uploadFilesTimeout; }

void Api::setDownloadFilesTimeout(const cpr::Timeout& timeout) noexcept {
  m_downloadFilesTimeout = timeout;
}
cpr::Timeout Api::getDownloadFilesTimeout() const noexcept { return m_downloadFilesTimeout; }


/////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Message> Api::sendInvoice(const std::variant<std::int64_t, std::string>& chatId,
                              const std::string& title,
                              const std::string& description,
                              const std::string& payload,
                              const std::string& providerToken,
                              const std::string& currency,
                              const std::vector<Ptr<LabeledPrice>>& prices,
                              std::int32_t messageThreadId,
                              std::int32_t maxTipAmount,
                              const std::vector<std::int32_t>& suggestedTipAmounts,
                              const std::string& startParameter,
                              const std::string& providerData,
                              const std::string& photoUrl,
                              std::int32_t photoSize,
                              std::int32_t photoWidth,
                              std::int32_t photoHeight,
                              bool needName,
                              bool needPhoneNumber,
                              bool needEmail,
                              bool needShippingAddress,
                              bool sendPhoneNumberToProvider,
                              bool sendEmailToProvider,
                              bool isFlexible,
                              bool disableNotification,
                              bool protectContent,
                              std::int32_t replyToMessageId,
                              bool allowSendingWithoutReply,
                              const Ptr<IReplyMarkup>& replyMarkup) const {

  cpr::Multipart data{};
  data.parts.reserve(28);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.parts.emplace_back("chat_id", chatIdStr);
      }
      break;
    default:
      break;
  }
  data.parts.emplace_back("title", title);
  data.parts.emplace_back("description", description);
  data.parts.emplace_back("payload", payload);
  data.parts.emplace_back("provider_token", providerToken);
  data.parts.emplace_back("currency", currency);
  nl::json pricesJson = nl::json::array();
  for (const Ptr<LabeledPrice>& price: prices)
    pricesJson.push_back(price->toJson());
  data.parts.emplace_back("prices", pricesJson.dump());
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (maxTipAmount)
    data.parts.emplace_back("max_tip_amount", maxTipAmount);
  if (not suggestedTipAmounts.empty())
    data.parts.emplace_back("suggested_tip_amounts", nl::json(suggestedTipAmounts).dump());
  if (not startParameter.empty())
    data.parts.emplace_back("start_parameter", startParameter);
  if (not providerData.empty())
    data.parts.emplace_back("provider_data", providerData);
  if (not photoUrl.empty())
    data.parts.emplace_back("photo_url", photoUrl);
  if (photoSize)
    data.parts.emplace_back("photo_size", photoSize);
  if (photoWidth)
    data.parts.emplace_back("photo_width", photoWidth);
  if (photoHeight)
    data.parts.emplace_back("photo_height", photoHeight);
  if (needName)
    data.parts.emplace_back("need_name", needName);
  if (needPhoneNumber)
    data.parts.emplace_back("need_phone_number", needPhoneNumber);
  if (needEmail)
    data.parts.emplace_back("need_email", needEmail);
  if (needShippingAddress)
    data.parts.emplace_back("need_shipping_address", needShippingAddress);
  if (sendPhoneNumberToProvider)
    data.parts.emplace_back("send_phone_number_to_provider", sendPhoneNumberToProvider);
  if (sendEmailToProvider)
    data.parts.emplace_back("send_email_to_provider", sendEmailToProvider);
  if (isFlexible)
    data.parts.emplace_back("is_flexible", isFlexible);
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

  nl::json sentMessageObj = sendRequest("sendInvoice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}


std::string Api::createInvoiceLink(const std::string& title,
                                   const std::string& description,
                                   const std::string& payload,
                                   const std::string& providerToken,
                                   const std::string& currency,
                                   const std::vector<Ptr<LabeledPrice>>& prices,
                                   std::int32_t maxTipAmount,
                                   const std::vector<std::int32_t>& suggestedTipAmounts,
                                   const std::string& providerData,
                                   const std::string& photoUrl,
                                   std::int32_t photoSize,
                                   std::int32_t photoWidth,
                                   std::int32_t photoHeight,
                                   bool needName,
                                   bool needPhoneNumber,
                                   bool needEmail,
                                   bool needShippingAddress,
                                   bool sendPhoneNumberToProvider,
                                   bool sendEmailToProvider,
                                   bool isFlexible) const {

  cpr::Multipart data{};
  data.parts.reserve(20);
  data.parts.emplace_back("title", title);
  data.parts.emplace_back("description", description);
  data.parts.emplace_back("payload", payload);
  data.parts.emplace_back("provider_token", providerToken);
  data.parts.emplace_back("currency", currency);
  nl::json pricesJson = nl::json::array();
  for (const Ptr<LabeledPrice>& price: prices)
    pricesJson.push_back(price->toJson());
  data.parts.emplace_back("prices", pricesJson.dump());
  if (maxTipAmount)
    data.parts.emplace_back("max_tip_amount", maxTipAmount);
  if (not suggestedTipAmounts.empty())
    data.parts.emplace_back("suggested_tip_amounts", nl::json(suggestedTipAmounts).dump());
  if (not providerData.empty())
    data.parts.emplace_back("provider_data", providerData);
  if (not photoUrl.empty())
    data.parts.emplace_back("photo_url", photoUrl);
  if (photoSize)
    data.parts.emplace_back("photo_size", photoSize);
  if (photoWidth)
    data.parts.emplace_back("photo_width", photoWidth);
  if (photoHeight)
    data.parts.emplace_back("photo_height", photoHeight);
  if (needName)
    data.parts.emplace_back("need_name", needName);
  if (needPhoneNumber)
    data.parts.emplace_back("need_phone_number", needPhoneNumber);
  if (needEmail)
    data.parts.emplace_back("need_email", needEmail);
  if (needShippingAddress)
    data.parts.emplace_back("need_shipping_address", needShippingAddress);
  if (sendPhoneNumberToProvider)
    data.parts.emplace_back("send_phone_number_to_provider", sendPhoneNumberToProvider);
  if (sendEmailToProvider)
    data.parts.emplace_back("send_email_to_provider", sendEmailToProvider);
  if (isFlexible)
    data.parts.emplace_back("is_flexible", isFlexible);

  return sendRequest("createInvoiceLink", data);
}

bool Api::answerShippingQuery(const std::string& shippingQueryId,
                              bool ok,
                              const std::vector<Ptr<ShippingOption>>& shippingOptions,
                              const std::string& errorMessage) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("shipping_query_id", shippingQueryId);
  data.parts.emplace_back("ok", ok);
  if (not shippingOptions.empty()) {
    nl::json shippingOptionsJson = nl::json::array();
    for (const Ptr<ShippingOption>& opt: shippingOptions)
      shippingOptionsJson.push_back(opt->toJson());
    data.parts.emplace_back("shipping_options", shippingOptionsJson.dump());
  }
  if (not errorMessage.empty())
    data.parts.emplace_back("error_message", errorMessage);

  return sendRequest("answerShippingQuery", data);
}

bool Api::answerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                 bool ok,
                                 const std::string& errorMessage) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("pre_checkout_query_id", preCheckoutQueryId);
  data.parts.emplace_back("ok", ok);
  if (not errorMessage.empty())
    data.parts.emplace_back("error_message", errorMessage);

  return sendRequest("answerPreCheckoutQuery", data);
}
