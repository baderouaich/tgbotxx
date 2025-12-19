#include <chrono>
#include <memory>
#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
#include <utility>
#include <ranges>
/// Objects
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <tgbotxx/objects/BotDescription.hpp>
#include <tgbotxx/objects/BotName.hpp>
#include <tgbotxx/objects/BotShortDescription.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>
#include <tgbotxx/objects/ChatInviteLink.hpp>
#include <tgbotxx/objects/ChatMember.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/File.hpp>
#include <tgbotxx/objects/ForumTopic.hpp>
#include <tgbotxx/objects/GameHighScore.hpp>
#include <tgbotxx/objects/IReplyMarkup.hpp>
#include <tgbotxx/objects/InlineQueryResult.hpp>
#include <tgbotxx/objects/InlineQueryResultsButton.hpp>
#include <tgbotxx/objects/InputMedia.hpp>
#include <tgbotxx/objects/InputSticker.hpp>
#include <tgbotxx/objects/LabeledPrice.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/MenuButton.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/MessageId.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PassportElementError.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/InputPollOption.hpp>
#include <tgbotxx/objects/ReactionType.hpp>
#include <tgbotxx/objects/ReplyParameters.hpp>
#include <tgbotxx/objects/SentWebAppMessage.hpp>
#include <tgbotxx/objects/ShippingOption.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/StickerSet.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/UserProfilePhotos.hpp>
#include <tgbotxx/objects/WebhookInfo.hpp>
#include <tgbotxx/objects/LinkPreviewOptions.hpp>
#include <tgbotxx/objects/SuggestedPostParameters.hpp>
#include <tgbotxx/objects/InputChecklist.hpp>
#include <tgbotxx/objects/UserChatBoosts.hpp>
#include <tgbotxx/objects/Gifts.hpp>
#include <tgbotxx/objects/InputProfilePhoto.hpp>
#include <tgbotxx/objects/AcceptedGiftTypes.hpp>
#include <tgbotxx/objects/StarAmount.hpp>
#include <tgbotxx/objects/OwnedGifts.hpp>
#include <tgbotxx/objects/InputStoryContent.hpp>
#include <tgbotxx/objects/Story.hpp>
#include <tgbotxx/objects/StoryArea.hpp>
#include <tgbotxx/objects/StarTransactions.hpp>
#include <tgbotxx/objects/InputPaidMedia.hpp>

using namespace tgbotxx;

/// Static declarations
const std::string Api::DEFAULT_API_URL = "https://api.telegram.org";                           /// Telegram Api Url (Use api()->setUrl("http..") to set your self-hosted url)
const cpr::ConnectTimeout Api::DEFAULT_CONNECT_TIMEOUT = std::chrono::milliseconds(20 * 1000); /// 20s (Telegram server can take up to 20s to connect with us)
const cpr::Timeout Api::DEFAULT_TIMEOUT = std::chrono::seconds(60 + 10);                       /// 70s (Telegram server can take up to 70s to reply us (should be longer than long poll timeout)).
const cpr::Timeout Api::DEFAULT_LONG_POLL_TIMEOUT = std::chrono::seconds(60);                  /// 60s (long polling getUpdates() every 60 seconds) Telegram's guidelines recommended a timeout between 30 and 90 seconds for long polling.
const cpr::Timeout Api::DEFAULT_UPLOAD_FILES_TIMEOUT = std::chrono::seconds(15 * 60);          /// 15min (Files can take longer time to upload. Setting a shorter timeout will stop the request even if the file isn't fully uploaded)
const cpr::Timeout Api::DEFAULT_DOWNLOAD_FILES_TIMEOUT = std::chrono::seconds(30 * 60);        /// 30min (Files can take longer time to download. Setting a shorter timeout will stop the request even if the file isn't fully downloaded)

void Api::Cache::refresh(const Api *api) {
  // Cache Bot's username & commands
  botUsername = api->getMe()->username;
  if (const auto cmds = api->getMyCommands(); !cmds.empty()) {
    botCommands.reserve(cmds.size());
    for (const auto& cmd: cmds) {
      botCommands.push_back(cmd->command);
    }
  }
}

Api::Api(const std::string& token) : m_token(token) {
  m_cache.refresh(this);
}

nl::json Api::sendRequest(const std::string& endpoint, const cpr::Multipart& data, const std::shared_ptr<std::atomic<bool>>& cancellationParam) const {
  cpr::Session session{}; // Note: Why not have one session as a class member to use for all requests ?
                          // You can initiate multiple concurrent requests to the Telegram API, which means
                          // You can call sendMessage while getUpdates long polling is still pending, and you can't do that with a single cpr::Session instance.

  if (cancellationParam) {
    session.SetCancellationParam(cancellationParam);
  }

  const bool hasFiles = std::ranges::any_of(data.parts, [](const cpr::Part& part) noexcept { return part.is_file; });
  session.SetProxies(m_proxies);
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
  const bool isMultipart = not data.parts.empty();
  if (isMultipart) {
    session.SetMultipart(data);
    session.UpdateHeader(cpr::Header{{{"Content-Type", "multipart/form-data"}}});
  }

  const cpr::Response res = isMultipart ? session.Post() : session.Get();
  if (res.error) [[unlikely]] {
    throw Exception(endpoint + ": " + res.error.message, (res.error.code == cpr::ErrorCode::ABORTED_BY_CALLBACK) ? ErrorCode::REQUEST_CANCELLED : ErrorCode::OTHER);
  }
  if (res.status_code == 0) [[unlikely]] {
    throw Exception(endpoint + ": Failed to connect to Telegram API with status code: 0. Perhaps you are not connected to the internet?", ErrorCode::OTHER);
  }
  if (!res.text.compare(0, 6, "<html>")) [[unlikely]] {
    throw Exception(endpoint + ": Failed to get a JSON response from Telegram API. Did you enter the correct bot token?", ErrorCode::OTHER);
  }

  try {
    const nl::json response = nl::json::parse(res.text);
    if (response["ok"].get<bool>()) {
      return response["result"];
    } else {
      std::string desc = response["description"];
      const std::int32_t errorCode = response["error_code"];
      if (errorCode == cpr::status::HTTP_NOT_FOUND) {
        desc += ". Did you enter the correct bot token?";
      }
      throw Exception(desc, static_cast<ErrorCode>(errorCode));
    }
  } catch (const nl::json::exception& e) {
    throw Exception(endpoint + ": Failed to parse JSON response: " + res.text + "\nreason: " + e.what());
  } catch (const Exception&) {
    throw; // rethrow Exception
  } catch (const std::exception&) {
    throw; // rethrow std::exception
  }
}

Ptr<User> Api::getMe() const {
  nl::json json = sendRequest("getMe");
  Ptr<User> me(new User(json));
  // Cache Bot's username
  m_cache.botUsername = me->username;
  return me;
}

bool Api::logOut() const {
  return sendRequest("logOut");
}

bool Api::close() const {
  return sendRequest("close");
}

