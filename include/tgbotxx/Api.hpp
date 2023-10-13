#pragma once
#include <cpr/cpr.h>
#include <cstdint>
#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
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
#include <tgbotxx/objects/ForceReply.hpp>
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
#include <tgbotxx/objects/InputMedia.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/KeyboardButton.hpp>
#include <tgbotxx/objects/KeyboardButtonPollType.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestChat.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestUser.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
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
#include <tgbotxx/objects/WriteAccessAllowed.hpp>
#include <variant>
namespace nl = nlohmann;

namespace tgbotxx {
  /// @brief Api Methods https://core.telegram.org/bots/api#available-methods
  /// @note All methods in the Bot API are case-insensitive.
  /// @note We support GET and POST HTTP methods. Use either URL query string or application/json or application/x-www-form-urlencoded or multipart/form-data for passing parameters in Bot API requests.
  class Api {
      inline static const std::string BASE_URL = "https://api.telegram.org";
      inline static const cpr::Timeout TIMEOUT = 25 * 1000;                // 25s (Telegram server can take up to 25s to reply us (should be longer than long poll timeout)). Max long polling timeout seems to be 50s.
      inline static const cpr::Timeout FILES_UPLOAD_TIMEOUT = 300 * 1000;  // 5min (Files can take longer time to upload. Setting a shorter timeout can stop the request even if the file isn't fully uploaded)
      inline static const cpr::ConnectTimeout CONNECT_TIMEOUT = 20 * 1000; // 20s (Telegram server can take up to 20s to connect with us)
      inline static const std::int32_t LONG_POLL_TIMEOUT = 10;             // 10s (calling getUpdates() every 10 seconds)
      const std::string m_token;

    public:
      /// @brief Constructs Api object.
      /// @param token Bot Token from FatherBot.
      Api(const std::string& token);

    public:
      /// @brief A simple method for testing your bot's authentication token.
      /// @returns basic information about the bot in form of a User object.
      Ptr<User> getMe() const;

      /// @brief Use this method to log out from the cloud Bot API server before launching the bot locally.
      /// You must log out the bot before running it locally, otherwise there is no guarantee that the bot will receive updates.
      /// After a successful call, you can immediately log in on a local server, but will not be able to log in back to the cloud Bot API server for 10 minutes.
      /// @returns true on success.
      /// @ref https://core.telegram.org/bots/api#logout
      bool logOut() const;

      /// @brief Use this method to close the bot instance before moving it from one local server to another.
      /// You need to delete the webhook before calling this method to ensure that the bot isn't launched again after server restart.
      /// The method will return error 429 in the first 10 minutes after the bot is launched.
      /// @returns true on success.
      /// @ref https://core.telegram.org/bots/api#close
      bool close() const;

