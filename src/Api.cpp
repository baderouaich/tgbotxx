#include <chrono>
#include <tgbotxx/Api.hpp>
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
#include <tgbotxx/objects/ShippingAddress.hpp>
#include <tgbotxx/objects/ShippingQuery.hpp>
#include <tgbotxx/objects/Sticker.hpp>
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
const std::string Api::BASE_URL = "api.telegram.org";                                                          /// Telegram api base url. No https:// prefix because its how cpp-httplib's SSLClient wants its host to be like
const std::chrono::system_clock::duration Api::DEFAULT_CONNECT_TIMEOUT = std::chrono::milliseconds(20 * 1000); /// 20s (Telegram server can take up to 20s to connect with us)
const std::chrono::system_clock::duration Api::DEFAULT_TIMEOUT = std::chrono::seconds(60 + 10);                /// 70s (Telegram server can take up to 70s to reply us (should be longer than long poll timeout)).
const std::chrono::system_clock::duration Api::DEFAULT_LONG_POLL_TIMEOUT = std::chrono::seconds(60);           /// 60s (long polling getUpdates() every 30 seconds) Telegram's guidelines recommended a timeout between 30 and 90 seconds for long polling.
const std::chrono::system_clock::duration Api::DEFAULT_UPLOAD_FILES_TIMEOUT = std::chrono::seconds(15 * 60);   /// 15min (Files can take longer time to upload. Setting a shorter timeout will stop the request even if the file isn't fully uploaded)
const std::chrono::system_clock::duration Api::DEFAULT_DOWNLOAD_FILES_TIMEOUT = std::chrono::seconds(30 * 60); /// 30min (Files can take longer time to download. Setting a shorter timeout will stop the request even if the file isn't fully downloaded)

#ifdef __unix__
static const std::string& get_trusted_cert_path() {
  static std::string trustedCertPath;
  if (!trustedCertPath.empty()) {
    return trustedCertPath;
  }
  static const std::string trusted_certs_paths[] = {
    // "../ca-bundle.crt",
    "/etc/ssl/certs/ca-certificates.crt",                // Debian/Ubuntu/Gentoo
    "/etc/pki/tls/certs/ca-bundle.crt",                  // Fedora/RHEL 6
    "/etc/ssl/ca-bundle.pem",                            // OpenSUSE
    "/etc/pki/tls/cacert.pem",                           // OpenELEC
    "/etc/pki/ca-trust/extracted/pem/tls-ca-bundle.pem", // CentOS/RHEL 7
    "/etc/ssl/cert.pem",                                 // OpenBSD, Alpine
  };
  for (const auto& path: trusted_certs_paths) {
    if (access(path.c_str(), F_OK) == 0) {
      trustedCertPath = path;
      return trustedCertPath;
    }
  }
  throw Exception("Could not find trusted certs file in "
                  "any of the `system`-predefined locations. "
                  "Please install a certs file there.");
}
#endif // !__unix__

Api::Api(const std::string& token) : m_token(token) {}