Ptr<Message> Api::sendMessage(const std::variant<std::int64_t, std::string>& chatId,
                              const std::string& text,
                              std::int32_t messageThreadId,
                              const std::string& parseMode,
                              const std::vector<Ptr<MessageEntity>>& entities,
                              bool disableNotification,
                              bool protectContent,
                              const Ptr<IReplyMarkup>& replyMarkup,
                              const std::string& businessConnectionId,
                              std::int32_t directMessagesTopicId,
                              const Ptr<LinkPreviewOptions>& linkPreviewOptions,
                              bool allowPaidBroadcast,
                              const std::string& messageEffectId,
                              const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                              const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
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
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (linkPreviewOptions)
    data.parts.emplace_back("link_preview_options", linkPreviewOptions->toJson().dump());
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendMessage", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::forwardMessage(const std::variant<std::int64_t, std::string>& chatId,
                                 const std::variant<std::int64_t, std::string>& fromChatId,
                                 std::int32_t messageId,
                                 std::int32_t messageThreadId,
                                 bool disableNotification,
                                 bool protectContent,
                                 std::int32_t directMessagesTopicId,
                                 std::time_t videoStartTimestamp,
                                 const Ptr<SuggestedPostParameters>& suggestedPostParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));                  // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", fromChatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("message_id", messageId);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (videoStartTimestamp)
    data.parts.emplace_back("video_start_timestamp", videoStartTimestamp);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());

  const nl::json fwdMsgObj = sendRequest("forwardMessage", data);
  Ptr<Message> message(new Message(fwdMsgObj));
  return message;
}

std::vector<Ptr<MessageId>> Api::forwardMessages(const std::variant<std::int64_t, std::string>& chatId,
                                                 const std::variant<std::int64_t, std::string>& fromChatId,
                                                 const std::vector<std::int32_t>& messageIds,
                                                 std::int32_t messageThreadId,
                                                 bool disableNotification,
                                                 bool protectContent,
                                                 std::int32_t directMessagesTopicId) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));                  // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", fromChatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("message_ids", nl::json(messageIds).dump());
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);

  const nl::json msgIds = sendRequest("forwardMessages", data);
  std::vector<Ptr<MessageId>> ret;
  ret.reserve(msgIds.size());
  for (const nl::json& msgIdObj: msgIds) {
    Ptr<MessageId> msgId(new MessageId(msgIdObj));
    ret.emplace_back(std::move(msgId));
  }
  return ret;
}

Ptr<MessageId> Api::copyMessage(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<std::int64_t, std::string>& fromChatId,
                                std::int32_t messageId,
                                std::int32_t messageThreadId,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities,
                                bool disableNotification,
                                bool protectContent,
                                const Ptr<IReplyMarkup>& replyMarkup,
                                std::int32_t directMessagesTopicId,
                                std::time_t videoStartTimestamp,
                                bool showCaptionAboveMedia,
                                bool allowPaidBroadcast,
                                const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                                const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(18);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));                  // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", fromChatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (videoStartTimestamp)
    data.parts.emplace_back("video_start_timestamp", videoStartTimestamp);
  if (showCaptionAboveMedia)
    data.parts.emplace_back("show_caption_above_media", showCaptionAboveMedia);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json msgIdJson = sendRequest("copyMessage", data);
  Ptr<MessageId> messageIdObj(new MessageId(msgIdJson));
  return messageIdObj;
}

std::vector<Ptr<MessageId>> Api::copyMessages(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::variant<std::int64_t, std::string>& fromChatId,
                                              const std::vector<std::int32_t>& messageIds,
                                              std::int32_t messageThreadId,
                                              std::int32_t directMessagesTopicId,
                                              bool disableNotification,
                                              bool protectContent,
                                              bool removeCaption) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));                  // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("from_chat_id", fromChatId.index() == 0 ? std::to_string(std::get<0>(fromChatId)) : std::get<1>(fromChatId)); // Since cpr::Part() does not take 64bit integers (only 32bit), passing a 64bit chatId to 32bit integer gets overflown and sends wrong chat_id which causes Bad Request: chat not found
  data.parts.emplace_back("message_ids", nl::json(messageIds).dump());
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (removeCaption)
    data.parts.emplace_back("remove_caption", removeCaption);

  const nl::json msgIds = sendRequest("copyMessages", data);
  std::vector<Ptr<MessageId>> ret;
  ret.reserve(msgIds.size());
  for (const nl::json& msgIdObj: msgIds) {
    Ptr<MessageId> msgId(new MessageId(msgIdObj));
    ret.emplace_back(std::move(msgId));
  }
  return ret;
}