      /// @brief Use this method to send text messages. On success, the sent Message is returned.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param text Text of the message to be sent, 1-4096 characters after entities parsing
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param parseMode Optional. Mode for parsing entities in the message text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param entities Optional. A JSON-serialized list of special entities that appear in message text, which can be specified instead of parseMode
      /// @param disableWebPagePreview Optional. Disables link previews for links in this message
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns sent Message object on success.
      /// @ref https://core.telegram.org/bots/api#sendmessage
      Ptr<Message> sendMessage(std::int64_t chatId,
                               const std::string& text,
                               std::int32_t messageThreadId = 0,
                               const std::string& parseMode = "",
                               const std::vector<Ptr<MessageEntity>>& entities = std::vector<Ptr<MessageEntity>>(),
                               bool disableWebPagePreview = false,
                               bool disableNotification = false,
                               bool protectContent = false,
                               std::int32_t replyToMessageId = 0,
                               bool allowSendingWithoutReply = false,
                               const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;

      /// @brief Use this method to forward messages of any kind. Service messages can't be forwarded.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param fromChatId Unique identifier for the chat where the original message was sent (or channel username in the format \@channelusername)
      /// @param messageId Message identifier in the chat specified in fromChatId
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#forwardmessage
      Ptr<Message> forwardMessage(std::int64_t chatId,
                                  std::int64_t fromChatId,
                                  std::int32_t messageId,
                                  std::int32_t messageThreadId = 0,
                                  bool disableNotification = false,
                                  bool protectContent = false) const;

      /// @brief Use this method to copy messages of any kind. Service messages and invoice messages can't be copied.
      /// A quiz poll can be copied only if the value of the field correct_option_id is known to the bot.
      /// The method is analogous to the method forwardMessage, but the copied message doesn't have a link to the original message.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param fromChatId Unique identifier for the chat where the original message was sent (or channel username in the format \@channelusername)
      /// @param messageId Message identifier in the chat specified in fromChatId
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param caption Optional. New caption for media, 0-1024 characters after entities parsing. If not specified, the original caption is kept
      /// @param parseMode Optional. Mode for parsing entities in the message text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param disableWebPagePreview Optional. Disables link previews for links in this message
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the MessageId of the sent message on success.
      /// @ref https://core.telegram.org/bots/api#copymessage
      Ptr<MessageId> copyMessage(std::int64_t chatId,
                                 std::int64_t fromChatId,
                                 std::int32_t messageId,
                                 std::int32_t messageThreadId = 0,
                                 const std::string& caption = "",
                                 const std::string& parseMode = "",
                                 const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                                 bool disableNotification = false,
                                 bool protectContent = false,
                                 std::int32_t replyToMessageId = 0,
                                 bool allowSendingWithoutReply = false,
                                 const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;

      /// @brief Use this method to send photos.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param photo Photo to send. cpr::File or std::string.
      /// Pass a fileId as String to send a photo that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a photo from the Internet, or upload a new photo using multipart/form-data.
      /// The photo must be at most 10 MB in size. The photo's width and height must not exceed 10000 in total.
      /// Width and height ratio must be at most 20.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param caption Optional. Photo caption (may also be used when resending photos by file_id), 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the photo caption. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#sendphoto
      Ptr<Message> sendPhoto(std::int64_t chatId,
                             std::variant<cpr::File, std::string> photo,
                             std::int32_t messageThreadId = 0,
                             const std::string& caption = "",
                             const std::string& parseMode = "",
                             const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;

      /// @brief Use this method to send audio files, if you want Telegram clients to display them in the music player.
      /// Your audio must be in the .MP3 or .M4A format.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param audio Audio file to send. cpr::File or std::string.
      /// Pass a fileId as String to send an audio file that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get an audio file from the Internet, or upload a new one using multipart/form-data.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param caption Optional. Audio caption, 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the audio caption. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param duration Optional. Duration of the audio in seconds
      /// @param performer Optional. Performer
      /// @param title Optional. Track name
      /// @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
      /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
      /// Ignored if the file is not uploaded using multipart/form-data.
      /// Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future.
      /// @note For sending voice messages, use the sendVoice method instead.
      /// @ref https://core.telegram.org/bots/api#sendaudio
      Ptr<Message> sendAudio(std::int64_t chatId,
                             std::variant<cpr::File, std::string> audio,
                             std::int32_t messageThreadId = 0,
                             const std::string& caption = "",
                             const std::string& parseMode = "",
                             const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                             std::int32_t duration = 0,
                             const std::string& performer = "",
                             const std::string& title = "",
                             std::optional<std::variant<cpr::File, std::string>> thumbnail = std::nullopt,
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send general files.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param document File to send.
      /// Pass a file_id as String to send a file that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data.
      /// More information on Sending Files » » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
      /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
      /// Ignored if the file is not uploaded using multipart/form-data.
      /// Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param caption Optional. Document caption (may also be used when resending documents by file_id), 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the document text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future.
      /// @note For sending voice messages, use the sendVoice method instead.
      /// @ref https://core.telegram.org/bots/api#senddocument
      Ptr<Message> sendDocument(std::int64_t chatId,
                                std::variant<cpr::File, std::string> document,
                                std::int32_t messageThreadId = 0,
                                std::optional<std::variant<cpr::File, std::string>> thumbnail = std::nullopt,
                                const std::string& caption = "",
                                const std::string& parseMode = "",
                                const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                                bool disableNotification = false,
                                bool protectContent = false,
                                std::int32_t replyToMessageId = 0,
                                bool allowSendingWithoutReply = false,
                                const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send video files, Telegram clients support MPEG4 videos (other formats may be sent as Document using Api::sendDocument()).
      /// Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param video Video to send.
      /// Pass a fileId as String to send a video that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new video using multipart/form-data.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param duration Optional. Duration of sent video in seconds
      /// @param width Optional. Video width
      /// @param height Optional. Video height
      /// @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
      /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
      /// Ignored if the file is not uploaded using multipart/form-data.
      /// Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param caption Optional. Video caption (may also be used when resending videos by file_id), 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the video caption. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param hasSpoiler Optional. Pass True if the video needs to be covered with a spoiler animation
      /// @param supportsStreaming Optional. Pass True if the uploaded video is suitable for streaming
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvideo
      Ptr<Message> sendVideo(std::int64_t chatId,
                             std::variant<cpr::File, std::string> video,
                             std::int32_t messageThreadId = 0,
                             std::int32_t duration = 0,
                             std::int32_t width = 0,
                             std::int32_t height = 0,
                             std::optional<std::variant<cpr::File, std::string>> thumbnail = std::nullopt,
                             const std::string& caption = "",
                             const std::string& parseMode = "",
                             const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                             bool hasSpoiler = false,
                             bool supportsStreaming = false,
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send animation files (GIF or H.264/MPEG-4 AVC video without sound).
      /// Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param animation Animation to send.
      /// Pass a fileId as String to send an animation that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a animation from the Internet, or upload a new animation using multipart/form-data.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param duration Optional. Duration of sent animation in seconds
      /// @param width Optional. Animation width
      /// @param height Optional. Animation height
      /// @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
      /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
      /// Ignored if the file is not uploaded using multipart/form-data.
      /// Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param caption Optional. Animation caption (may also be used when resending animation by file_id), 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the animation caption. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param hasSpoiler Optional. Pass True if the animation needs to be covered with a spoiler animation
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendanimation
      Ptr<Message> sendAnimation(std::int64_t chatId,
                                 std::variant<cpr::File, std::string> animation,
                                 std::int32_t messageThreadId = 0,
                                 std::int32_t duration = 0,
                                 std::int32_t width = 0,
                                 std::int32_t height = 0,
                                 std::optional<std::variant<cpr::File, std::string>> thumbnail = std::nullopt,
                                 const std::string& caption = "",
                                 const std::string& parseMode = "",
                                 const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                                 bool hasSpoiler = false,
                                 bool disableNotification = false,
                                 bool protectContent = false,
                                 std::int32_t replyToMessageId = 0,
                                 bool allowSendingWithoutReply = false,
                                 const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send audio files, if you want Telegram clients to display the file as a playable voice message.
      /// For this to work, your audio must be in an .OGG file encoded with OPUS (other formats may be sent as Audio or Document).
      /// Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param voice Audio file to send.
      /// Pass a fileId as String to send a file that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new file using multipart/form-data.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param caption Optional. Voice message caption, 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the voice message caption. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param duration Optional. Duration of the voice message in seconds
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvoice
      Ptr<Message> sendVoice(std::int64_t chatId,
                             std::variant<cpr::File, std::string> voice,
                             std::int32_t messageThreadId = 0,
                             const std::string& caption = "",
                             const std::string& parseMode = "",
                             const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                             std::int32_t duration = 0,
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief As of v.4.0, Telegram clients support rounded square MPEG4 videos of up to 1 minute long.
      /// Use this method to send video messages. https://telegram.org/blog/video-messages-and-telescope
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param videoNote Video note to send.
      /// Pass a fileId as String to send a video note that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL as a String for Telegram to get a video from the Internet, or upload a new video using multipart/form-data.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param duration Optional. Duration of sent video in seconds
      /// @param length Optional. Video width and height, i.e. diameter of the video message
      /// @param thumbnail Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
      /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
      /// Ignored if the file is not uploaded using multipart/form-data.
      /// Thumbnails can't be reused and can be only uploaded as a new file, so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @note Sending video notes by a URL is currently unsupported
      /// @note Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvideonote
      Ptr<Message> sendVideoNote(std::int64_t chatId,
                                 std::variant<cpr::File, std::string> videoNote,
                                 std::int32_t messageThreadId = 0,
                                 std::int32_t duration = 0,
                                 std::int32_t length = 0,
                                 std::optional<std::variant<cpr::File, std::string>> thumbnail = std::nullopt,
                                 bool disableNotification = false,
                                 bool protectContent = false,
                                 std::int32_t replyToMessageId = 0,
                                 bool allowSendingWithoutReply = false,
                                 const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send a group of photos, videos, documents or audios as an album.
      /// Documents and audio files can be only grouped in an album with messages of the same type.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param media A JSON-serialized array describing messages to be sent, must include 2-10 items.
      /// Array of InputMediaAudio, InputMediaDocument, InputMediaPhoto and InputMediaVideo
      /// https://core.telegram.org/bots/api#inputmedia
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @returns an array of Messages that were sent.
      /// @note Documents and audio files can be only grouped in an album with messages of the same type.
      /// @ref https://core.telegram.org/bots/api#sendmediagroup
      std::vector<Ptr<Message>> sendMediaGroup(std::int64_t chatId,
                                               const std::vector<Ptr<InputMedia>>& media,
                                               std::int32_t messageThreadId = 0,
                                               bool disableNotification = false,
                                               bool protectContent = false,
                                               std::int32_t replyToMessageId = 0,
                                               bool allowSendingWithoutReply = false) const;


      /// @brief Use this method to send point on the map.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param latitude Latitude of the location
      /// @param longitude Longitude of the location
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
      /// @param livePeriod Optional. Period in seconds for which the location will be updated (see Live Locations, should be between 60 and 86400. https://telegram.org/blog/live-locations
      /// @param heading Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
      /// @param proximityAlertRadius Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#sendlocation
      Ptr<Message> sendLocation(std::int64_t chatId,
                                float latitude,
                                float longitude,
                                std::int32_t messageThreadId = 0,
                                float horizontalAccuracy = 0.0f,
                                std::int32_t livePeriod = 0,
                                std::int32_t heading = 0,
                                std::int32_t proximityAlertRadius = 0,
                                bool disableNotification = false,
                                bool protectContent = false,
                                std::int32_t replyToMessageId = 0,
                                bool allowSendingWithoutReply = false,
                                const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send information about a venue.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param latitude Latitude of the venue
      /// @param longitude Longitude of the venue
      /// @param title Name of the venue
      /// @param address Address of the venue
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param foursquareId Optional. Foursquare identifier of the venue
      /// @param foursquareType Optional. Foursquare type of the venue, if known. (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
      /// @param googlePlaceId Optional. Google Places identifier of the venue
      /// @param googlePlaceType Optional. Google Places type of the venue. (See supported types. https://developers.google.com/places/web-service/supported_types)
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#sendvenue
      Ptr<Message> sendVenue(std::int64_t chatId,
                             float latitude,
                             float longitude,
                             const std::string& title,
                             const std::string& address,
                             std::int32_t messageThreadId = 0,
                             const std::string& foursquareId = "",
                             const std::string& foursquareType = "",
                             const std::string& googlePlaceId = "",
                             const std::string& googlePlaceType = "",
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send phone contacts.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param phoneNumber Contact's phone number
      /// @param firstName Contact's first name
      /// @param lastName Optional. Contact's last name
      /// @param vcard Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes https://en.wikipedia.org/wiki/VCard
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#sendcontact
      Ptr<Message> sendContact(std::int64_t chatId,
                               const std::string& phoneNumber,
                               const std::string& firstName,
                               const std::string& lastName = "",
                               const std::string& vcard = "",
                               std::int32_t messageThreadId = 0,
                               bool disableNotification = false,
                               bool protectContent = false,
                               std::int32_t replyToMessageId = 0,
                               bool allowSendingWithoutReply = false,
                               const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send a native poll.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param question Poll question, 1-300 characters
      /// @param options A list of answer options, 2-10 strings 1-100 characters each
      /// @param isAnonymous Optional. True, if the poll needs to be anonymous, defaults to True
      /// @param type Optional. Poll type, “quiz” or “regular”, defaults to “regular”
      /// @param allowsMultipleAnswers Optional. True, if the poll allows multiple answers, ignored for polls in quiz mode, defaults to False
      /// @param correctOptionId Optional. 0-based identifier of the correct answer option, required for polls in quiz mode
      /// @param explanation Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters with at most 2 line feeds after entities parsing
      /// @param explanationParseMode Optional. Mode for parsing entities in the explanation. See formatting options for more details.
      /// @param explanationEntities Optional. A JSON-serialized list of special entities that appear in the poll explanation, which can be specified instead of parseMode
      /// @param openPeriod Optional. Amount of time in seconds the poll will be active after creation, 5-600. Can't be used together with closeDate.
      /// @param closeDate Optional. Point in time (Unix timestamp) when the poll will be automatically closed. Must be at least 5 and no more than 600 seconds in the future. Can't be used together with openPeriod.
      /// @param isClosed Optional. Pass True if the poll needs to be immediately closed. This can be useful for poll preview.
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#sendpoll
      Ptr<Message> sendPoll(std::int64_t chatId,
                            const std::string& question,
                            const std::vector<std::string>& options,
                            bool isAnonymous = false,
                            const std::string& type = "regular",
                            bool allowsMultipleAnswers = false,
                            std::int32_t correctOptionId = -1,
                            const std::string& explanation = "",
                            const std::string& explanationParseMode = "",
                            const std::vector<Ptr<MessageEntity>>& explanationEntities = std::vector<Ptr<MessageEntity>>(),
                            std::int32_t openPeriod = 0,
                            std::int32_t closeDate = 0,
                            bool isClosed = false,
                            std::int32_t messageThreadId = 0,
                            bool disableNotification = false,
                            bool protectContent = false,
                            std::int32_t replyToMessageId = 0,
                            bool allowSendingWithoutReply = false,
                            const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send an animated emoji that will display a random value.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param emoji Optional. Emoji on which the dice throw animation is based. Currently, must be one of “🎲”, “🎯”, “🏀”, “⚽”, “🎳”, or “🎰”.
      /// Dice can have values 1-6 for “🎲”, “🎯” and “🎳”, values 1-5 for “🏀” and “⚽”, and values 1-64 for “🎰”. Defaults to “🎲”
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message on success.
      /// @ref https://core.telegram.org/bots/api#senddice
      Ptr<Message> sendDice(std::int64_t chatId,
                            const std::string& emoji = "🎲",
                            std::int32_t messageThreadId = 0,
                            bool disableNotification = false,
                            bool protectContent = false,
                            std::int32_t replyToMessageId = 0,
                            bool allowSendingWithoutReply = false,
                            const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method when you need to tell the user that something is happening on the bot's side.
      /// The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param action Type of action to broadcast. Choose one, depending on what the user is about to receive:
      /// - "typing" for text messages
      /// - "upload_photo" for photos
      /// - "record_video" or upload_video for videos
      /// - "record_voice" or upload_voice for voice notes
      /// - "upload_document" for general files
      /// - "choose_sticker" for stickers
      /// - "find_location" for location data
      /// - "record_video_note"
      /// - "upload_video_note" for video notes
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @returns True on success.
      /// @example Example: The ImageBot needs some time to process a request and upload the image. https://t.me/imagebot
      /// Instead of sending a text message along the lines of “Retrieving image, please wait…”,
      /// the bot may use sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
      /// @note We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
      /// @ref https://core.telegram.org/bots/api#sendchataction
      bool sendChatAction(std::int64_t chatId,
                          const std::string& action,
                          std::int32_t messageThreadId = 0) const;


      /// @brief Use this method to get a list of profile pictures for a user.
      /// @param userId Unique identifier of the target user
      /// @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
      /// @param limit Optional. Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults to 100.
      /// @returns UserProfilePhotos object.
      /// @ref https://core.telegram.org/bots/api#getuserprofilephotos
      Ptr<UserProfilePhotos> getUserProfilePhotos(std::int64_t userId,
                                                  std::int32_t offset = 0,
                                                  std::int32_t limit = 100) const;


      /// @brief Use this method to get basic information about a file and prepare it for downloading.
      /// For the moment, bots can download files of up to 20MB in size.
      /// The file can then be downloaded using Api::downloadFile or via the link https://api.telegram.org/file/bot<token>/<file_path>, where <file_path> is taken from the response.
      /// @param fileId File identifier to get information about
      /// @returns a File object is returned on success.
      /// @note It is guaranteed that the link will be valid for at least 1 hour. When the link expires, a new one can be requested by calling getFile again.
      /// @note This function may not preserve the original file name and MIME type. You should save the file's MIME type and name (if available) when the File object is received.
      /// @ref https://core.telegram.org/bots/api#getfile
      Ptr<File> getFile(const std::string& fileId) const;


      /// @brief Use this method to download a file from Telegram and save it in memory.
      /// For the moment, bots can download files of up to 20MB in size. See Api::getFile.
      /// The file can then be downloaded via the link https://api.telegram.org/file/bot<token>/<file_path>, where <file_path> is taken from the response.
      /// @param filePath Telegram file path from Api::getFile(fileId) -> File::filePath
      /// @param progressCallback Optional. Download progress callback. Callback shall return true to continue downloading, or false to cancel the download.
      /// @returns std::string contains downloaded file contents.
      /// @ref https://core.telegram.org/bots/api#getfile
      /// @throws Exception on failure
      std::string downloadFile(const std::string& filePath, const std::function<bool(cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow)>& progressCallback = nullptr) const;


      /// @brief Use this method to ban a user in a group, a supergroup or a channel.
      /// In the case of supergroups and channels, the user will not be able to return to the chat on their own using invite links, etc., unless unbanned first.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights. https://core.telegram.org/bots/api#unbanchatmember
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param untilDate Optional. Date when the user will be unbanned; Unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever. .
      /// AApplied for supergroups and channels only.
      /// @param revokeMessages Optional. Pass True to delete all messages from the chat for the user that is being removed. If False, the user will be able to see messages in the group that were sent before the user was removed. Always True for supergroups and channels.
      /// @returns True on success.
      /// @note You can't ban members in private chats
      /// @ref https://core.telegram.org/bots/api#banchatmember
      bool banChatMember(std::int64_t chatId,
                         std::int64_t userId,
                         std::time_t untilDate = 0,
                         bool revokeMessages = false) const;


      /// @brief Use this method to unban a previously banned user in a supergroup or channel.
      /// The user will not return to the group or channel automatically, but will be able to join via link, etc.
      /// The bot must be an administrator for this to work. By default, this method guarantees that after the call the user is not a member of the chat,
      /// but will be able to join it. So if the user is a member of the chat they will also be removed from the chat. If you don't want this,
      /// use the parameter onlyIfBanned.
      /// @param chatId Integer Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param onlyIfBanned Optional. Do nothing if the user is not banned
      /// @returns True on success.
      /// @ref https://core.telegram.org/bots/api#unbanchatmember
      bool unbanChatMember(std::int64_t chatId,
                           std::int64_t userId,
                           bool onlyIfBanned = false) const;


      /// @brief Use this method to remove webhook integration if you decide to switch back to getUpdates.
      /// Returns True on success.
      /// @param dropPendingUpdates: Pass True to drop all pending updates.
      /// @note when Bot is not running, updates will remain 24 hours in Telegram server before they get deleted or retrieved by BOT
      /// @note In order for Api::getUpdates() to work, there should be no outgoing webhook set up.
      /// see https://core.telegram.org/bots/api#getupdates
      /// @link ref https://core.telegram.org/bots/api#deletewebhook @endlink
      bool deleteWebhook(bool dropPendingUpdates = false) const;

      /// @brief Use this method to receive incoming updates using long polling.
      /// @param offset Identifier of the first update to be returned. Must be greater by one than the highest
      /// among the identifiers of previously received updates. By default, updates starting with the earliest
      /// unconfirmed update are returned. An update is considered confirmed as soon as getUpdates is called
      /// with an offset higher than its update_id. The negative offset can be specified to retrieve updates
      /// starting from -offset update from the end of the updates queue. All previous updates will be forgotten.
      /// @param limit Limits the number of updates to be retrieved. Values between 1-100 are accepted. Defaults to 100.
      /// @param timeout Timeout in seconds for long polling. Defaults to 0, i.e. usual short polling. Should be positive,
      /// short polling should be used for testing purposes only.
      /// @param allowedUpdates JSON-serialized list of the update types you want your bot to receive.
      /// For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types.
      /// See Update for a complete list of available update types. Specify an empty list to receive all update types
      /// except chat_member (default). If not specified, the previous setting will be used.
      /// @returns an Array of Update objects.
      /// @note Please note that this parameter doesn't affect updates created before the call to the getUpdates, so unwanted updates may be received for a short period of time.
      /// @note This method will not work if an outgoing webhook is set up.
      /// @note In order to avoid getting duplicate updates, recalculate offset after each server response.
      /// @link ref https://core.telegram.org/bots/api#getupdates @endlink
      std::vector<Ptr<Update>> getUpdates(std::int32_t offset, std::int32_t limit = 100, std::int32_t timeout = LONG_POLL_TIMEOUT, const std::vector<std::string>& allowedUpdates = {}) const;

    public: /// @defgroup Commands
      /// @brief Use this method to change the list of the bot's commands.
      /// See this manual for more details about bot commands.
      /// @param commands A JSON-serialized list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
      /// @param scope A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
      /// @param languageCode A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
      /// @returns true on success.
      /// @link ref https://core.telegram.org/bots/api#setmycommands @endlink
      bool setMyCommands(const std::vector<Ptr<BotCommand>>& commands, const Ptr<BotCommandScope>& scope = nullptr, const std::string& languageCode = "") const;


      /// @brief Use this method to get the current list of the bot's commands for the given scope and user language.
      /// @param scope A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
      /// @param languageCode A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
      /// @returns an Array of BotCommand objects. If commands aren't set, an empty list is returned.
      /// @link ref https://core.telegram.org/bots/api#getmycommands @endlink
      std::vector<Ptr<BotCommand>> getMyCommands(const Ptr<BotCommandScope>& scope = nullptr, const std::string& languageCode = "") const;

      /// Todo: ...

    private:
      nl::json sendRequest(const std::string& endpoint, const cpr::Multipart& data = cpr::Multipart({})) const;
  };
}