nl::json Api::sendRequest(const std::string& endpoint, const httplib::MultipartFormDataItems& data) const {
  httplib::SSLClient session(BASE_URL); // Note: Why not have one session as a class member to use for all requests ?
                                        // You can initiate multiple concurrent requests to the Telegram API, which means
                                        // You can call sendMessage while getUpdates long polling is still pending, and you can't do that with a single http::SSLClient instance.
#ifdef __unix__
  session.set_ca_cert_path(get_trusted_cert_path());
  session.enable_server_certificate_verification(true);
#endif

  bool hasFiles = std::any_of(data.begin(), data.end(), [](const httplib::MultipartFormData& part) noexcept { return !part.filename.empty(); });
  bool isMultipart = not data.empty();

  session.set_connection_timeout(m_connectTimeout);
  session.set_read_timeout(hasFiles ? m_uploadFilesTimeout : m_timeout); // Files can take longer to upload
  //session.set_write_timeout();
  session.set_default_headers(httplib::Headers{
    {"Connection", "close"}, // disable keep-alive
    {"Accept", "application/json"},
    {"User-Agent", "tgbotxx/" TGBOTXX_VERSION},
    {"Content-Type", isMultipart ? "multipart/form-data" : "application/x-www-form-urlencoded"},
  });

  std::ostringstream path{};
  path << "/bot" << m_token << '/' << endpoint; // Note: token should have a prefix botTOKEN.
  httplib::Result res = isMultipart ? session.Post(path.str(), data) : session.Get(path.str());
  if (!res) [[unlikely]] {
    throw Exception(endpoint + ": Failed to send an HTTPS request to " + path.str() + ". Reason: " + httplib::to_string(res.error()));
  }
  if (res->status == 0) [[unlikely]] {
    throw Exception(endpoint + ": Failed to connect to Telegram API with status code: 0. Perhaps you are not connected to the internet?");
  }
  if (!res->body.compare(0, 6, "<html>")) [[unlikely]] {
    throw Exception(endpoint + ": Failed to get a JSON response from Telegram API. Did you enter the correct bot token?");
  }

  try {
    nl::json response = nl::json::parse(res->body);
    if (response["ok"].get<bool>()) {
      return response["result"];
    } else {
      std::string desc = response["description"];
      if (response["error_code"] == 404) {
        desc += ". Did you enter the correct bot token?";
      } else {
        desc += httplib::status_message(res->status);
      }
      throw Exception(desc);
    }
  } catch (const nl::json::exception& e) {
    throw Exception(endpoint + ": Failed to parse JSON response: " + res->body + "\nReason: " + e.what());
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
  httplib::MultipartFormDataItems data{};
  data.reserve(11);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back(/*name*/ "text", /*content*/ text, /*filename*/ "", /*content_type*/ "");

  //  std::string name;
  //  std::string content;
  //  std::string filename;
  //  std::string content_type;
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not entities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: entities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("entities", entitiesArray.dump());
  }
  if (disableWebPagePreview)
    data.emplace_back("disable_web_page_preview", std::to_string(disableWebPagePreview), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendMessage", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<MessageId> Api::copyMessage(const std::variant<std::int64_t, std::string>& chatId, const std::variant<std::int64_t, std::string>& fromChatId, std::int32_t messageId,
                                std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification,
                                bool protectContent, std::int32_t replyToMessageId, bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(12);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("from_chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId), "", "");
  data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json msgIdJson = sendRequest("copyMessage", data);
  Ptr<MessageId> messageIdObj(new MessageId(msgIdJson));
  return messageIdObj;
}

Ptr<Message> Api::forwardMessage(const std::variant<std::int64_t, std::string>& chatId, const std::variant<std::int64_t, std::string>& fromChatId, std::int32_t messageId, std::int32_t messageThreadId,
                                 bool disableNotification, bool protectContent) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(6);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("from_chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId), "", "");
  data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");

  nl::json sentMessageObj = sendRequest("sendMessage", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendPhoto(const std::variant<std::int64_t, std::string>& chatId, const std::variant<fs::path, std::string>& photo,
                            std::int32_t messageThreadId, const std::string& caption, const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities, bool disableNotification, bool protectContent,
                            std::int32_t replyToMessageId, bool allowSendingWithoutReply, const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(12);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (photo.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(photo);
    data.emplace_back("photo", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(photo);
    data.emplace_back("photo", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendPhoto", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendAudio(const std::variant<std::int64_t, std::string>& chatId,
                            std::variant<fs::path, std::string> audio,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::int32_t duration,
                            const std::string& performer,
                            const std::string& title,
                            std::optional<std::variant<fs::path, std::string>> thumbnail,
                            bool disableNotification,
                            bool protectContent,
                            std::int32_t replyToMessageId,
                            bool allowSendingWithoutReply,
                            const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(15);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (audio.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(audio);
    data.emplace_back("audio", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(audio);
    data.emplace_back("audio", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (duration)
    data.emplace_back("duration", std::to_string(duration), "", "");
  if (not performer.empty())
    data.emplace_back("performer", performer, "", "");
  if (not title.empty())
    data.emplace_back("title", title, "", "");
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* fs::path */ {
      const fs::path& file = std::get<fs::path>(*thumbnail);
      data.emplace_back("thumbnail", FileUtils::read(file), file.filename().string(), "application/octet-stream");
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.emplace_back("thumbnail", fileIdOrUrl, "", "");
    }
  }
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendAudio", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}
Ptr<Message> Api::sendDocument(const std::variant<std::int64_t, std::string>& chatId,
                               const std::variant<fs::path, std::string>& document,
                               std::int32_t messageThreadId,
                               std::optional<std::variant<fs::path, std::string>> thumbnail,
                               const std::string& caption,
                               const std::string& parseMode,
                               const std::vector<Ptr<MessageEntity>>& captionEntities,
                               bool disableNotification,
                               bool protectContent,
                               std::int32_t replyToMessageId,
                               bool allowSendingWithoutReply,
                               const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(12);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (document.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(document);
    data.emplace_back("document", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(document);
    data.emplace_back("document", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* fs::path */ {
      const fs::path& file = std::get<fs::path>(*thumbnail);
      data.emplace_back("thumbnail", FileUtils::read(file), file.filename().string(), "application/octet-stream");
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.emplace_back("thumbnail", fileIdOrUrl, "", "");
    }
  }
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendDocument", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<File> Api::getFile(const std::string& fileId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("file_id", fileId, "", "");
  nl::json fileObj = sendRequest("getFile", data);
  Ptr<File> file(new File(fileObj));
  return file;
}

std::string Api::downloadFile(const std::string& filePath) const {

  httplib::SSLClient session(BASE_URL);
#ifdef __unix__
  session.set_ca_cert_path(get_trusted_cert_path());
  session.enable_server_certificate_verification(true);
#endif
  session.set_connection_timeout(m_connectTimeout);
  session.set_read_timeout(m_downloadFilesTimeout); // Files can take longer to download
  session.set_compress(true);
  std::ostringstream path{};
  path << "/file/bot" << m_token << "/" << filePath;
  std::string buffer;
  auto res = session.Get(path.str(), [&](const char *data, std::size_t data_length) {
    buffer.append(data, data_length);
    return true;
  });
  if (!res) [[unlikely]] {
    throw Exception("Failed to download file " + filePath + ". Reason: " + httplib::to_string(res.error()));
  }
  if (res->status != 200)
    throw Exception("Failed to download file " + filePath + " with status code: " + httplib::status_message(res->status));

  return buffer;
}

Ptr<Message> Api::sendVideo(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<fs::path, std::string>& video,
                            std::int32_t messageThreadId,
                            std::int32_t duration,
                            std::int32_t width,
                            std::int32_t height,
                            std::optional<std::variant<fs::path, std::string>> thumbnail,
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
  httplib::MultipartFormDataItems data{};
  data.reserve(17);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (video.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(video);
    data.emplace_back("video", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(video);
    data.emplace_back("video", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (duration)
    data.emplace_back("duration", std::to_string(duration), "", "");
  if (width)
    data.emplace_back("width", std::to_string(width), "", "");
  if (height)
    data.emplace_back("height", std::to_string(height), "", "");
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* fs::path */ {
      const fs::path& file = std::get<fs::path>(*thumbnail);
      data.emplace_back("thumbnail", FileUtils::read(file), file.filename().string(), "application/octet-stream");
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.emplace_back("thumbnail", fileIdOrUrl, "", "");
    }
  }
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (hasSpoiler)
    data.emplace_back("has_spoiler", std::to_string(hasSpoiler), "", "");
  if (supportsStreaming)
    data.emplace_back("supports_streaming", std::to_string(supportsStreaming), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVideo", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendAnimation(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<fs::path, std::string>& animation,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t width,
                                std::int32_t height,
                                std::optional<std::variant<fs::path, std::string>> thumbnail,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities,
                                bool hasSpoiler,
                                bool disableNotification,
                                bool protectContent,
                                std::int32_t replyToMessageId,
                                bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(16);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (animation.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(animation);
    data.emplace_back("animation", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(animation);
    data.emplace_back("animation", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (duration)
    data.emplace_back("duration", std::to_string(duration), "", "");
  if (width)
    data.emplace_back("width", std::to_string(width), "", "");
  if (height)
    data.emplace_back("height", std::to_string(height), "", "");
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* fs::path */ {
      const fs::path& file = std::get<fs::path>(*thumbnail);
      data.emplace_back("thumbnail", FileUtils::read(file), file.filename().string(), "application/octet-stream");
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.emplace_back("thumbnail", fileIdOrUrl, "", "");
    }
  }
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (hasSpoiler)
    data.emplace_back("has_spoiler", std::to_string(hasSpoiler), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendAnimation", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendVoice(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<fs::path, std::string>& voice,
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
  httplib::MultipartFormDataItems data{};
  data.reserve(12);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (voice.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(voice);
    data.emplace_back("voice", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(voice);
    data.emplace_back("voice", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (duration)
    data.emplace_back("duration", std::to_string(duration), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendVoice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<Message> Api::sendVideoNote(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<fs::path, std::string>& videoNote,
                                std::int32_t messageThreadId,
                                std::int32_t duration,
                                std::int32_t length,
                                std::optional<std::variant<fs::path, std::string>> thumbnail,
                                bool disableNotification,
                                bool protectContent,
                                std::int32_t replyToMessageId,
                                bool allowSendingWithoutReply,
                                const Ptr<IReplyMarkup>& replyMarkup) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(11);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (videoNote.index() == 0) /* fs::path */ {
    const fs::path& file = std::get<fs::path>(videoNote);
    data.emplace_back("video_note", FileUtils::read(file), file.filename().string(), "application/octet-stream");
  } else /* std::string (fileId or Url) */ {
    const std::string& fileIdOrUrl = std::get<std::string>(videoNote);
    data.emplace_back("video_note", fileIdOrUrl, "", "");
  }
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (duration)
    data.emplace_back("duration", std::to_string(duration), "", "");
  if (length)
    data.emplace_back("length", std::to_string(duration), "", "");
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* fs::path */ {
      const fs::path& file = std::get<fs::path>(*thumbnail);
      data.emplace_back("thumbnail", FileUtils::read(file), file.filename().string(), "application/octet-stream");
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.emplace_back("thumbnail", fileIdOrUrl, "", "");
    }
  }
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(7);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (media.size() > 10 or media.size() < 2)
    throw Exception("Api::sendMediaGroup(): media must include 2-10 items. See https://core.telegram.org/bots/api#sendmediagroup");
  nl::json mediaJson = nl::json::array();
  for (const Ptr<InputMedia>& m: media)
    mediaJson.push_back(m->toJson());
  data.emplace_back("media", mediaJson.dump());
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");

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
  httplib::MultipartFormDataItems data{};
  data.reserve(13);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("latitude", std::to_string(latitude), "", "");
  data.emplace_back("longitude", std::to_string(longitude), "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (horizontalAccuracy != 0.0f)
    data.emplace_back("horizontal_accuracy", std::to_string(horizontalAccuracy), "", "");
  if (livePeriod)
    data.emplace_back("live_period", std::to_string(livePeriod), "", "");
  if (heading)
    data.emplace_back("heading", std::to_string(heading), "", "");
  if (proximityAlertRadius)
    data.emplace_back("proximity_alert_radius", std::to_string(proximityAlertRadius), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(15);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("latitude", std::to_string(latitude), "", "");
  data.emplace_back("longitude", std::to_string(longitude), "", "");
  data.emplace_back("title", title, "", "");
  data.emplace_back("address", address, "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not foursquareId.empty())
    data.emplace_back("foursquare_id", foursquareId, "", "");
  if (not foursquareType.empty())
    data.emplace_back("foursquare_type", foursquareType, "", "");
  if (not googlePlaceId.empty())
    data.emplace_back("google_place_id", googlePlaceId, "", "");
  if (not googlePlaceType.empty())
    data.emplace_back("google_place_type", googlePlaceType, "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(11);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("phone_number", phoneNumber, "", "");
  data.emplace_back("first_name", firstName, "", "");
  if (not lastName.empty())
    data.emplace_back("last_name", lastName, "", "");
  if (not vcard.empty())
    data.emplace_back("vcard", vcard, "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(19);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("question", question, "", "");
  data.emplace_back("options", nl::json(options).dump());
  if (not isAnonymous)
    data.emplace_back("is_anonymous", std::to_string(isAnonymous), "", "");
  if (not type.empty())
    data.emplace_back("type", type, "", "");
  if (allowsMultipleAnswers)
    data.emplace_back("allows_multiple_answers", std::to_string(allowsMultipleAnswers), "", "");
  if (correctOptionId >= 0)
    data.emplace_back("correct_option_id", std::to_string(correctOptionId), "", "");
  if (not explanation.empty())
    data.emplace_back("explanation", explanation, "", "");
  if (not explanationParseMode.empty())
    data.emplace_back("explanation_parse_mode", explanationParseMode, "", "");
  if (not explanationEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: explanationEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("explanation_entities", entitiesArray.dump());
  }
  if (openPeriod)
    data.emplace_back("open_period", std::to_string(openPeriod), "", "");
  if (closeDate)
    data.emplace_back("close_date", std::to_string(closeDate), "", "");
  if (isClosed)
    data.emplace_back("is_closed", std::to_string(isClosed), "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(8);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (not emoji.empty())
    data.emplace_back("emoji", emoji, "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  if (protectContent)
    data.emplace_back("protect_content", std::to_string(disableNotification), "", "");
  if (replyToMessageId)
    data.emplace_back("reply_to_message_id", std::to_string(replyToMessageId), "", "");
  if (allowSendingWithoutReply)
    data.emplace_back("allow_sending_without_reply", std::to_string(allowSendingWithoutReply), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json sentMessageObj = sendRequest("sendDice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

bool Api::sendChatAction(const std::variant<std::int64_t, std::string>& chatId,
                         const std::string& action,
                         std::int32_t messageThreadId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("action", action, "", "");
  if (messageThreadId)
    data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");

  return sendRequest("sendChatAction", data);
}

Ptr<UserProfilePhotos> Api::getUserProfilePhotos(std::int64_t userId,
                                                 std::int32_t offset,
                                                 std::int32_t limit) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("user_id", std::to_string(userId));
  if (offset)
    data.emplace_back("offset", std::to_string(offset), "", "");
  if (limit)
    data.emplace_back("limit", std::to_string(limit), "", "");

  nl::json userProfilePhotosObj = sendRequest("getUserProfilePhotos", data);
  Ptr<UserProfilePhotos> userProfilePhotos(new UserProfilePhotos(userProfilePhotosObj));
  return userProfilePhotos;
}

bool Api::banChatMember(const std::variant<std::int64_t, std::string>& chatId,
                        std::int64_t userId,
                        std::time_t untilDate,
                        bool revokeMessages) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(4);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  if (untilDate)
    data.emplace_back("until_date", std::to_string(untilDate), "", "");
  if (revokeMessages)
    data.emplace_back("revoke_messages", std::to_string(revokeMessages), "", "");

  return sendRequest("banChatMember", data);
}

bool Api::unbanChatMember(const std::variant<std::int64_t, std::string>& chatId,
                          std::int64_t userId,
                          bool onlyIfBanned) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  if (onlyIfBanned)
    data.emplace_back("only_if_banned", std::to_string(onlyIfBanned), "", "");

  return sendRequest("unbanChatMember", data);
}

bool Api::restrictChatMember(const std::variant<std::int64_t, std::string>& chatId,
                             std::int64_t userId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions,
                             std::time_t untilDate) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(5);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  data.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.emplace_back("use_independent_chat_permissions", std::to_string(useIndependentChatPermissions), "", "");
  if (untilDate)
    data.emplace_back("until_date", std::to_string(untilDate), "", "");

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
  httplib::MultipartFormDataItems data{};
  data.reserve(17);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  if (isAnonymous)
    data.emplace_back("is_anonymous", std::to_string(isAnonymous), "", "");
  if (canManageChat)
    data.emplace_back("can_manage_chat", std::to_string(canManageChat), "", "");
  if (canDeleteMessages)
    data.emplace_back("can_delete_messages", std::to_string(canDeleteMessages), "", "");
  if (canManageVideoChats)
    data.emplace_back("can_manage_video_chats", std::to_string(canManageVideoChats), "", "");
  if (canRestrictMembers)
    data.emplace_back("can_restrict_members", std::to_string(canRestrictMembers), "", "");
  if (canPromoteMembers)
    data.emplace_back("can_promote_members", std::to_string(canPromoteMembers), "", "");
  if (canChangeInfo)
    data.emplace_back("can_change_info", std::to_string(canChangeInfo), "", "");
  if (canInviteUsers)
    data.emplace_back("can_invite_users", std::to_string(canInviteUsers), "", "");
  if (canPostMessages)
    data.emplace_back("can_post_messages", std::to_string(canPostMessages), "", "");
  if (canEditMessages)
    data.emplace_back("can_edit_messages", std::to_string(canEditMessages), "", "");
  if (canPinMessages)
    data.emplace_back("can_pin_messages", std::to_string(canPinMessages), "", "");
  if (canPostStories)
    data.emplace_back("can_post_stories", std::to_string(canPostStories), "", "");
  if (canEditStories)
    data.emplace_back("can_edit_stories", std::to_string(canEditStories), "", "");
  if (canDeleteStories)
    data.emplace_back("can_delete_stories", std::to_string(canDeleteStories), "", "");
  if (canManageTopics)
    data.emplace_back("can_manage_topics", std::to_string(canManageTopics), "", "");
  return sendRequest("promoteChatMember", data);
}

bool Api::setChatAdministratorCustomTitle(const std::variant<std::int64_t, std::string>& chatId,
                                          std::int64_t userId,
                                          const std::string& customTitle) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  data.emplace_back("custom_title", customTitle, "", "");
  return sendRequest("setChatAdministratorCustomTitle", data);
}

bool Api::banChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                            std::int64_t senderChatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("banChatSenderChat", data);
}

bool Api::unbanChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                              std::int64_t senderChatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("sender_chat_id", std::to_string(senderChatId));
  return sendRequest("unbanChatSenderChat", data);
}

bool Api::setChatPermissions(const std::variant<std::int64_t, std::string>& chatId,
                             const Ptr<ChatPermissions>& permissions,
                             bool useIndependentChatPermissions) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("permissions", permissions->toJson().dump());
  if (useIndependentChatPermissions)
    data.emplace_back("use_independent_chat_permissions", std::to_string(useIndependentChatPermissions), "", "");
  return sendRequest("setChatPermissions", data);
}

std::string Api::exportChatInviteLink(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("exportChatInviteLink", data);
}

Ptr<ChatInviteLink> Api::createChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::string& name,
                                              std::time_t expireDate,
                                              std::int32_t memberLimit,
                                              bool createsJoinRequest) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(5);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (not name.empty())
    data.emplace_back("name", name, "", "");
  if (expireDate)
    data.emplace_back("expire_date", std::to_string(expireDate), "", "");
  if (memberLimit)
    data.emplace_back("member_limit", std::to_string(memberLimit), "", "");
  if (createsJoinRequest)
    data.emplace_back("creates_join_request", std::to_string(createsJoinRequest), "", "");

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
  httplib::MultipartFormDataItems data{};
  data.reserve(6);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("invite_link", inviteLink, "", "");
  if (not name.empty())
    data.emplace_back("name", name, "", "");
  if (expireDate)
    data.emplace_back("expire_date", std::to_string(expireDate), "", "");
  if (memberLimit)
    data.emplace_back("member_limit", std::to_string(memberLimit), "", "");
  if (createsJoinRequest)
    data.emplace_back("creates_join_request", std::to_string(createsJoinRequest), "", "");

  nl::json chatInviteLinkObj = sendRequest("editChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::revokeChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::string& inviteLink) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("invite_link", inviteLink, "", "");

  nl::json chatInviteLinkObj = sendRequest("revokeChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

bool Api::approveChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  return sendRequest("approveChatJoinRequest", data);
}

bool Api::declineChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));
  return sendRequest("declineChatJoinRequest", data);
}

bool Api::setChatPhoto(const std::variant<std::int64_t, std::string>& chatId, const fs::path& photo) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("photo", FileUtils::read(photo), photo.filename().string(), "application/octet-stream");
  return sendRequest("setChatPhoto", data);
}

bool Api::deleteChatPhoto(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("deleteChatPhoto", data);
}

bool Api::setChatTitle(const std::variant<std::int64_t, std::string>& chatId, const std::string& title) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("title", title, "", "");
  return sendRequest("setChatTitle", data);
}

bool Api::setChatDescription(const std::variant<std::int64_t, std::string>& chatId, const std::string& description) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (not description.empty())
    data.emplace_back("description", description, "", "");
  return sendRequest("setChatDescription", data);
}

bool Api::pinChatMessage(const std::variant<std::int64_t, std::string>& chatId,
                         std::int32_t messageId,
                         bool disableNotification) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (disableNotification)
    data.emplace_back("disable_notification", std::to_string(disableNotification), "", "");
  return sendRequest("pinChatMessage", data);
}

bool Api::unpinChatMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  return sendRequest("unpinChatMessage", data);
}

bool Api::unpinAllChatMessages(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("unpinAllChatMessages", data);
}


bool Api::leaveChat(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("leaveChat", data);
}

Ptr<Chat> Api::getChat(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");

  nl::json chatObj = sendRequest("getChat", data);
  Ptr<Chat> chat(new Chat(chatObj));
  return chat;
}

std::vector<Ptr<ChatMember>> Api::getChatAdministrators(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");

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
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("getChatMemberCount", data);
}

Ptr<ChatMember> Api::getChatMember(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("user_id", std::to_string(userId));

  nl::json chatMemberObj = sendRequest("getChatMember", data);
  Ptr<ChatMember> chatMember(new ChatMember(chatMemberObj));
  return chatMember;
}

bool Api::setChatStickerSet(const std::variant<std::int64_t, std::string>& chatId, const std::string& stickerSetName) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("sticker_set_name", stickerSetName, "", "");
  return sendRequest("setChatStickerSet", data);
}

bool Api::deleteChatStickerSet(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
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
  httplib::MultipartFormDataItems data{};
  data.reserve(4);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("name", name, "", "");
  if (iconColor)
    data.emplace_back("icon_color", std::to_string(iconColor), "", "");
  if (not iconCustomEmojiId.empty())
    data.emplace_back("icon_custom_emoji_id", iconCustomEmojiId, "", "");

  nl::json forumTopicObj = sendRequest("createForumTopic", data);
  Ptr<ForumTopic> forumTopic(new ForumTopic(forumTopicObj));
  return forumTopic;
}

bool Api::editForumTopic(const std::variant<std::int64_t, std::string>& chatId,
                         std::int32_t messageThreadId,
                         const std::string& name,
                         const std::optional<std::string>& iconCustomEmojiId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(4);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  if (not name.empty())
    data.emplace_back("name", name, "", "");
  if (iconCustomEmojiId.has_value()) {
    data.emplace_back("icon_custom_emoji_id", *iconCustomEmojiId);
  }
  return sendRequest("editForumTopic", data);
}

bool Api::closeForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  return sendRequest("closeForumTopic", data);
}

bool Api::reopenForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  return sendRequest("reopenForumTopic", data);
}

bool Api::deleteForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  return sendRequest("deleteForumTopic", data);
}

bool Api::unpinAllForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_thread_id", std::to_string(messageThreadId), "", "");
  return sendRequest("unpinAllForumTopicMessages", data);
}

bool Api::editGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId, const std::string& name) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("name", name, "", "");
  return sendRequest("editGeneralForumTopic", data);
}

bool Api::closeGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("closeGeneralForumTopic", data);
}

bool Api::reopenGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("reopenGeneralForumTopic", data);
}

bool Api::hideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("hideGeneralForumTopic", data);
}

bool Api::unhideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("unhideGeneralForumTopic", data);
}

bool Api::unpinAllGeneralForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  return sendRequest("unpinAllGeneralForumTopicMessages", data);
}

bool Api::answerCallbackQuery(const std::string& callbackQueryId,
                              const std::string& text,
                              bool showAlert,
                              const std::string& url,
                              std::int32_t cacheTime) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(5);
  data.emplace_back("callback_query_id", callbackQueryId, "", "");
  if (not text.empty())
    data.emplace_back("text", text, "", "");
  if (showAlert)
    data.emplace_back("show_alert", std::to_string(showAlert), "", "");
  if (not url.empty())
    data.emplace_back("url", url, "", "");
  if (cacheTime)
    data.emplace_back("cache_time", std::to_string(cacheTime), "", "");
  return sendRequest("answerCallbackQuery", data);
}

bool Api::setMyCommands(const std::vector<Ptr<BotCommand>>& commands,
                        const Ptr<BotCommandScope>& scope,
                        const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(3);

  nl::json commandsJson = nl::json::array();
  for (const Ptr<BotCommand>& command: commands)
    commandsJson.push_back(command->toJson());
  data.emplace_back("commands", commandsJson.dump());
  if (scope)
    data.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");


  return sendRequest("setMyCommands", data);
}

bool Api::deleteMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (scope)
    data.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");
  return sendRequest("deleteMyCommands", data);
}

std::vector<Ptr<BotCommand>> Api::getMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  std::vector<Ptr<BotCommand>> commands;
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (scope)
    data.emplace_back("scope", scope->toJson().dump());
  else {
    auto defScope = makePtr<BotCommandScopeDefault>();
    data.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");

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
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (not name.empty())
    data.emplace_back("name", name, "", "");
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");
  return sendRequest("setMyName", data);
}

Ptr<BotName> Api::getMyName(const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");

  nl::json botNameObj = sendRequest("getMyName", data);
  ;
  return makePtr<BotName>(botNameObj);
}

bool Api::setMyDescription(const std::string& description, const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (not description.empty())
    data.emplace_back("description", description, "", "");
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");
  return sendRequest("setMyDescription", data);
}

Ptr<BotDescription> Api::getMyDescription(const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");

  nl::json botDescObj = sendRequest("getMyDescription", data);
  ;
  return makePtr<BotDescription>(botDescObj);
}

bool Api::setMyShortDescription(const std::string& shortDescription, const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (not shortDescription.empty())
    data.emplace_back("short_description", shortDescription, "", "");
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");
  return sendRequest("setMyShortDescription", data);
}

Ptr<BotShortDescription> Api::getMyShortDescription(const std::string& languageCode) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  if (not languageCode.empty())
    data.emplace_back("language_code", languageCode, "", "");

  nl::json botShortDescObj = sendRequest("getMyShortDescription", data);
  return makePtr<BotShortDescription>(botShortDescObj);
}