Ptr<Message> Api::sendPhoto(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& photo,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            bool disableNotification,
                            bool protectContent,
                            const Ptr<IReplyMarkup>& replyMarkup,
                            const std::string& businessConnectionId,
                            std::int32_t directMessagesTopicId,
                            bool showCaptionAboveMedia,
                            bool hasSpoiler,
                            bool allowPaidBroadcast,
                            const std::string& messageEffectId,
                            const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                            const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (showCaptionAboveMedia)
    data.parts.emplace_back("show_caption_above_media", showCaptionAboveMedia);
  if (hasSpoiler)
    data.parts.emplace_back("has_spoiler", hasSpoiler);
  if (hasSpoiler)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendPhoto", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::sendAudio(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& audio,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::time_t duration,
                            const std::string& performer,
                            const std::string& title,
                            const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                            bool disableNotification,
                            bool protectContent,
                            const Ptr<IReplyMarkup>& replyMarkup,
                            const std::string& businessConnectionId,
                            std::int32_t directMessagesTopicId,
                            bool allowPaidBroadcast,
                            const std::string& messageEffectId,
                            const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                            const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(19);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendAudio", data);
  Ptr<Message> message(new Message(sentMsgObj));
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
                               const Ptr<IReplyMarkup>& replyMarkup,
                               const std::string& businessConnectionId,
                               std::int32_t directMessagesTopicId,
                               bool disableContentTypeDetection,
                               bool allowPaidBroadcast,
                               const std::string& messageEffectId,
                               const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                               const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (disableContentTypeDetection)
    data.parts.emplace_back("disable_content_type_detection", disableContentTypeDetection);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendDocument", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}


Ptr<Message> Api::sendVideo(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& video,
                            std::int32_t messageThreadId,
                            std::time_t duration,
                            std::int32_t width,
                            std::int32_t height,
                            const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                            const std::optional<std::variant<cpr::File, std::string>>& cover,
                            std::time_t startTimestamp,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            bool showCaptionAboveMedia,
                            bool hasSpoiler,
                            bool supportsStreaming,
                            bool disableNotification,
                            bool protectContent,
                            const Ptr<IReplyMarkup>& replyMarkup,
                            const std::string& businessConnectionId,
                            std::int32_t directMessagesTopicId,
                            bool allowPaidBroadcast,
                            const std::string& messageEffectId,
                            const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                            const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(24);
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
  if (cover.has_value()) {
    if (cover->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*cover);
      data.parts.emplace_back("cover", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*cover);
      data.parts.emplace_back("cover", fileIdOrUrl);
    }
  }
  if (startTimestamp)
    data.parts.emplace_back("start_timestamp", startTimestamp);
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
  if (showCaptionAboveMedia)
    data.parts.emplace_back("show_caption_above_media", showCaptionAboveMedia);
  if (hasSpoiler)
    data.parts.emplace_back("has_spoiler", hasSpoiler);
  if (supportsStreaming)
    data.parts.emplace_back("supports_streaming", supportsStreaming);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendVideo", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::sendAnimation(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<cpr::File, std::string>& animation,
                                std::int32_t messageThreadId,
                                std::time_t duration,
                                std::int32_t width,
                                std::int32_t height,
                                const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities,
                                bool disableNotification,
                                bool protectContent,
                                const Ptr<IReplyMarkup>& replyMarkup,
                                const std::string& businessConnectionId,
                                std::int32_t directMessagesTopicId,
                                bool allowPaidBroadcast,
                                const std::string& messageEffectId,
                                const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                                const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(21);
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
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendAnimation", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::sendVoice(const std::variant<std::int64_t, std::string>& chatId,
                            const std::variant<cpr::File, std::string>& voice,
                            std::int32_t messageThreadId,
                            const std::string& caption,
                            const std::string& parseMode,
                            const std::vector<Ptr<MessageEntity>>& captionEntities,
                            std::time_t duration,
                            bool disableNotification,
                            bool protectContent,
                            const Ptr<IReplyMarkup>& replyMarkup,
                            const std::string& businessConnectionId,
                            std::int32_t directMessagesTopicId,
                            bool allowPaidBroadcast,
                            const std::string& messageEffectId,
                            const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                            const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(16);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendVoice", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}


Ptr<Message> Api::sendVideoNote(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<cpr::File, std::string>& videoNote,
                                std::int32_t messageThreadId,
                                std::time_t duration,
                                std::int32_t length,
                                const std::optional<std::variant<cpr::File, std::string>>& thumbnail,
                                bool disableNotification,
                                bool protectContent,
                                const Ptr<IReplyMarkup>& replyMarkup,
                                const std::string& businessConnectionId,
                                std::int32_t directMessagesTopicId,
                                bool allowPaidBroadcast,
                                const std::string& messageEffectId,
                                const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                                const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendVideoNote", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::sendPaidMedia(const std::variant<std::int64_t, std::string>& chatId,
                                std::int32_t starCount,
                                const std::vector<Ptr<InputPaidMedia>>& media,
                                const std::string& payload,
                                std::int32_t messageThreadId,
                                const std::string& caption,
                                const std::string& parseMode,
                                const std::vector<Ptr<MessageEntity>>& captionEntities,
                                bool showCaptionAboveMedia,
                                bool disableNotification,
                                bool protectContent,
                                bool allowPaidBroadcast,
                                const Ptr<IReplyMarkup>& replyMarkup,
                                const std::string& businessConnectionId,
                                std::int32_t directMessagesTopicId,
                                const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                                const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("star_count", starCount);
  nl::json mediaJson = nl::json::array();
  // Handle local media files if available, see https://core.telegram.org/bots/api#inputmediaphoto
  for (const Ptr<InputPaidMedia>& m: media) {
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
      default:
        break;
    }
    mediaJson.push_back(mJson);
  }
  data.parts.emplace_back("media", mediaJson.dump());
  if (not payload.empty())
    data.parts.emplace_back("payload", payload);
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
  if (showCaptionAboveMedia)
    data.parts.emplace_back("show_caption_above_media", showCaptionAboveMedia);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());


  const nl::json sentMsgObj = sendRequest("sendPaidMedia", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

std::vector<Ptr<Message>> Api::sendMediaGroup(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::vector<Ptr<InputMedia>>& media,
                                              std::int32_t messageThreadId,
                                              bool disableNotification,
                                              bool protectContent,
                                              const std::string& businessConnectionId,
                                              std::int32_t directMessagesTopicId,
                                              bool allowPaidBroadcast,
                                              const std::string& messageEffectId,
                                              const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(10);
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
      default:
        break;
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
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMessagesArray = sendRequest("sendMediaGroup", data);
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
                               const Ptr<IReplyMarkup>& replyMarkup,
                               const std::string& businessConnectionId,
                               std::int32_t directMessagesTopicId,
                               bool allowPaidBroadcast,
                               const std::string& messageEffectId,
                               const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                               const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(17);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("latitude", std::to_string(latitude));
  data.parts.emplace_back("longitude", std::to_string(longitude));
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (horizontalAccuracy != 0.0f)
    data.parts.emplace_back("horizontal_accuracy", std::to_string(horizontalAccuracy));
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendLocation", data);
  Ptr<Message> message(new Message(sentMsgObj));
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
                            const Ptr<IReplyMarkup>& replyMarkup,
                            const std::string& businessConnectionId,
                            std::int32_t directMessagesTopicId,
                            bool allowPaidBroadcast,
                            const std::string& messageEffectId,
                            const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                            const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(19);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendVenue", data);
  Ptr<Message> message(new Message(sentMsgObj));
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
                              const Ptr<IReplyMarkup>& replyMarkup,
                              const std::string& businessConnectionId,
                              std::int32_t directMessagesTopicId,
                              bool allowPaidBroadcast,
                              const std::string& messageEffectId,
                              const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                              const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(15);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendContact", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}


Ptr<Message> Api::sendPoll(const std::variant<std::int64_t, std::string>& chatId,
                           const std::string& question,
                           const std::vector<Ptr<InputPollOption>>& options,
                           std::int32_t messageThreadId,
                           const std::string& questionParseMode,
                           const std::vector<Ptr<MessageEntity>>& questionEntities,
                           bool isAnonymous,
                           const std::string& type,
                           bool allowsMultipleAnswers,
                           std::int32_t correctOptionId,
                           const std::string& explanation,
                           const std::string& explanationParseMode,
                           const std::vector<Ptr<MessageEntity>>& explanationEntities,
                           std::time_t openPeriod,
                           std::time_t closeDate,
                           bool isClosed,
                           bool disableNotification,
                           bool protectContent,
                           const Ptr<IReplyMarkup>& replyMarkup,
                           const std::string& businessConnectionId,
                           bool allowPaidBroadcast,
                           const std::string& messageEffectId,
                           const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(23);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("question", question);
  if (not options.empty()) {
    nl::json optionsArray = nl::json::array();
    for (const Ptr<InputPollOption>& option: options)
      optionsArray.push_back(option->toJson());
    data.parts.emplace_back("options", optionsArray.dump());
  }
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not questionParseMode.empty())
    data.parts.emplace_back("question_parse_mode", questionParseMode);
  if (not questionEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: questionEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("question_entities", entitiesArray.dump());
  }
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
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendPoll", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}


Ptr<Message> Api::sendChecklist(const std::variant<std::int64_t, std::string>& chatId,
                                const std::string& businessConnectionId,
                                const Ptr<InputChecklist>& checklist,
                                bool disableNotification,
                                bool protectContent,
                                const Ptr<IReplyMarkup>& replyMarkup,
                                const std::string& messageEffectId,
                                const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(8);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("checklist", checklist->toJson().dump());
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendChecklist", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

Ptr<Message> Api::sendDice(const std::variant<std::int64_t, std::string>& chatId,
                           const std::string& emoji,
                           std::int32_t messageThreadId,
                           bool disableNotification,
                           bool protectContent,
                           const Ptr<IReplyMarkup>& replyMarkup,
                           const std::string& businessConnectionId,
                           std::int32_t directMessagesTopicId,
                           bool allowPaidBroadcast,
                           const std::string& messageEffectId,
                           const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                           const Ptr<ReplyParameters>& replyParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(12);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (not emoji.empty())
    data.parts.emplace_back("emoji", emoji);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());

  const nl::json sentMsgObj = sendRequest("sendDice", data);
  Ptr<Message> message(new Message(sentMsgObj));
  return message;
}

bool Api::sendChatAction(const std::variant<std::int64_t, std::string>& chatId,
                         const std::string& action,
                         std::int32_t messageThreadId,
                         const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("action", action);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  return sendRequest("sendChatAction", data);
}

bool Api::setMessageReaction(const std::variant<std::int64_t, std::string>& chatId,
                             std::int32_t messageId,
                             const std::vector<Ptr<ReactionType>>& reaction,
                             bool isBig) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (not reaction.empty()) {
    nl::json reactionJson = nl::json::array();
    for (const Ptr<ReactionType>& reactionType: reaction) {
      reactionJson.push_back(reactionType->toJson());
    }
    data.parts.emplace_back("reaction", reactionJson.dump());
  }
  if (isBig)
    data.parts.emplace_back("is_big", isBig);
  return sendRequest("setMessageReaction", data);
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

  const nl::json userProfilePhotosObj = sendRequest("getUserProfilePhotos", data);
  Ptr<UserProfilePhotos> userProfilePhotos(new UserProfilePhotos(userProfilePhotosObj));
  return userProfilePhotos;
}

Ptr<File> Api::getFile(const std::string& fileId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("file_id", fileId);
  const nl::json fileObj = sendRequest("getFile", data);
  Ptr<File> file(new File(fileObj));
  return file;
}

std::string Api::downloadFile(const std::string& filePath, const std::function<bool(cpr::cpr_off_t, cpr::cpr_off_t)>& progressCallback) const {
  std::ostringstream oss{};
  oss << m_apiUrl << "/file/bot" << m_token << "/" << filePath;

  cpr::Session session{};
  session.SetProxies(m_proxies);
  session.SetUrl(cpr::Url{oss.str()});
  session.SetConnectTimeout(m_connectTimeout);
  session.SetTimeout(m_downloadFilesTimeout);
  session.SetAcceptEncoding({cpr::AcceptEncodingMethods::deflate, cpr::AcceptEncodingMethods::gzip, cpr::AcceptEncodingMethods::zlib});
  if (progressCallback) {
    const cpr::ProgressCallback pCallback{[&progressCallback](cpr::cpr_off_t downloadTotal,
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
  throw Exception("Failed to download file '" + filePath + "' contents", isErrorCode(res.status_code) ? static_cast<ErrorCode>(res.status_code) : ErrorCode::OTHER);
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
    data.parts.emplace_back("until_date", std::to_string(untilDate));
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
    data.parts.emplace_back("until_date", std::to_string(untilDate));

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
                            bool canManageTopics,
                            bool canManageDirectMessages) const {
  cpr::Multipart data{};
  data.parts.reserve(18);
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
  if (canManageDirectMessages)
    data.parts.emplace_back("can_manage_direct_messages", canManageDirectMessages);
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
    data.parts.emplace_back("expire_date", std::to_string(expireDate));
  if (memberLimit)
    data.parts.emplace_back("member_limit", memberLimit);
  if (createsJoinRequest)
    data.parts.emplace_back("creates_join_request", createsJoinRequest);

  const nl::json chatInviteLinkObj = sendRequest("createChatInviteLink", data);
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
    data.parts.emplace_back("expire_date", std::to_string(expireDate));
  if (memberLimit)
    data.parts.emplace_back("member_limit", memberLimit);
  if (createsJoinRequest)
    data.parts.emplace_back("creates_join_request", createsJoinRequest);

  const nl::json chatInviteLinkObj = sendRequest("editChatInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::createChatSubscriptionInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                                          std::time_t subscriptionPeriod,
                                                          std::int32_t subscriptionPrice,
                                                          const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("subscription_period", subscriptionPeriod);
  data.parts.emplace_back("subscription_price", subscriptionPrice);
  if (not name.empty())
    data.parts.emplace_back("name", name);

  const nl::json chatInviteLinkObj = sendRequest("createChatSubscriptionInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::editChatSubscriptionInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                                        const std::string& inviteLink,
                                                        const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("invite_link", inviteLink);
  if (not name.empty())
    data.parts.emplace_back("name", name);

  const nl::json chatInviteLinkObj = sendRequest("editChatSubscriptionInviteLink", data);
  Ptr<ChatInviteLink> chatInviteLink(new ChatInviteLink(chatInviteLinkObj));
  return chatInviteLink;
}

Ptr<ChatInviteLink> Api::revokeChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                              const std::string& inviteLink) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("invite_link", inviteLink);

  const nl::json chatInviteLinkObj = sendRequest("revokeChatInviteLink", data);
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
                         bool disableNotification,
                         const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  return sendRequest("pinChatMessage", data);
}

bool Api::unpinChatMessage(const std::variant<std::int64_t, std::string>& chatId,
                           std::int32_t messageId,
                           const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

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

  const nl::json chatObj = sendRequest("getChat", data);
  Ptr<Chat> chat(new Chat(chatObj));
  return chat;
}

std::vector<Ptr<ChatMember>> Api::getChatAdministrators(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));

  const nl::json chatMembersArray = sendRequest("getChatAdministrators", data);
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

  const nl::json chatMemberObj = sendRequest("getChatMember", data);
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
  const nl::json stickersArray = sendRequest("getForumTopicIconStickers");
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

  const nl::json forumTopicObj = sendRequest("createForumTopic", data);
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
                              std::time_t cacheTime) const {
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

Ptr<UserChatBoosts> Api::getUserChatBoosts(const std::variant<std::int64_t, std::string>& chatId,
                                           std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("user_id", std::to_string(userId));
  return makePtr<UserChatBoosts>(sendRequest("getUserChatBoosts", data));
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


  const bool ok = sendRequest("setMyCommands", data);
  if (ok) {
    // Cache commands locally to avoid calling getMyCommands() each time we receive a new message,
    // and we want to determine if it is a Command.
    m_cache.botCommands.clear();
    m_cache.botCommands.reserve(commands.size());
    for (const Ptr<BotCommand>& command: commands)
      m_cache.botCommands.push_back(command->command);
  }
  return ok;
}

bool Api::deleteMyCommands(const Ptr<BotCommandScope>& scope, const std::string& languageCode) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (scope)
    data.parts.emplace_back("scope", scope->toJson().dump());
  else {
    const auto defScope = makePtr<BotCommandScopeDefault>();
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
    const auto defScope = makePtr<BotCommandScopeDefault>();
    data.parts.emplace_back("scope", defScope->toJson().dump());
  }
  if (not languageCode.empty())
    data.parts.emplace_back("language_code", languageCode);

  const nl::json commandsJson = sendRequest("getMyCommands", data);
  m_cache.botCommands.clear();
  if (commandsJson.empty()) return commands;
  commands.reserve(commandsJson.size());
  m_cache.botCommands.reserve(commandsJson.size());
  for (const nl::json& commandObj: commandsJson) {
    Ptr<BotCommand> cmd(new BotCommand(commandObj));
    // Cache commands locally to avoid calling getMyCommands() each time we receive a new message,
    // and we want to determine if it is a Command.
    m_cache.botCommands.push_back(cmd->command);
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

  const nl::json botNameObj = sendRequest("getMyName", data);
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

  const nl::json botDescObj = sendRequest("getMyDescription", data);
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

  const nl::json botShortDescObj = sendRequest("getMyShortDescription", data);
  return makePtr<BotShortDescription>(botShortDescObj);
}

bool Api::setChatMenuButton(const std::variant<std::int64_t, std::string>& chatId, const Ptr<tgbotxx::MenuButton>& menuButton) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  const std::string chatIdStr = chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId);
  if (not chatIdStr.empty())
    data.parts.emplace_back("chat_id", chatIdStr);
  if (menuButton)
    data.parts.emplace_back("menu_button", menuButton->toJson().dump());
  else {
    const auto defMenuButton = makePtr<MenuButtonDefault>();
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
  const nl::json chatAdministratorRightsObj = sendRequest("getMyDefaultAdministratorRights", data);
  return makePtr<ChatAdministratorRights>(chatAdministratorRightsObj);
}

/////////////////////////////////////////////////////////////////////////////////////////////////


Ptr<Gifts> Api::getAvailableGifts() const {
  return makePtr<Gifts>(sendRequest("getAvailableGifts"));
}

bool Api::sendGift(const std::string& giftId,
                   std::int64_t userId,
                   const std::variant<std::int64_t, std::string>& chatId,
                   bool payForUpgrade,
                   const std::string& text,
                   const std::string& textParseMode,
                   const std::vector<Ptr<MessageEntity>>& textEntities) const {
  cpr::Multipart data{};
  data.parts.reserve(6); // one of userId or chatId
  data.parts.emplace_back("gift_id", giftId);
  if (userId)
    data.parts.emplace_back("user_id", std::to_string(userId));
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
  if (payForUpgrade)
    data.parts.emplace_back("pay_for_upgrade", payForUpgrade);
  if (not text.empty())
    data.parts.emplace_back("text", text);
  if (not textParseMode.empty())
    data.parts.emplace_back("text_parse_mode", textParseMode);
  if (not textEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: textEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("text_entities", entitiesArray.dump());
  }
  return sendRequest("sendGift", data);
}

bool Api::giftPremiumSubscription(std::int64_t userId,
                                  std::int32_t monthCount,
                                  std::int32_t starCount,
                                  const std::string& text,
                                  const std::string& textParseMode,
                                  const std::vector<Ptr<MessageEntity>>& textEntities) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("month_count", monthCount);
  data.parts.emplace_back("star_count", starCount);
  if (not text.empty())
    data.parts.emplace_back("text", text);
  if (not textParseMode.empty())
    data.parts.emplace_back("text_parse_mode", textParseMode);
  if (not textEntities.empty()) {
    nl::json entitiesArray = nl::json::array();
    for (const Ptr<MessageEntity>& entity: textEntities)
      entitiesArray.push_back(entity->toJson());
    data.parts.emplace_back("text_entities", entitiesArray.dump());
  }
  return sendRequest("giftPremiumSubscription", data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
bool Api::verifyUser(std::int64_t userId,
                     const std::string& customDescription) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (not customDescription.empty())
    data.parts.emplace_back("custom_description", customDescription);
  return sendRequest("verifyUser", data);
}

bool Api::verifyChat(const std::variant<std::int64_t, std::string>& chatId,
                     const std::string& customDescription) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
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
  if (not customDescription.empty())
    data.parts.emplace_back("custom_description", customDescription);
  return sendRequest("verifyChat", data);
}

bool Api::removeUserVerification(std::int64_t userId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("user_id", std::to_string(userId));
  return sendRequest("removeUserVerification", data);
}

bool Api::removeChatVerification(const std::variant<std::int64_t, std::string>& chatId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
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
  return sendRequest("removeChatVerification", data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool Api::readBusinessMessage(const std::string& businessConnectionId,
                              const std::variant<std::int64_t, std::string>& chatId,
                              std::int32_t messageId) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
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
  data.parts.emplace_back("message_id", messageId);
  return sendRequest("readBusinessMessage", data);
}

bool Api::deleteBusinessMessages(const std::string& businessConnectionId,
                                 const std::vector<std::int32_t>& messageIds) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("message_ids", nl::json(messageIds).dump());
  return sendRequest("deleteBusinessMessages", data);
}

bool Api::setBusinessAccountName(const std::string& businessConnectionId,
                                 const std::string& firstName,
                                 const std::string& lastName) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("first_name", firstName);
  if (not lastName.empty())
    data.parts.emplace_back("last_name", lastName);
  return sendRequest("setBusinessAccountName", data);
}

bool Api::setBusinessAccountUsername(const std::string& businessConnectionId,
                                     const std::string& username) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (not username.empty())
    data.parts.emplace_back("username", username);
  return sendRequest("setBusinessAccountUsername", data);
}

bool Api::setBusinessAccountBio(const std::string& businessConnectionId,
                                const std::string& bio) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (not bio.empty())
    data.parts.emplace_back("bio", bio);
  return sendRequest("setBusinessAccountBio", data);
}

bool Api::setBusinessAccountProfilePhoto(const std::string& businessConnectionId,
                                         const Ptr<InputProfilePhoto>& photo,
                                         bool isPublic) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("photo", photo->toJson().dump());
  if (isPublic)
    data.parts.emplace_back("is_public", isPublic);
  return sendRequest("setBusinessAccountProfilePhoto", data);
}

bool Api::removeBusinessAccountProfilePhoto(const std::string& businessConnectionId,
                                            bool isPublic) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (isPublic)
    data.parts.emplace_back("is_public", isPublic);
  return sendRequest("removeBusinessAccountProfilePhoto", data);
}

bool Api::setBusinessAccountGiftSettings(const std::string& businessConnectionId,
                                         bool showGiftButton,
                                         const Ptr<AcceptedGiftTypes>& acceptedGiftTypes) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("show_gift_button", showGiftButton);
  data.parts.emplace_back("accepted_gift_types", acceptedGiftTypes->toJson().dump());
  return sendRequest("setBusinessAccountGiftSettings", data);
}