bool Api::setChatMenuButton(const std::variant<std::int64_t, std::string>& chatId, const Ptr<tgbotxx::MenuButton>& menuButton) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  std::string chatIdStr = chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId);
  if (not chatIdStr.empty())
    data.emplace_back("chat_id", chatIdStr, "", "");
  if (menuButton)
    data.emplace_back("menu_button", menuButton->toJson().dump());
  else {
    auto defMenuButton = makePtr<MenuButtonDefault>();
    data.emplace_back("menu_button", defMenuButton->toJson().dump());
  }
  return sendRequest("setChatMenuButton", data);
}

Ptr<MenuButton> Api::getChatMenuButton(const std::variant<std::int64_t, std::string>& chatId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  std::string chatIdStr = chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId);
  if (not chatIdStr.empty())
    data.emplace_back("chat_id", chatIdStr, "", "");
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
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  if (rights)
    data.emplace_back("rights", rights->toJson().dump());
  if (forChannels)
    data.emplace_back("for_channels", std::to_string(forChannels), "", "");
  return sendRequest("setMyDefaultAdministratorRights", data);
}

Ptr<ChatAdministratorRights> Api::getMyDefaultAdministratorRights(bool forChannels) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  if (forChannels)
    data.emplace_back("for_channels", std::to_string(forChannels), "", "");
  nl::json chatAdministratorRightsObj = sendRequest("getMyDefaultAdministratorRights", data);
  return makePtr<ChatAdministratorRights>(chatAdministratorRightsObj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Api::deleteWebhook(bool dropPendingUpdates) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(1);
  if (dropPendingUpdates)
    data.emplace_back("drop_pending_updates", std::to_string(dropPendingUpdates), "", "");
  return sendRequest("deleteWebhook", data);
}