Ptr<StarAmount> Api::getBusinessAccountStarBalance(const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  return makePtr<StarAmount>(sendRequest("getBusinessAccountStarBalance", data));
}

bool Api::transferBusinessAccountStars(const std::string& businessConnectionId, std::int32_t starCount) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("star_count", starCount);
  return sendRequest("transferBusinessAccountStars", data);
}

Ptr<OwnedGifts> Api::getBusinessAccountGifts(const std::string& businessConnectionId,
                                             bool excludeUnsaved,
                                             bool excludeSaved,
                                             bool excludeUnlimited,
                                             bool excludeLimited,
                                             bool excludeUnique,
                                             bool sortByPrice,
                                             const std::string& offset,
                                             std::int32_t limit) const {
  cpr::Multipart data{};
  data.parts.reserve(9);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (excludeUnsaved)
    data.parts.emplace_back("exclude_unsaved", excludeUnsaved);
  if (excludeSaved)
    data.parts.emplace_back("exclude_saved", excludeSaved);
  if (excludeUnlimited)
    data.parts.emplace_back("exclude_unlimited", excludeUnlimited);
  if (excludeLimited)
    data.parts.emplace_back("exclude_limited", excludeLimited);
  if (excludeUnique)
    data.parts.emplace_back("exclude_unique", excludeUnique);
  if (sortByPrice)
    data.parts.emplace_back("sort_by_price", sortByPrice);
  data.parts.emplace_back("offset", offset);
  data.parts.emplace_back("limit", limit);
  return makePtr<OwnedGifts>(sendRequest("getBusinessAccountGifts", data));
}

bool Api::convertGiftToStars(const std::string& businessConnectionId, const std::string& ownedGiftId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("owned_gift_id", ownedGiftId);
  return sendRequest("convertGiftToStars", data);
}

bool Api::upgradeGift(const std::string& businessConnectionId,
                      const std::string& ownedGiftId,
                      bool keepOriginalDetails,
                      std::int32_t starCount) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("owned_gift_id", ownedGiftId);
  if (keepOriginalDetails)
    data.parts.emplace_back("keep_original_details", keepOriginalDetails);
  if (starCount >= 0)
    data.parts.emplace_back("star_count", starCount);
  return sendRequest("convertGiftToStars", data);
}

bool Api::transferGift(const std::string& businessConnectionId,
                       const std::string& ownedGiftId,
                       std::int64_t newOwnerChatId,
                       std::int32_t starCount) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("owned_gift_id", ownedGiftId);
  data.parts.emplace_back("new_owner_chat_id", newOwnerChatId);
  if (starCount >= 0)
    data.parts.emplace_back("star_count", starCount);
  return sendRequest("transferGift", data);
}

Ptr<Story> Api::postStory(const std::string& businessConnectionId,
                          const Ptr<InputStoryContent>& content,
                          std::time_t activePeriod,
                          const std::string& caption,
                          const std::string& parseMode,
                          const std::vector<Ptr<MessageEntity>>& captionEntities,
                          const std::vector<Ptr<StoryArea>>& areas,
                          bool postToChatPage,
                          bool protectContent) const {
  cpr::Multipart data{};
  data.parts.reserve(9);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("content", content->toJson().dump());
  data.parts.emplace_back("active_period", activePeriod);
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
  if (not areas.empty()) {
    nl::json areasArray = nl::json::array();
    for (const Ptr<StoryArea>& area: areas)
      areasArray.push_back(area->toJson());
    data.parts.emplace_back("areas", areasArray.dump());
  }
  if (postToChatPage)
    data.parts.emplace_back("post_to_chat_page", postToChatPage);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);

  return makePtr<Story>(sendRequest("postStory", data));
}

Ptr<Story> Api::editStory(const std::string& businessConnectionId,
                          std::int32_t storyId,
                          const Ptr<InputStoryContent>& content,
                          const std::string& caption,
                          const std::string& parseMode,
                          const std::vector<Ptr<MessageEntity>>& captionEntities,
                          const std::vector<Ptr<StoryArea>>& areas) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("story_id", storyId);
  data.parts.emplace_back("content", content->toJson().dump());
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
  if (not areas.empty()) {
    nl::json areasArray = nl::json::array();
    for (const Ptr<StoryArea>& area: areas)
      areasArray.push_back(area->toJson());
    data.parts.emplace_back("areas", areasArray.dump());
  }
  return makePtr<Story>(sendRequest("editStory", data));
}