/// Called every LONG_POOL_TIMEOUT seconds
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, const std::vector<std::string>& allowedUpdates) const {
  std::vector<Ptr<Update>> updates;
  httplib::MultipartFormDataItems data = {
    {"offset", std::to_string(offset), "", ""},
    {"limit", std::to_string(std::max<std::int32_t>(1, std::min<std::int32_t>(100, limit))), "", ""},
    {"timeout", std::to_string(static_cast<std::int32_t>(std::chrono::duration_cast<std::chrono::seconds>(m_longPollTimeout).count())), "", ""},
    {"allowed_updates", nl::json(allowedUpdates).dump(), "", ""},
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
                     const std::optional<fs::path>& certificate,
                     const std::string& ipAddress,
                     std::int32_t maxConnections,
                     const std::vector<std::string>& allowedUpdates,
                     bool dropPendingUpdates,
                     const std::string& secretToken) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(7);
  data.emplace_back("url", url, "", "");
  if (certificate.has_value())
    data.emplace_back("certificate", FileUtils::read(*certificate), certificate->filename().string(), "application/octet-stream");
  if (not ipAddress.empty())
    data.emplace_back("ip_address", ipAddress, "", "");
  if (maxConnections != 40)
    data.emplace_back("max_connections", std::to_string(std::max<std::int32_t>(1, std::min<std::int32_t>(100, maxConnections))));
  if (not allowedUpdates.empty())
    data.emplace_back("allowed_updates", nl::json(allowedUpdates).dump());
  if (dropPendingUpdates)
    data.emplace_back("drop_pending_updates", std::to_string(dropPendingUpdates), "", "");
  if (!secretToken.empty()) {
    data.emplace_back("secret_token", secretToken, "", "");
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
  httplib::MultipartFormDataItems data{};
  data.reserve(8);
  data.emplace_back("text", text, "", "");
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not entities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: entities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("entities", entitiesArray.dump());
  }
  if (disableWebPagePreview)
    data.emplace_back("disable_web_page_preview", std::to_string(disableWebPagePreview), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(7);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (not caption.empty())
    data.emplace_back("caption", caption, "", "");
  if (not parseMode.empty())
    data.emplace_back("parse_mode", parseMode, "", "");
  if (not captionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: captionEntities)
      entitiesArray.push_back(entity->toJson());
    data.emplace_back("entities", entitiesArray.dump());
  }
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(5);
  data.emplace_back("media", media->toJson().dump());
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(9);
  data.emplace_back("latitude", std::to_string(latitude), "", "");
  data.emplace_back("longitude", std::to_string(longitude), "", "");
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (horizontalAccuracy != 0.0f)
    data.emplace_back("horizontal_accuracy", std::to_string(horizontalAccuracy), "", "");
  if (heading)
    data.emplace_back("heading", std::to_string(heading), "", "");
  if (proximityAlertRadius)
    data.emplace_back("proximity_alert_radius", std::to_string(proximityAlertRadius), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(4);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(4);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
        data.emplace_back("chat_id", chatIdStr, "", "");
      }
      break;
    default:
      break;
  }
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (not inlineMessageId.empty())
    data.emplace_back("inline_message_id", inlineMessageId, "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

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
  httplib::MultipartFormDataItems data{};
  data.reserve(3);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  if (messageId)
    data.emplace_back("message_id", std::to_string(messageId), "", "");
  if (replyMarkup)
    data.emplace_back("reply_markup", replyMarkup->toJson().dump());

  nl::json pollObj = sendRequest("stopPoll", data);
  Ptr<Poll> poll(new Poll(pollObj));
  return poll;
}

bool Api::deleteMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(2);
  data.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId), "", "");
  data.emplace_back("message_id", std::to_string(messageId), "", "");
  return sendRequest("deleteMessage", data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
bool Api::answerInlineQuery(const std::string& inlineQueryId,
                            const std::vector<Ptr<InlineQueryResult>>& results,
                            std::int32_t cacheTime,
                            bool isPersonal,
                            const std::string& nextOffset,
                            const Ptr<InlineQueryResultsButton>& button) const {
  httplib::MultipartFormDataItems data{};
  data.reserve(6);
  data.emplace_back("inline_query_id", inlineQueryId, "", "");
  nl::json resultsArray = nl::json::array();
  for (const Ptr<InlineQueryResult>& result: results)
    resultsArray.push_back(result->toJson());
  data.emplace_back("results", resultsArray.dump());
  if (cacheTime != 300)
    data.emplace_back("cache_time", std::to_string(cacheTime), "", "");
  if (isPersonal)
    data.emplace_back("is_personal", std::to_string(isPersonal), "", "");
  if (not nextOffset.empty())
    data.emplace_back("next_offset", nextOffset, "", "");
  if (button)
    data.emplace_back("button", button->toJson().dump());

  return sendRequest("answerInlineQuery", data);
}

void Api::setLongPollTimeout(const std::chrono::system_clock::duration& longPollTimeout) {
  if (longPollTimeout > m_timeout)
    throw Exception("Api::setLongPollTimeout: Long poll timeout should always be shorter than api request timeout."
                    " Otherwise the api request will time out before long polling finishes.");
  m_longPollTimeout = longPollTimeout;
}
std::chrono::system_clock::duration Api::getLongPollTimeout() const noexcept { return m_longPollTimeout; }

void Api::setConnectTimeout(const std::chrono::system_clock::duration& timeout) noexcept {
  m_connectTimeout = timeout;
}
std::chrono::system_clock::duration Api::getConnectTimeout() const noexcept { return m_connectTimeout; }

void Api::setTimeout(const std::chrono::system_clock::duration& timeout) {
  if (timeout <= m_longPollTimeout)
    throw Exception("Api::setTimeout: Api request timeout should always be longer than long poll timeout."
                    " Otherwise the api request will time out before long polling finishes.");
  m_timeout = timeout;
}
std::chrono::system_clock::duration Api::getTimeout() const noexcept { return m_timeout; }

void Api::setUploadFilesTimeout(const std::chrono::system_clock::duration& timeout) noexcept {
  m_uploadFilesTimeout = timeout;
}
std::chrono::system_clock::duration Api::getUploadFilesTimeout() const noexcept { return m_uploadFilesTimeout; }

void Api::setDownloadFilesTimeout(const std::chrono::system_clock::duration& timeout) noexcept {
  m_downloadFilesTimeout = timeout;
}
std::chrono::system_clock::duration Api::getDownloadFilesTimeout() const noexcept { return m_downloadFilesTimeout; }