bool Api::deleteStory(const std::string& businessConnectionId, std::int32_t storyId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("story_id", storyId);
  return sendRequest("deleteStory", data);
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
std::vector<Ptr<Update>> Api::getUpdates(std::int32_t offset, std::int32_t limit, const std::shared_ptr<std::atomic<bool>>& cancellationParam) const {
  std::vector<Ptr<Update>> updates;
  const cpr::Multipart data = {
    {"offset", offset},
    {"limit", std::max<std::int32_t>(1, std::min<std::int32_t>(100, limit))},
    {"timeout", static_cast<std::int32_t>(std::chrono::duration_cast<std::chrono::seconds>(m_longPollTimeout.ms).count())},
    {"allowed_updates", nl::json(m_allowedUpdates).dump()},
  };
  const nl::json updatesJson = sendRequest("getUpdates", data, cancellationParam);
  updates.reserve(updatesJson.size());
  for (const nl::json& updateObj: updatesJson) {
    Ptr<Update> update = makePtr<Update>(updateObj);
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
                                  const Ptr<IReplyMarkup>& replyMarkup,
                                  const std::string& businessConnectionId,
                                  const Ptr<LinkPreviewOptions>& linkPreviewOptions) const {
  cpr::Multipart data{};
  data.parts.reserve(9);
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
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (linkPreviewOptions)
    data.parts.emplace_back("link_preview_options", linkPreviewOptions->toJson().dump());

  nl::json sentMessageObj = sendRequest("editMessageText", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}

Ptr<Message> Api::editMessageCaption(const std::variant<std::int64_t, std::string>& chatId,
                                     std::int32_t messageId,
                                     const std::string& inlineMessageId,
                                     const std::string& caption,
                                     const std::string& parseMode,
                                     const std::vector<Ptr<MessageEntity>>& captionEntities,
                                     const Ptr<IReplyMarkup>& replyMarkup,
                                     const std::string& businessConnectionId,
                                     bool showCaptionAboveMedia) const {
  cpr::Multipart data{};
  data.parts.reserve(9);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (const std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (const std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
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
    data.parts.emplace_back("caption_entities", entitiesArray.dump());
  }
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (showCaptionAboveMedia)
    data.parts.emplace_back("show_caption_above_media", showCaptionAboveMedia);

  const nl::json sentMessageObj = sendRequest("editMessageCaption", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}


Ptr<Message> Api::editMessageMedia(const Ptr<InputMedia>& media,
                                   const std::variant<std::int64_t, std::string>& chatId,
                                   std::int32_t messageId,
                                   const std::string& inlineMessageId,
                                   const Ptr<IReplyMarkup>& replyMarkup,
                                   const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(6);
  data.parts.emplace_back("media", media->toJson().dump());
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (const std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (const std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
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
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  const nl::json sentMessageObj = sendRequest("editMessageMedia", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}

Ptr<Message> Api::editMessageLiveLocation(float latitude,
                                          float longitude,
                                          const std::variant<std::int64_t, std::string>& chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          std::int32_t livePeriod,
                                          float horizontalAccuracy,
                                          std::int32_t heading,
                                          std::int32_t proximityAlertRadius,
                                          const Ptr<IReplyMarkup>& replyMarkup,
                                          const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(11);
  data.parts.emplace_back("latitude", std::to_string(latitude));
  data.parts.emplace_back("longitude", std::to_string(longitude));
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (const std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (const std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
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
  if (livePeriod)
    data.parts.emplace_back("live_period", livePeriod);
  if (horizontalAccuracy != 0.0f)
    data.parts.emplace_back("horizontal_accuracy", std::to_string(horizontalAccuracy));
  if (heading)
    data.parts.emplace_back("heading", heading);
  if (proximityAlertRadius)
    data.parts.emplace_back("proximity_alert_radius", proximityAlertRadius);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  const nl::json sentMessageObj = sendRequest("editMessageLiveLocation", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}


Ptr<Message> Api::stopMessageLiveLocation(const std::variant<std::int64_t, std::string>& chatId,
                                          std::int32_t messageId,
                                          const std::string& inlineMessageId,
                                          const Ptr<IReplyMarkup>& replyMarkup,
                                          const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (const std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (const std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
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
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  const nl::json sentMessageObj = sendRequest("stopMessageLiveLocation", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}

Ptr<Message> Api::editMessageChecklist(std::int64_t chatId,
                                       std::int32_t messageId,
                                       const Ptr<InputChecklist>& checklist,
                                       const std::string& businessConnectionId,
                                       const Ptr<IReplyMarkup>& replyMarkup) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("message_id", messageId);
  data.parts.emplace_back("message_id", checklist->toJson().dump());
  data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  const nl::json sentMessageObj = sendRequest("editMessageChecklist", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}


Ptr<Message> Api::editMessageReplyMarkup(const std::variant<std::int64_t, std::string>& chatId,
                                         std::int32_t messageId,
                                         const std::string& inlineMessageId,
                                         const Ptr<IReplyMarkup>& replyMarkup,
                                         const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(5);
  switch (chatId.index()) {
    case 0: // std::int64_t
      if (const std::int64_t chatIdInt = std::get<std::int64_t>(chatId); chatIdInt != 0) {
        data.parts.emplace_back("chat_id", std::to_string(chatIdInt));
      }
      break;
    case 1: // std::string
      if (const std::string chatIdStr = std::get<std::string>(chatId); not chatIdStr.empty()) {
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
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  const nl::json sentMessageObj = sendRequest("editMessageReplyMarkup", data);
  if (sentMessageObj.contains("message_id")) {
    Ptr<Message> message(new Message(sentMessageObj));
    return message;
  } else {
    // @todo: we have 2 return types here, Message or Boolean, shall we return a variant?
    return nullptr;
  }
}

Ptr<Poll> Api::stopPoll(const std::variant<std::int64_t, std::string>& chatId,
                        std::int32_t messageId,
                        const Ptr<IReplyMarkup>& replyMarkup,
                        const std::string& businessConnectionId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);

  const nl::json pollObj = sendRequest("stopPoll", data);
  Ptr<Poll> poll(new Poll(pollObj));
  return poll;
}

bool Api::approveSuggestedPost(std::int64_t chatId,
                               std::int32_t messageId,
                               std::time_t sendDate) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (sendDate)
    data.parts.emplace_back("send_date", sendDate);
  return sendRequest("approveSuggestedPost", data);
}

bool Api::deleteMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_id", messageId);
  return sendRequest("deleteMessage", data);
}
bool Api::deleteMessages(const std::variant<std::int64_t, std::string>& chatId, const std::vector<std::int32_t>& messageIds) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("chat_id", chatId.index() == 0 ? std::to_string(std::get<0>(chatId)) : std::get<1>(chatId));
  data.parts.emplace_back("message_ids", nl::json(messageIds).dump());
  return sendRequest("deleteMessages", data);
}

bool Api::declineSuggestedPost(std::int64_t chatId,
                               std::int32_t messageId,
                               const std::string& comment) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("chat_id", std::to_string(chatId));
  data.parts.emplace_back("message_id", messageId);
  if (not comment.empty())
    data.parts.emplace_back("comment", comment);
  return sendRequest("declineSuggestedPost", data);
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

  const nl::json sendWebAppMsgObj = sendRequest("answerWebAppQuery", data);
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
                              const Ptr<tgbotxx::IReplyMarkup>& replyMarkup,
                              const std::string& businessConnectionId,
                              std::int32_t directMessagesTopicId,
                              const Ptr<LinkPreviewOptions>& linkPreviewOptions,
                              bool allowPaidBroadcast,
                              const std::string& messageEffectId,
                              const Ptr<SuggestedPostParameters>& suggestedPostParameters) const {
  cpr::Multipart data{};
  data.parts.reserve(13);
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
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  if (directMessagesTopicId)
    data.parts.emplace_back("direct_messages_topic_id", directMessagesTopicId);
  if (linkPreviewOptions)
    data.parts.emplace_back("link_preview_options", linkPreviewOptions->toJson().dump());
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());

  const nl::json sentMessageObj = sendRequest("sendSticker", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

Ptr<StickerSet> Api::getStickerSet(const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("name", name);

  const nl::json stickerSetObj = sendRequest("getStickerSet", data);
  Ptr<StickerSet> stickerSet(new StickerSet(stickerSetObj));
  return stickerSet;
}

std::vector<Ptr<Sticker>> Api::getCustomEmojiStickers(const std::vector<std::string>& customEmojiIds) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("custom_emoji_ids", nl::json(customEmojiIds).dump());
  const nl::json stickersArray = sendRequest("getCustomEmojiStickers", data);

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

  const nl::json fileObj = sendRequest("uploadStickerFile", data);
  Ptr<File> file(new File(fileObj));
  return file;
}

bool Api::createNewStickerSet(std::int64_t userId,
                              const std::string& name,
                              const std::string& title,
                              const std::vector<Ptr<InputSticker>>& stickers,
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

bool Api::replaceStickerInSet(std::int64_t userId,
                              const std::string& name,
                              const std::string& oldSticker,
                              const Ptr<InputSticker>& sticker) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("name", name);
  data.parts.emplace_back("old_sticker", oldSticker);
  data.parts.emplace_back("sticker", sticker->toJson().dump());
  return sendRequest("replaceStickerInSet", data);
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
                                 std::int64_t userId,
                                 const std::string& format,
                                 const std::optional<std::variant<cpr::File, std::string>>& thumbnail) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("name", name);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("format", format);
  if (thumbnail.has_value()) {
    if (thumbnail->index() == 0) /* cpr::File */ {
      const cpr::File& file = std::get<cpr::File>(*thumbnail);
      data.parts.emplace_back("thumbnail", cpr::Files{file});
    } else /* std::string (fileId or Url) */ {
      const std::string& fileIdOrUrl = std::get<std::string>(*thumbnail);
      data.parts.emplace_back("thumbnail", fileIdOrUrl);
    }
  }
  return sendRequest("setStickerSetThumbnail", data);
}

bool Api::setCustomEmojiStickerSetThumbnail(const std::string& name, const std::optional<std::string>& customEmojiId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("name", name);
  if (customEmojiId.has_value()) {
    data.parts.emplace_back("custom_emoji_id", customEmojiId.value());
  }
  return sendRequest("setCustomEmojiStickerSetThumbnail", data);
}

bool Api::deleteStickerSet(const std::string& name) const {
  cpr::Multipart data{};
  data.parts.reserve(1);
  data.parts.emplace_back("name", name);
  return sendRequest("deleteStickerSet", data);
}


/////////////////////////////////////////////////////////////////////////////////////////////////

bool Api::setPassportDataErrors(std::int64_t userId, const std::vector<Ptr<PassportElementError>>& errors) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("user_id", std::to_string(userId));
  nl::json errorsArray = nl::json::array();
  for (const Ptr<PassportElementError>& err: errors) {
    errorsArray.push_back(err->toJson());
  }
  data.parts.emplace_back("errors", errorsArray.dump());
  return sendRequest("setPassportDataErrors", data);
}


/////////////////////////////////////////////////////////////////////////////////////////////////

Ptr<Message> Api::sendGame(const std::variant<std::int64_t, std::string>& chatId,
                           const std::string& gameShortName,
                           std::int32_t messageThreadId,
                           bool disableNotification,
                           bool protectContent,
                           const Ptr<tgbotxx::ReplyParameters>& replyParameters,
                           const Ptr<tgbotxx::IReplyMarkup>& replyMarkup) const {
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
  data.parts.emplace_back("game_short_name", gameShortName);
  if (messageThreadId)
    data.parts.emplace_back("message_thread_id", messageThreadId);
  if (disableNotification)
    data.parts.emplace_back("disable_notification", disableNotification);
  if (protectContent)
    data.parts.emplace_back("protect_content", protectContent);
  if (replyParameters)
    data.parts.emplace_back("reply_parameters", replyParameters->toJson().dump());
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  const nl::json sentMessageObj = sendRequest("sendGame", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}


Ptr<Message> Api::setGameScore(std::int64_t userId,
                               std::int32_t score,
                               bool force,
                               bool disableEditMessage,
                               std::int64_t chatId,
                               std::int32_t messageId,
                               const std::string& inlineMessageId) const {
  cpr::Multipart data{};
  data.parts.reserve(7);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("score", score);
  if (force)
    data.parts.emplace_back("force", force);
  if (disableEditMessage)
    data.parts.emplace_back("disable_edit_message", disableEditMessage);
  if (chatId)
    data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);

  const nl::json sentMessageObj = sendRequest("setGameScore", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}

std::vector<Ptr<GameHighScore>> Api::getGameHighScores(std::int64_t userId,
                                                       std::int64_t chatId,
                                                       std::int32_t messageId,
                                                       const std::string& inlineMessageId) const {
  cpr::Multipart data{};
  data.parts.reserve(4);
  data.parts.emplace_back("user_id", std::to_string(userId));
  if (chatId)
    data.parts.emplace_back("chat_id", std::to_string(chatId));
  if (messageId)
    data.parts.emplace_back("message_id", messageId);
  if (not inlineMessageId.empty())
    data.parts.emplace_back("inline_message_id", inlineMessageId);

  const nl::json gameScoresJson = sendRequest("getGameHighScores", data);

  std::vector<Ptr<GameHighScore>> gameScores;
  gameScores.reserve(gameScoresJson.size());
  for (const nl::json& gameScoreJson: gameScoresJson) {
    Ptr<GameHighScore> gameScore = makePtr<GameHighScore>(gameScoreJson);
    gameScores.push_back(std::move(gameScore));
  }
  return gameScores;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
void Api::setUrl(const std::string& url) noexcept {
  m_apiUrl = url;
}
const std::string& Api::getUrl() const noexcept {
  return m_apiUrl;
}

void Api::setLongPollTimeout(const cpr::Timeout& longPollTimeout) {
  using namespace std::chrono_literals;
  if (longPollTimeout.ms >= m_timeout.ms)
    // Api request timeout should always be longer than long poll timeout.
    // Otherwise, the api request will time out before long polling finishes
    m_timeout.ms = longPollTimeout.ms + 1s;
  m_longPollTimeout = longPollTimeout;
}
cpr::Timeout Api::getLongPollTimeout() const noexcept { return m_longPollTimeout; }

void Api::setConnectTimeout(const cpr::ConnectTimeout& timeout) noexcept {
  m_connectTimeout = timeout;
}
cpr::ConnectTimeout Api::getConnectTimeout() const noexcept { return m_connectTimeout; }

void Api::setTimeout(const cpr::Timeout& timeout) {
  using namespace std::chrono_literals;
  cpr::Timeout newTimeout{timeout.ms};
  if (newTimeout.ms <= m_longPollTimeout.ms)
    // Api request timeout should always be longer than long poll timeout.
    // Otherwise, the api request will time out before long polling finishes.
    newTimeout.ms = m_longPollTimeout.ms + 1s;
  m_timeout = newTimeout;
}
cpr::Timeout Api::getTimeout() const noexcept { return m_timeout; }

void Api::setProxies(const cpr::Proxies& proxies) { m_proxies = proxies; }
const cpr::Proxies& Api::getProxies() const noexcept { return m_proxies; }

void Api::setUploadFilesTimeout(const cpr::Timeout& timeout) noexcept {
  m_uploadFilesTimeout = timeout;
}
cpr::Timeout Api::getUploadFilesTimeout() const noexcept { return m_uploadFilesTimeout; }

void Api::setDownloadFilesTimeout(const cpr::Timeout& timeout) noexcept {
  m_downloadFilesTimeout = timeout;
}
cpr::Timeout Api::getDownloadFilesTimeout() const noexcept { return m_downloadFilesTimeout; }

void Api::setAllowedUpdates(const std::vector<std::string>& allowedUpdates) noexcept {
  m_allowedUpdates = allowedUpdates;
}
/// @brief Get list of the update types you want your bot to receive.
const std::vector<std::string>& Api::getAllowedUpdates() const noexcept { return m_allowedUpdates; }

const Api::Cache& Api::getCache() const noexcept { return m_cache; }

/////////////////////////////////////////////////////////////////////////////////////////////////
Ptr<Message> Api::sendInvoice(const std::variant<std::int64_t, std::string>& chatId,
                              const std::string& title,
                              const std::string& description,
                              const std::string& payload,
                              const std::string& currency,
                              const std::vector<Ptr<LabeledPrice>>& prices,
                              const std::string& providerToken,
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
                              bool allowPaidBroadcast,
                              const std::string& messageEffectId,
                              const Ptr<SuggestedPostParameters>& suggestedPostParameters,
                              const Ptr<IReplyMarkup>& replyMarkup) const {

  cpr::Multipart data{};
  data.parts.reserve(31);
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
  data.parts.emplace_back("currency", currency);
  nl::json pricesJson = nl::json::array();
  for (const Ptr<LabeledPrice>& price: prices)
    pricesJson.push_back(price->toJson());
  data.parts.emplace_back("prices", pricesJson.dump());
  data.parts.emplace_back("provider_token", providerToken);
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
  if (allowPaidBroadcast)
    data.parts.emplace_back("allow_paid_broadcast", allowPaidBroadcast);
  if (not messageEffectId.empty())
    data.parts.emplace_back("message_effect_id", messageEffectId);
  if (suggestedPostParameters)
    data.parts.emplace_back("suggested_post_parameters", suggestedPostParameters->toJson().dump());
  if (replyMarkup)
    data.parts.emplace_back("reply_markup", replyMarkup->toJson().dump());

  const nl::json sentMessageObj = sendRequest("sendInvoice", data);
  Ptr<Message> message(new Message(sentMessageObj));
  return message;
}


std::string Api::createInvoiceLink(const std::string& title,
                                   const std::string& description,
                                   const std::string& payload,
                                   const std::string& currency,
                                   const std::vector<Ptr<LabeledPrice>>& prices,
                                   const std::string& businessConnectionId,
                                   const std::string& providerToken,
                                   std::time_t subscriptionPeriod,
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
  data.parts.reserve(22);
  data.parts.emplace_back("title", title);
  data.parts.emplace_back("description", description);
  data.parts.emplace_back("payload", payload);
  data.parts.emplace_back("currency", currency);
  nl::json pricesJson = nl::json::array();
  for (const Ptr<LabeledPrice>& price: prices)
    pricesJson.push_back(price->toJson());
  data.parts.emplace_back("prices", pricesJson.dump());
  if (not businessConnectionId.empty())
    data.parts.emplace_back("business_connection_id", businessConnectionId);
  data.parts.emplace_back("provider_token", providerToken);
  if (subscriptionPeriod)
    data.parts.emplace_back("subscription_period", subscriptionPeriod);
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

Ptr<StarAmount> Api::getMyStarBalance() const {
  return makePtr<StarAmount>(sendRequest("getMyStarBalance"));
}

Ptr<StarTransactions> Api::getStarTransactions(std::int32_t offset, std::int32_t limit) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  if (offset)
    data.parts.emplace_back("offset", offset);
  if (limit)
    data.parts.emplace_back("limit", limit);
  return makePtr<StarTransactions>(sendRequest("getStarTransactions", data));
}

bool Api::refundStarPayment(std::int64_t userId, const std::string& telegramPaymentChargeId) const {
  cpr::Multipart data{};
  data.parts.reserve(2);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("telegram_payment_charge_id", telegramPaymentChargeId);
  return sendRequest("refundStarPayment", data);
}

bool Api::editUserStarSubscription(std::int64_t userId, const std::string& telegramPaymentChargeId, bool isCancelled) const {
  cpr::Multipart data{};
  data.parts.reserve(3);
  data.parts.emplace_back("user_id", std::to_string(userId));
  data.parts.emplace_back("telegram_payment_charge_id", telegramPaymentChargeId);
  data.parts.emplace_back("is_canceled", isCancelled);
  return sendRequest("editUserStarSubscription", data);
}
