#pragma once
#include <cpr/cpr.h>
#include <cstdint>
#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <tgbotxx/utils/DateTimeUtils.hpp>
#include <tgbotxx/utils/Ptr.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
#include <variant>
namespace nl = nlohmann;

namespace tgbotxx {
  /// @brief Forward declarations
  struct User;
  struct Message;
  struct Update;
  struct Chat;
  struct MessageEntity;
  struct IReplyMarkup;
  struct MessageId;
  struct InputMedia;
  struct UserProfilePhotos;
  struct File;
  struct ChatMember;
  struct ChatPermissions;
  struct ChatInviteLink;
  struct Sticker;
  struct ForumTopic;
  struct BotCommand;
  struct BotCommandScope;
  struct BotName;
  struct BotShortDescription;
  struct BotDescription;
  struct InlineQueryResult;
  struct InlineQueryResultsButton;
  struct MenuButton;
  struct ChatAdministratorRights;
  struct WebhookInfo;
  struct Poll;
  struct LabeledPrice;
  struct ShippingOption;
  struct SentWebAppMessage;
  struct ReplyParameters;
  struct StickerSet;
  struct InputSticker;
  struct MaskPosition;

  /// @brief Api Methods https://core.telegram.org/bots/api#available-methods
  /// @note All methods in the Bot API are case-insensitive.
  /// @note We support GET and POST HTTP methods. Use either URL query string or application/json or application/x-www-form-urlencoded or multipart/form-data for passing parameters in Bot API requests.
  class Api {
      static const std::string DEFAULT_API_URL;                 /// Telegram api base url
      static const cpr::ConnectTimeout DEFAULT_CONNECT_TIMEOUT; /// 20s (Telegram server can take up to 20s to connect with us)
      static const cpr::Timeout DEFAULT_TIMEOUT;                /// 70s (Telegram server can take up to 70s to reply us (should be longer than long poll timeout)).
      static const cpr::Timeout DEFAULT_LONG_POLL_TIMEOUT;      /// 60s (long polling getUpdates() every 60 seconds) Telegram's guidelines recommended a timeout between 30 and 90 seconds for long polling.
      static const cpr::Timeout DEFAULT_UPLOAD_FILES_TIMEOUT;   /// 15min (Files can take longer time to upload. Setting a shorter timeout will stop the request even if the file isn't fully uploaded)
      static const cpr::Timeout DEFAULT_DOWNLOAD_FILES_TIMEOUT; /// 30min (Files can take longer time to download. Setting a shorter timeout will stop the request even if the file isn't fully downloaded)

      const std::string m_token;                                            /// Bot token from \@BotFather
      std::string m_apiUrl = DEFAULT_API_URL;                               /// Api URL. Either DEFAULT_API_URL or local Telegram Bot server URL (example: http://0.0.0.0:8081). See how to build and start your own tg bot server locally https://t.ly/ZmqK3
      cpr::ConnectTimeout m_connectTimeout = DEFAULT_CONNECT_TIMEOUT;       /// Api connection timeout
      cpr::Timeout m_timeout = DEFAULT_TIMEOUT;                             /// Api requests timeout
      cpr::Timeout m_longPollTimeout = DEFAULT_LONG_POLL_TIMEOUT;           /// Long polling timeout
      cpr::Timeout m_uploadFilesTimeout = DEFAULT_UPLOAD_FILES_TIMEOUT;     /// Api files upload timeout
      cpr::Timeout m_downloadFilesTimeout = DEFAULT_DOWNLOAD_FILES_TIMEOUT; /// Api files download timeout

      friend class Bot;

    public:
      /// @brief Constructs Api object.
      /// @param token Bot Token from FatherBot.
      explicit Api(const std::string& token);

    public: /// Bot Api Methods https://core.telegram.org/bots/api#available-methods
      /// @brief A simple method for testing your bot's authentication token.
      /// @returns basic information about the bot in form of a User object.
      /// @throws Exception on failure
      Ptr<User> getMe() const;

      /// @brief Use this method to log out from the cloud Bot API server before launching the bot locally.
      /// You must log out the bot before running it locally, otherwise there is no guarantee that the bot will receive updates.
      /// After a successful call, you can immediately log in on a local server, but will not be able to log in back to the cloud Bot API server for 10 minutes.
      /// @returns true on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#logout
      bool logOut() const;

      /// @brief Use this method to close the bot instance before moving it from one local server to another.
      /// You need to delete the webhook before calling this method to ensure that the bot isn't launched again after server restart.
      /// The method will return error 429 in the first 10 minutes after the bot is launched.
      /// @returns true on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#close
      bool close() const;

      /// @brief Use this method to send text messages. On success, the sent Message is returned.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format @channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendmessage
      Ptr<Message> sendMessage(const std::variant<std::int64_t, std::string>& chatId,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param fromChatId Integer or String Unique identifier for the chat where the original message was sent (or channel username in the format \@channelusername)
      /// @param messageId Message identifier in the chat specified in fromChatId
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @returns the sent Message on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#forwardmessage
      Ptr<Message> forwardMessage(const std::variant<std::int64_t, std::string>& chatId,
                                  const std::variant<std::int64_t, std::string>& fromChatId,
                                  std::int32_t messageId,
                                  std::int32_t messageThreadId = 0,
                                  bool disableNotification = false,
                                  bool protectContent = false) const;

      /// @brief Use this method to copy messages of any kind. Service messages and invoice messages can't be copied.
      /// A quiz poll can be copied only if the value of the field correct_option_id is known to the bot.
      /// The method is analogous to the method forwardMessage, but the copied message doesn't have a link to the original message.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param fromChatId Integer or String identifier for the chat where the original message was sent (or channel username in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#copymessage
      Ptr<MessageId> copyMessage(const std::variant<std::int64_t, std::string>& chatId,
                                 const std::variant<std::int64_t, std::string>& fromChatId,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendphoto
      Ptr<Message> sendPhoto(const std::variant<std::int64_t, std::string>& chatId,
                             const std::variant<cpr::File, std::string>& photo,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Bots can currently send audio files of up to 50 MB in size, this limit may be changed in the future.
      /// @note For sending voice messages, use the sendVoice method instead.
      /// @ref https://core.telegram.org/bots/api#sendaudio
      Ptr<Message> sendAudio(const std::variant<std::int64_t, std::string>& chatId,
                             const std::variant<cpr::File, std::string>& audio,
                             std::int32_t messageThreadId = 0,
                             const std::string& caption = "",
                             const std::string& parseMode = "",
                             const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                             std::int32_t duration = 0,
                             const std::string& performer = "",
                             const std::string& title = "",
                             const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt,
                             bool disableNotification = false,
                             bool protectContent = false,
                             std::int32_t replyToMessageId = 0,
                             bool allowSendingWithoutReply = false,
                             const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send general files.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Bots can currently send files of any type of up to 50 MB in size, this limit may be changed in the future.
      /// @note For sending voice messages, use the sendVoice method instead.
      /// @ref https://core.telegram.org/bots/api#senddocument
      Ptr<Message> sendDocument(const std::variant<std::int64_t, std::string>& chatId,
                                const std::variant<cpr::File, std::string>& document,
                                std::int32_t messageThreadId = 0,
                                const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvideo
      Ptr<Message> sendVideo(const std::variant<std::int64_t, std::string>& chatId,
                             const std::variant<cpr::File, std::string>& video,
                             std::int32_t messageThreadId = 0,
                             std::int32_t duration = 0,
                             std::int32_t width = 0,
                             std::int32_t height = 0,
                             const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Bots can currently send animation files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendanimation
      Ptr<Message> sendAnimation(const std::variant<std::int64_t, std::string>& chatId,
                                 const std::variant<cpr::File, std::string>& animation,
                                 std::int32_t messageThreadId = 0,
                                 std::int32_t duration = 0,
                                 std::int32_t width = 0,
                                 std::int32_t height = 0,
                                 const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Bots can currently send voice messages of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvoice
      Ptr<Message> sendVoice(const std::variant<std::int64_t, std::string>& chatId,
                             const std::variant<cpr::File, std::string>& voice,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @note Sending video notes by a URL is currently unsupported
      /// @note Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
      /// @ref https://core.telegram.org/bots/api#sendvideonote
      Ptr<Message> sendVideoNote(const std::variant<std::int64_t, std::string>& chatId,
                                 const std::variant<cpr::File, std::string>& videoNote,
                                 std::int32_t messageThreadId = 0,
                                 std::int32_t duration = 0,
                                 std::int32_t length = 0,
                                 const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt,
                                 bool disableNotification = false,
                                 bool protectContent = false,
                                 std::int32_t replyToMessageId = 0,
                                 bool allowSendingWithoutReply = false,
                                 const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to send a group of photos, videos, documents or audios as an album.
      /// Documents and audio files can be only grouped in an album with messages of the same type.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param media A JSON-serialized array describing messages to be sent, must include 2-10 items.
      /// Array of InputMediaAudio, InputMediaDocument, InputMediaPhoto and InputMediaVideo
      /// https://core.telegram.org/bots/api#inputmedia
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @returns an array of Messages that were sent.
      /// @throws Exception on failure
      /// @note Documents and audio files can be only grouped in an album with messages of the same type.
      /// @ref https://core.telegram.org/bots/api#sendmediagroup
      std::vector<Ptr<Message>> sendMediaGroup(const std::variant<std::int64_t, std::string>& chatId,
                                               const std::vector<Ptr<InputMedia>>& media,
                                               std::int32_t messageThreadId = 0,
                                               bool disableNotification = false,
                                               bool protectContent = false,
                                               std::int32_t replyToMessageId = 0,
                                               bool allowSendingWithoutReply = false) const;


      /// @brief Use this method to send point on the map.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendlocation
      Ptr<Message> sendLocation(const std::variant<std::int64_t, std::string>& chatId,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendvenue
      Ptr<Message> sendVenue(const std::variant<std::int64_t, std::string>& chatId,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendcontact
      Ptr<Message> sendContact(const std::variant<std::int64_t, std::string>& chatId,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendpoll
      Ptr<Message> sendPoll(const std::variant<std::int64_t, std::string>& chatId,
                            const std::string& question,
                            const std::vector<std::string>& options,
                            bool isAnonymous = true,
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
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#senddice
      Ptr<Message> sendDice(const std::variant<std::int64_t, std::string>& chatId,
                            const std::string& emoji = "🎲",
                            std::int32_t messageThreadId = 0,
                            bool disableNotification = false,
                            bool protectContent = false,
                            std::int32_t replyToMessageId = 0,
                            bool allowSendingWithoutReply = false,
                            const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method when you need to tell the user that something is happening on the bot's side.
      /// The status is set for 5 seconds or less (when a message arrives from your bot, Telegram clients clear its typing status).
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
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
      /// @throws Exception on failure
      /// Example: The ImageBot needs some time to process a request and upload the image. https://t.me/imagebot
      /// Instead of sending a text message along the lines of “Retrieving image, please wait…”,
      /// the bot may use sendChatAction with action = upload_photo. The user will see a “sending photo” status for the bot.
      /// @note We only recommend using this method when a response from the bot will take a noticeable amount of time to arrive.
      /// @ref https://core.telegram.org/bots/api#sendchataction
      bool sendChatAction(const std::variant<std::int64_t, std::string>& chatId,
                          const std::string& action,
                          std::int32_t messageThreadId = 0) const;


      /// @brief Use this method to get a list of profile pictures for a user.
      /// @param userId Unique identifier of the target user
      /// @param offset Optional. Sequential number of the first photo to be returned. By default, all photos are returned.
      /// @param limit Optional. Limits the number of photos to be retrieved. Values between 1-100 are accepted. Defaults to 100.
      /// @returns UserProfilePhotos object.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getuserprofilephotos
      Ptr<UserProfilePhotos> getUserProfilePhotos(std::int64_t userId,
                                                  std::int32_t offset = 0,
                                                  std::int32_t limit = 100) const;


      /// @brief Use this method to get basic information about a file and prepare it for downloading.
      /// For the moment, bots can download files of up to 20MB in size.
      /// The file can then be downloaded using Api::downloadFile or via the link https://api.telegram.org/file/bot<token>/<file_path>, where <file_path> is taken from the response.
      /// @param fileId File identifier to get information about
      /// @returns a File object is returned on success.
      /// @throws Exception on failure
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
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getfile
      /// @throws Exception on failure
      std::string downloadFile(const std::string& filePath, const std::function<bool(cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow)>& progressCallback = nullptr) const;


      /// @brief Use this method to ban a user in a group, a supergroup or a channel.
      /// In the case of supergroups and channels, the user will not be able to return to the chat on their own using invite links, etc., unless unbanned first.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights. https://core.telegram.org/bots/api#unbanchatmember
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param untilDate Optional. Date when the user will be unbanned; Unix time. If user is banned for more than 366 days or less than 30 seconds from the current time they are considered to be banned forever. .
      /// AApplied for supergroups and channels only.
      /// @param revokeMessages Optional. Pass True to delete all messages from the chat for the user that is being removed. If False, the user will be able to see messages in the group that were sent before the user was removed. Always True for supergroups and channels.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @note You can't ban members in private chats
      /// @ref https://core.telegram.org/bots/api#banchatmember
      bool banChatMember(const std::variant<std::int64_t, std::string>& chatId,
                         std::int64_t userId,
                         std::time_t untilDate = 0,
                         bool revokeMessages = false) const;


      /// @brief Use this method to unban a previously banned user in a supergroup or channel.
      /// The user will not return to the group or channel automatically, but will be able to join via link, etc.
      /// The bot must be an administrator for this to work. By default, this method guarantees that after the call the user is not a member of the chat,
      /// but will be able to join it. So if the user is a member of the chat they will also be removed from the chat. If you don't want this,
      /// use the parameter onlyIfBanned.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param onlyIfBanned Optional. Do nothing if the user is not banned
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#unbanchatmember
      bool unbanChatMember(const std::variant<std::int64_t, std::string>& chatId,
                           std::int64_t userId,
                           bool onlyIfBanned = false) const;


      /// @brief Use this method to restrict a user in a supergroup.
      /// The bot must be an administrator in the supergroup for this to work and must have the appropriate administrator rights.
      /// Pass True for all permissions of ChatPermissions object to lift restrictions from a user.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param permissions A ChatPermissions object for new user permissions
      /// @param useIndependentChatPermissions Optional. Pass True if chat permissions are set independently. Otherwise,
      /// the can_send_other_messages and can_add_web_page_previews permissions will imply the can_send_messages, can_send_audios, can_send_documents, can_send_photos, can_send_videos, can_send_video_notes, and can_send_voice_notes permissions; the can_send_polls permission will imply the can_send_messages permission.
      /// @param untilDate Optional. Date when restrictions will be lifted for the user; Unix time.
      /// If user is restricted for more than 366 days or less than 30 seconds from the current time, they are considered to be restricted forever
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#restrictchatmember
      bool restrictChatMember(const std::variant<std::int64_t, std::string>& chatId,
                              std::int64_t userId,
                              const Ptr<ChatPermissions>& permissions,
                              bool useIndependentChatPermissions = false,
                              std::time_t untilDate = 0) const;


      /// @brief Use this method to promote or demote a user in a supergroup or a channel.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// Pass False for all boolean parameters to demote a user.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param isAnonymous Optional. Pass True if the administrator's presence in the chat is hidden
      /// @param canManageChat Optional. Pass True if the administrator can access the chat event log, boost list in channels, see channel members,
      /// report spam messages, see anonymous administrators in supergroups and ignore slow mode. Implied by any other administrator privilege
      /// @param canDeleteMessages Optional. Pass True if the administrator can delete messages of other users
      /// @param canManageVideoChats Optional. Pass True if the administrator can manage video chats
      /// @param canRestrictMembers Optional. Pass True if the administrator can restrict, ban or unban chat members, or access supergroup statistics
      /// @param canPromoteMembers Optional. Pass True if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted, directly or indirectly (promoted by administrators that were appointed by him)
      /// @param canChangeInfo Optional. Pass True if the administrator can change chat title, photo and other settings
      /// @param canInviteUsers Optional. Pass True if the administrator can invite new users to the chat
      /// @param canPostMessages Optional. Pass True if the administrator can post messages in the channel, or access channel statistics; channels only
      /// @param canEditMessages Optional. Pass True if the administrator can edit messages of other users and can pin messages; channels only
      /// @param canPinMessages Optional. Pass True if the administrator can pin messages, supergroups only
      /// @param canPostStories Optional. Pass True if the administrator can post stories in the channel; channels only
      /// @param canEditStories Optional. Pass True if the administrator can edit stories posted by other users; channels only
      /// @param canDeleteStories Optional. Pass True if the administrator can delete stories posted by other users; channels only
      /// @param canManageTopics Optional. Pass True if the user is allowed to create, rename, close, and reopen forum topics, supergroups only
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#promotechatmember
      bool promoteChatMember(const std::variant<std::int64_t, std::string>& chatId,
                             std::int64_t userId,
                             bool isAnonymous = false,
                             bool canManageChat = false,
                             bool canDeleteMessages = false,
                             bool canManageVideoChats = false,
                             bool canRestrictMembers = false,
                             bool canPromoteMembers = false,
                             bool canChangeInfo = false,
                             bool canInviteUsers = false,
                             bool canPostMessages = false,
                             bool canEditMessages = false,
                             bool canPinMessages = false,
                             bool canPostStories = false,
                             bool canEditStories = false,
                             bool canDeleteStories = false,
                             bool canManageTopics = false) const;


      /// @brief Use this method to set a custom title for an administrator in a supergroup promoted by the bot.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @param customTitle New custom title for the administrator; 0-16 characters, emoji are not allowed
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setchatadministratorcustomtitle
      bool setChatAdministratorCustomTitle(const std::variant<std::int64_t, std::string>& chatId,
                                           std::int64_t userId,
                                           const std::string& customTitle) const;


      /// @brief Use this method to ban a channel chat in a supergroup or a channel.
      /// Until the chat is unbanned, the owner of the banned chat won't be able to send messages on behalf of <b>any of their channels</b>.
      /// The bot must be an administrator in the supergroup or channel for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param senderChatId Unique identifier of the target sender chat
      /// @param customTitle New custom title for the administrator; 0-16 characters, emoji are not allowed
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso unbanChatSenderChat
      /// @ref https://core.telegram.org/bots/api#banchatsenderchat
      bool banChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                             std::int64_t senderChatId) const;


      /// @brief Use this method to unban a previously banned channel chat in a supergroup or channel.
      /// The bot must be an administrator for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param senderChatId Unique identifier of the target sender chat
      /// @param customTitle New custom title for the administrator; 0-16 characters, emoji are not allowed
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso banChatSenderChat
      /// @ref https://core.telegram.org/bots/api#unbanchatsenderchat
      bool unbanChatSenderChat(const std::variant<std::int64_t, std::string>& chatId,
                               std::int64_t senderChatId) const;


      /// @brief Use this method to set default chat permissions for all members.
      /// The bot must be an administrator in the group or a supergroup for this to work and must have the canRestrictMembers administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param permissions A ChatPermissions object for new user permissions
      /// @param useIndependentChatPermissions Optional. Pass True if chat permissions are set independently. Otherwise,
      /// the canSendOtherMessages and canAddWebPagePreviews permissions will imply the canSendMessages, canSendAudios,
      /// canSendDocuments, canSendPhotos, canSendVideos, canSendVideoNotes, and canSendVoiceNotes permissions;
      /// the canSendPolls permission will imply the canSendMessages permission.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setchatpermissions
      bool setChatPermissions(const std::variant<std::int64_t, std::string>& chatId,
                              const Ptr<ChatPermissions>& permissions,
                              bool useIndependentChatPermissions = false) const;


      /// @brief Use this method to generate a new primary invite link for a chat; any previously generated primary link is revoked.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param permissions A ChatPermissions object for new user permissions
      /// @param useIndependentChatPermissions Optional. Pass True if chat permissions are set independently. Otherwise,
      /// the canSendOtherMessages and canAddWebPagePreviews permissions will imply the canSendMessages, canSendAudios,
      /// canSendDocuments, canSendPhotos, canSendVideos, canSendVideoNotes, and canSendVoiceNotes permissions;
      /// the canSendPolls permission will imply the canSendMessages permission.
      /// @returns The new invite link as std::string on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#exportchatinvitelink
      /// @note Each administrator in a chat generates their own invite links. Bots can't use invite links generated by other administrators.
      /// If you want your bot to work with invite links, it will need to generate its own link using exportChatInviteLink or by calling the getChat method.
      /// If your bot needs to generate a new primary invite link replacing its previous one, use exportChatInviteLink again.
      std::string exportChatInviteLink(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to create an additional invite link for a chat.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// The link can be revoked using the method revokeChatInviteLink.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param name Optional. Invite link name; 0-32 characters
      /// @param expireDate Optional. Point in time (Unix timestamp) when the link will expire
      /// @param memberLimit Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
      /// @param createsJoinRequest Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, memberLimit can't be specified
      /// @returns the new invite link as ChatInviteLink object on success.
      /// @throws Exception on failure
      /// @relatesalso editChatInviteLink revokeChatInviteLink
      /// @ref https://core.telegram.org/bots/api#createchatinvitelink
      Ptr<ChatInviteLink> createChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                               const std::string& name = "",
                                               std::time_t expireDate = 0,
                                               std::int32_t memberLimit = 0,
                                               bool createsJoinRequest = false) const;


      /// @brief Use this method to edit a non-primary invite link created by the bot.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param inviteLink The invite link to edit
      /// @param name Optional. Invite link name; 0-32 characters
      /// @param expireDate Optional. Point in time (Unix timestamp) when the link will expire
      /// @param memberLimit Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
      /// @param createsJoinRequest Optional. True, if users joining the chat via the link need to be approved by chat administrators. If True, memberLimit can't be specified
      /// @returns The edited invite link as a ChatInviteLink object on success.
      /// @throws Exception on failure
      /// @relatesalso createChatInviteLink revokeChatInviteLink
      /// @ref https://core.telegram.org/bots/api#editchatinvitelink
      Ptr<ChatInviteLink> editChatInviteLink(const std::variant<std::int64_t, std::string>& chatId,
                                             const std::string& inviteLink,
                                             const std::string& name = "",
                                             std::time_t expireDate = 0,
                                             std::int32_t memberLimit = 0,
                                             bool createsJoinRequest = false) const;


      /// @brief Use this method to revoke an invite link created by the bot. If the primary link is revoked, a new link is automatically generated.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param inviteLink The invite link to revoke
      /// @returns The revoked invite link as ChatInviteLink object on success.
      /// @throws Exception on failure
      /// @relatesalso createChatInviteLink editChatInviteLink
      /// @ref https://core.telegram.org/bots/api#revokechatinvitelink
      Ptr<ChatInviteLink> revokeChatInviteLink(const std::variant<std::int64_t, std::string>& chatId, const std::string& inviteLink) const;


      /// @brief Use this method to approve a chat join request.
      /// The bot must be an administrator in the chat for this to work and must have the canInviteUsers administrator right.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso declineChatJoinRequest
      /// @ref https://core.telegram.org/bots/api#approvechatjoinrequest
      bool approveChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const;


      /// @brief Use this method to decline a chat join request.
      /// The bot must be an administrator in the chat for this to work and must have the canInviteUsers administrator right.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso approveChatJoinRequest
      /// @ref https://core.telegram.org/bots/api#declinechatjoinrequest
      bool declineChatJoinRequest(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const;


      /// @brief Use this method to set a new profile photo for the chat. Photos can't be changed for private chats.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param photo New chat photo, uploaded using multipart/form-data
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso deleteChatPhoto
      /// @ref https://core.telegram.org/bots/api#setchatphoto
      bool setChatPhoto(const std::variant<std::int64_t, std::string>& chatId, const cpr::File& photo) const;


      /// @brief Use this method to delete a chat photo. Photos can't be changed for private chats.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso setChatPhoto
      /// @ref https://core.telegram.org/bots/api#deletechatphoto
      bool deleteChatPhoto(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to change the title of a chat. Titles can't be changed for private chats.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param title New chat title, 1-128 characters
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setchattitle
      bool setChatTitle(const std::variant<std::int64_t, std::string>& chatId, const std::string& title) const;


      /// @brief Use this method to change the description of a group, a supergroup or a channel.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param description Optional. New chat description, 0-255 characters
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setchatdescription
      bool setChatDescription(const std::variant<std::int64_t, std::string>& chatId, const std::string& description = "") const;


      /// @brief Use this method to add a message to the list of pinned messages in a chat.
      /// If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right
      /// in a supergroup or 'canEditMessages' administrator right in a channel.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageId Identifier of a message to pin
      /// @param disableNotification Optional. Pass True if it is not necessary to send a notification to all chat members about the new pinned message.
      /// Notifications are always disabled in channels and private chats.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso unpinChatMessage unpinAllChatMessages
      /// @ref https://core.telegram.org/bots/api#pinchatmessage
      bool pinChatMessage(const std::variant<std::int64_t, std::string>& chatId,
                          std::int32_t messageId,
                          bool disableNotification = false) const;


      /// @brief Use this method to remove a message from the list of pinned messages in a chat.
      /// If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right
      /// in a supergroup or 'canEditMessages' administrator right in a channel.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageId Optional. Identifier of a message to unpin. If not specified, the most recent pinned message (by sending date) will be unpinned.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso pinChatMessage unpinAllChatMessages
      /// @ref https://core.telegram.org/bots/api#unpinchatmessage
      bool unpinChatMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId = 0) const;


      /// @brief Use this method to clear the list of pinned messages in a chat.
      /// If the chat is not a private chat, the bot must be an administrator in the chat for this to work and must have the 'canPinMessages' administrator right
      /// in a supergroup or 'canEditMessages' administrator right in a channel.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso pinChatMessage unpinChatMessage
      /// @ref https://core.telegram.org/bots/api#unpinallchatmessages
      bool unpinAllChatMessages(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method for your bot to leave a group, supergroup or channel.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#leavechat
      bool leaveChat(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to get up to date information about the chat (current name of the user for one-on-one conversations, current username of a user, group or channel, etc.).
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns a Chat object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getchat
      Ptr<Chat> getChat(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to get a list of administrators in a chat, which aren't bots.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns an Array of ChatMember objects.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getchatadministrators
      std::vector<Ptr<ChatMember>> getChatAdministrators(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to get the number of members in a chat.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns std::int32_t on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getchatmembercount
      std::int32_t getChatMemberCount(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to get information about a member of a chat.
      /// The method is only guaranteed to work for other users if the bot is an administrator in the chat.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param userId Unique identifier of the target user
      /// @returns a ChatMember object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getchatmember
      Ptr<ChatMember> getChatMember(const std::variant<std::int64_t, std::string>& chatId, std::int64_t userId) const;


      /// @brief Use this method to set a new group sticker set for a supergroup.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// Use the field canSetStickerSet optionally returned in getChat requests to check if the bot can use this method.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param stickerSetName Name of the sticker set to be set as the group sticker set
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso deleteChatStickerSet getForumTopicIconStickers Sticker::setName
      /// @ref https://core.telegram.org/bots/api#setchatstickerset
      bool setChatStickerSet(const std::variant<std::int64_t, std::string>& chatId, const std::string& stickerSetName) const;


      /// @brief Use this method to delete a group sticker set from a supergroup.
      /// The bot must be an administrator in the chat for this to work and must have the appropriate administrator rights.
      /// Use the field canSetStickerSet optionally returned in getChat requests to check if the bot can use this method.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso setChatStickerSet getForumTopicIconStickers Sticker::setName
      /// @ref https://core.telegram.org/bots/api#deletechatstickerset
      bool deleteChatStickerSet(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to get custom emoji stickers, which can be used as a forum topic icon by any user.
      /// Requires no parameters.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns an Array of Sticker objects.
      /// @throws Exception on failure
      /// @relatesalso setChatStickerSet deleteChatStickerSet
      /// @ref https://core.telegram.org/bots/api#getforumtopiciconstickers
      std::vector<Ptr<Sticker>> getForumTopicIconStickers() const;


      /// @brief Use this method to create a topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
      /// https://core.telegram.org/bots/api#forumtopic
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param name Topic name, 1-128 characters
      /// @param iconColor Optional. Color of the topic icon in RGB format. Currently, must be one of 7322096 (0x6FB9F0), 16766590 (0xFFD67E), 13338331 (0xCB86DB), 9367192 (0x8EEE98), 16749490 (0xFF93B2), or 16478047 (0xFB6F5F)
      /// @param iconCustomEmojiId Optional. Unique identifier of the custom emoji shown as the topic icon. Use getForumTopicIconStickers to get all allowed custom emoji identifiers. https://core.telegram.org/bots/api#getforumtopiciconstickers
      /// @returns information about the created topic as a ForumTopic object.
      /// @throws Exception on failure
      /// @relatesalso editForumTopic closeForumTopic reopenForumTopic deleteForumTopic
      /// @ref https://core.telegram.org/bots/api#createforumtopic
      Ptr<ForumTopic> createForumTopic(const std::variant<std::int64_t, std::string>& chatId,
                                       const std::string& name,
                                       std::int32_t iconColor = 0x000000,
                                       const std::string& iconCustomEmojiId = "") const;


      /// @brief Use this method to edit name and icon of a topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
      /// https://core.telegram.org/bots/api#forumtopic
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageThreadId Unique identifier for the target message thread of the forum topic
      /// @param name Optional. New topic name, 0-128 characters. If not specified or empty, the current name of the topic will be kept
      /// @param iconCustomEmojiId Optional. New unique identifier of the custom emoji shown as the topic icon.
      /// Use getForumTopicIconStickers to get all allowed custom emoji identifiers.
      /// Pass an empty string to remove the icon. If not specified, the current icon will be kept
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso createForumTopic closeForumTopic reopenForumTopic deleteForumTopic
      /// @ref https://core.telegram.org/bots/api#editforumtopic
      bool editForumTopic(const std::variant<std::int64_t, std::string>& chatId,
                          std::int32_t messageThreadId,
                          const std::string& name,
                          const std::optional<std::string>& iconCustomEmojiId = std::nullopt) const;


      /// @brief Use this method to close an open topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
      /// https://core.telegram.org/bots/api#forumtopic
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageThreadId Unique identifier for the target message thread of the forum topic
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso createForumTopic editForumTopic reopenForumTopic deleteForumTopic
      /// @ref https://core.telegram.org/bots/api#closeforumtopic
      bool closeForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const;


      /// @brief Use this method to reopen a closed topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
      /// https://core.telegram.org/bots/api#forumtopic
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageThreadId Unique identifier for the target message thread of the forum topic
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso createForumTopic editForumTopic closeForumTopic deleteForumTopic
      /// @ref https://core.telegram.org/bots/api#reopenforumtopic
      bool reopenForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const;


      /// @brief Use this method to delete a forum topic along with all its messages in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator rights.
      /// https://core.telegram.org/bots/api#forumtopic
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageThreadId Unique identifier for the target message thread of the forum topic
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso createForumTopic editForumTopic closeForumTopic reopenForumTopic
      /// @ref https://core.telegram.org/bots/api#deleteforumtopic
      bool deleteForumTopic(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const;


      /// @brief Use this method to clear the list of pinned messages in a forum topic.
      /// The bot must be an administrator in the chat for this to work and must have the canPinMessages administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param messageThreadId Unique identifier for the target message thread of the forum topic
      /// @returns True on success.
      /// @throws Exception on failure
      /// @relatesalso createForumTopic editForumTopic closeForumTopic reopenForumTopic deleteForumTopic
      /// @ref https://core.telegram.org/bots/api#unpinallforumtopicmessages
      bool unpinAllForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageThreadId) const;


      /// @brief Use this method to edit the name of the 'General' topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @param name New topic name, 1-128 characters
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#editgeneralforumtopic
      bool editGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId, const std::string& name) const;


      /// @brief Use this method to close an open 'General' topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#closegeneralforumtopic
      bool closeGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to reopen a closed 'General' topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#reopengeneralforumtopic
      bool reopenGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to hide the 'General' topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#hidegeneralforumtopic
      bool hideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to unhide the 'General' topic in a forum supergroup chat.
      /// The bot must be an administrator in the chat for this to work and must have the canManageTopics administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#unhidegeneralforumtopic
      bool unhideGeneralForumTopic(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to clear the list of pinned messages in a General forum topic.
      /// The bot must be an administrator in the chat for this to work and must have the canPinMessages administrator right in the supergroup.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format \@channelusername)
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#unpinallgeneralforumtopicmessages
      bool unpinAllGeneralForumTopicMessages(const std::variant<std::int64_t, std::string>& chatId) const;


      /// @brief Use this method to send answers to callback queries sent from inline keyboards.
      /// The answer will be displayed to the user as a notification at the top of the chat screen or as an alert.
      /// The bot must be an administrator in the chat for this to work and must have the canPinMessages administrator right in the supergroup.
      /// https://core.telegram.org/bots/features#inline-keyboards
      /// @param callbackQueryId Unique identifier for the query to be answered
      /// @param text Optional. Text of the notification. If not specified, nothing will be shown to the user, 0-200 characters
      /// @param showAlert Optional. If True, an alert will be shown by the client instead of a notification at the top of the chat screen. Defaults to false.
      /// @param url Optional. URL that will be opened by the user's client. If you have created a Game and accepted the conditions via @BotFather, specify the URL that opens your game - note that this will only work if the query comes from a callback_game button.
      /// Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter.
      /// @param cacheTime Optional. The maximum amount of time in seconds that the result of the callback query may be cached client-side.
      /// Telegram apps will support caching starting in version 3.14. Defaults to 0.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ote Alternatively, the user can be redirected to the specified Game URL. For this option to work, you must first create a game for your bot via \@BotFather and accept the terms.
      /// Otherwise, you may use links like t.me/your_bot?start=XXXX that open your bot with a parameter.
      /// @ref https://core.telegram.org/bots/api#answercallbackquery
      bool answerCallbackQuery(const std::string& callbackQueryId,
                               const std::string& text = "",
                               bool showAlert = false,
                               const std::string& url = "",
                               std::int32_t cacheTime = 0) const;


      /// @brief Use this method to change the list of the bot's commands.
      /// See this manual for more details about bot commands. https://core.telegram.org/bots/features#commands
      /// @param commands A JSON-serialized list of bot commands to be set as the list of the bot's commands. At most 100 commands can be specified.
      /// @param scope Optional. A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
      /// @returns True on success.
      /// @throws Exception on failure
      /// @note Commands must not contain spaces and must be in snake case e.g "do_something" ✅  or "dosomthing" ✅ and not "doSomething" 𐄂 or "do something" 𐄂.
      /// @ref https://core.telegram.org/bots/api#setmycommands
      bool setMyCommands(const std::vector<Ptr<BotCommand>>& commands,
                         const Ptr<BotCommandScope>& scope = nullptr,
                         const std::string& languageCode = "") const;


      /// @brief Use this method to delete the list of the bot's commands for the given scope and user language.
      /// After deletion, higher level commands will be shown to affected users.
      /// https://core.telegram.org/bots/api#determining-list-of-commands
      /// @param scope Optional. A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#deletemycommands
      bool deleteMyCommands(const Ptr<BotCommandScope>& scope = nullptr, const std::string& languageCode = "") const;


      /// @brief Use this method to get the current list of the bot's commands for the given scope and user language.
      /// @param scope Optional. A JSON-serialized object, describing scope of users for which the commands are relevant. Defaults to BotCommandScopeDefault.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, commands will be applied to all users from the given scope, for whose language there are no dedicated commands
      /// @returns an Array of BotCommand objects. If commands aren't set, an empty list is returned.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getmycommands
      std::vector<Ptr<BotCommand>> getMyCommands(const Ptr<BotCommandScope>& scope = nullptr, const std::string& languageCode = "") const;


      /// @brief Use this method to change the bot's name.
      /// @param name Optional. New bot name; 0-64 characters. Pass an empty string to remove the dedicated name for the given language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the name will be shown to all users for whose language there is no dedicated name.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setmyname
      bool setMyName(const std::string& name = "", const std::string& languageCode = "") const;


      /// @brief Use this method to get the current bot name for the given user language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
      /// @returns BotName object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getmyname
      Ptr<BotName> getMyName(const std::string& languageCode = "") const;


      /// @brief Use this method to change the bot's description, which is shown in the chat with the bot if the chat is empty.
      /// @param description Optional. New bot description; 0-512 characters. Pass an empty string to remove the dedicated description for the given language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the description will be applied to all users for whose language there is no dedicated description.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setmydescription
      bool setMyDescription(const std::string& description = "", const std::string& languageCode = "") const;


      /// @brief Use this method to get the current bot description for the given user language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
      /// @returns BotDescription object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getmydescription
      Ptr<BotDescription> getMyDescription(const std::string& languageCode = "") const;

      /// @brief Use this method to change the bot's short description, which is shown on the bot's profile page and is sent together with the link when users share the bot.
      /// @param shortDescription Optional. New short description for the bot; 0-120 characters. Pass an empty string to remove the dedicated short description for the given language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code. If empty, the short description will be applied to all users for whose language there is no dedicated short description.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setmyshortdescription
      bool setMyShortDescription(const std::string& shortDescription = "", const std::string& languageCode = "") const;

      /// @brief Use this method to get the current bot short description for the given user language.
      /// @param languageCode Optional. A two-letter ISO 639-1 language code or an empty string
      /// @returns BotShortDescription object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getmyshortdescription
      Ptr<BotShortDescription> getMyShortDescription(const std::string& languageCode = "") const;

      /// @brief Use this method to change the bot's menu button in a private chat, or the default menu button.
      /// @param chatId Optional. Unique identifier for the target private chat. If not specified, default bot's menu button will be changed
      /// @param menuButton Optional. A JSON-serialized object for the bot's new menu button. Defaults to MenuButtonDefault
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setmyshortdescription
      bool setChatMenuButton(const std::variant<std::int64_t, std::string>& chatId = std::string{}, const Ptr<MenuButton>& menuButton = nullptr) const;

      /// @brief Use this method to get the current value of the bot's menu button in a private chat, or the default menu button.
      /// @param chatId Optional. Integer or String Unique identifier for the target private chat. If not specified, default bot's menu button will be returned
      /// @returns MenuButton object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getchatmenubutton
      Ptr<MenuButton> getChatMenuButton(const std::variant<std::int64_t, std::string>& chatId = std::string{}) const;

      /// @brief Use this method to change the default administrator rights requested by the bot when it's added as an administrator to groups or channels.
      /// These rights will be suggested to users, but they are free to modify the list before adding the bot.
      /// @param rights Optional. A JSON-serialized object describing new default administrator rights. If not specified, the default administrator rights will be cleared.
      /// @param forChannels Optional. Pass True to change the default administrator rights of the bot in channels. Otherwise, the default administrator rights of the bot for groups and supergroups will be changed.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setmydefaultadministratorrights
      bool setMyDefaultAdministratorRights(const Ptr<ChatAdministratorRights>& rights = nullptr, bool forChannels = false) const;

      /// @brief Use this method to get the current default administrator rights of the bot.
      /// @param forChannels Optional. Pass True to get default administrator rights of the bot in channels. Otherwise, default administrator rights of the bot for groups and supergroups will be returned.
      /// @returns ChatAdministratorRights object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getmydefaultadministratorrights
      Ptr<ChatAdministratorRights> getMyDefaultAdministratorRights(bool forChannels = false) const;


    public: /// Payments methods https://core.telegram.org/bots/api#payments
      /// @brief Use this method to send invoices.
      /// @param chatId Integer or String Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param title Product name, 1-32 characters
      /// @param description Product description, 1-255 characters
      /// @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
      /// @param providerToken Payment provider token, obtained via @BotFather
      /// @param currency Three-letter ISO 4217 currency code, [see more on currencies](https://core.telegram.org/bots/payments#supported-currencies)
      /// @param prices Array of LabeledPrice, Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param maxTipAmount Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double).
      /// For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See the exp parameter in currencies.json,
      /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies). Defaults to 0
      /// @param suggestedTipAmounts Optional. A JSON-serialized array of suggested amounts of tips in the smallest units of the currency (integer, not float/double).
      /// At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
      /// @param startParameter Optional. Unique deep-linking parameter. If left empty, forwarded copies of the sent message will have a Pay button, allowing multiple users to pay directly from the forwarded message,
      /// using the same invoice. If non-empty, forwarded copies of the sent message will have a URL button with a deep link to the bot (instead of a Pay button), with the value used as the start parameter
      /// @param providerData Optional. JSON-serialized data about the invoice, which will be shared with the payment provider. A detailed description of required fields should be provided by the payment provider.
      /// @param photoUrl Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service. People like it better when they see what they are paying for.
      /// @param photoSize Optional. Photo size in bytes
      /// @param photoWidth Optional. Photo width
      /// @param photoHeight Optional. Photo height
      /// @param needName Optional. Pass True if you require the user's full name to complete the order
      /// @param needPhoneNumber Optional. Pass True if you require the user's phone number to complete the order
      /// @param needEmail Optional. Pass True if you require the user's email address to complete the order
      /// @param needShippingAddress Optional. Pass True if you require the user's shipping address to complete the order
      /// @param sendPhoneNumberToProvider Optional. Pass True if the user's phone number should be sent to provider
      /// @param sendEmailToProvider Optional. Pass True if the user's email address should be sent to provider
      /// @param isFlexible Optional. Pass True if the final price depends on the shipping method
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. A JSON-serialized object for an inline keyboard. If empty, one 'Pay total price' button will be shown. If not empty, the first button must be a Pay button.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns sent Message object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendinvoice
      Ptr<Message> sendInvoice(const std::variant<std::int64_t, std::string>& chatId,
                               const std::string& title,
                               const std::string& description,
                               const std::string& payload,
                               const std::string& providerToken,
                               const std::string& currency,
                               const std::vector<Ptr<LabeledPrice>>& prices,
                               std::int32_t messageThreadId = 0,
                               std::int32_t maxTipAmount = 0,
                               const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                               const std::string& startParameter = "",
                               const std::string& providerData = "",
                               const std::string& photoUrl = "",
                               std::int32_t photoSize = 0,
                               std::int32_t photoWidth = 0,
                               std::int32_t photoHeight = 0,
                               bool needName = false,
                               bool needPhoneNumber = false,
                               bool needEmail = false,
                               bool needShippingAddress = false,
                               bool sendPhoneNumberToProvider = false,
                               bool sendEmailToProvider = false,
                               bool isFlexible = false,
                               bool disableNotification = false,
                               bool protectContent = false,
                               std::int32_t replyToMessageId = 0,
                               bool allowSendingWithoutReply = false,
                               const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;

      /// @brief Use this method to create a link for an invoice. Returns the created invoice link as std::string on success.
      /// @param title Product name, 1-32 characters
      /// @param description Product description, 1-255 characters
      /// @param payload Bot-defined invoice payload, 1-128 bytes. This will not be displayed to the user, use for your internal processes.
      /// @param providerToken Payment provider token, obtained via @BotFather
      /// @param currency Three-letter ISO 4217 currency code, [see more on currencies](https://core.telegram.org/bots/payments#supported-currencies)
      /// @param prices Array of LabeledPrice, Price breakdown, a JSON-serialized list of components (e.g. product price, tax, discount, delivery cost, delivery tax, bonus, etc.)
      /// @param maxTipAmount Optional. The maximum accepted amount for tips in the smallest units of the currency (integer, not float/double).
      /// For example, for a maximum tip of US$ 1.45 pass max_tip_amount = 145. See the exp parameter in currencies.json,
      /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies). Defaults to 0
      /// @param suggestedTipAmounts Optional. A JSON-serialized array of suggested amounts of tips in the smallest units of the currency (integer, not float/double).
      /// At most 4 suggested tip amounts can be specified. The suggested tip amounts must be positive, passed in a strictly increased order and must not exceed maxTipAmount.
      /// @param startParameter Optional. Unique deep-linking parameter. If left empty, forwarded copies of the sent message will have a Pay button, allowing multiple users to pay directly from the forwarded message,
      /// using the same invoice. If non-empty, forwarded copies of the sent message will have a URL button with a deep link to the bot (instead of a Pay button), with the value used as the start parameter
      /// @param providerData Optional. JSON-serialized data about the invoice, which will be shared with the payment provider. A detailed description of required fields should be provided by the payment provider.
      /// @param photoUrl Optional. URL of the product photo for the invoice. Can be a photo of the goods or a marketing image for a service. People like it better when they see what they are paying for.
      /// @param photoSize Optional. Photo size in bytes
      /// @param photoWidth Optional. Photo width
      /// @param photoHeight Optional. Photo height
      /// @param needName Optional. Pass True if you require the user's full name to complete the order
      /// @param needPhoneNumber Optional. Pass True if you require the user's phone number to complete the order
      /// @param needEmail Optional. Pass True if you require the user's email address to complete the order
      /// @param needShippingAddress Optional. Pass True if you require the user's shipping address to complete the order
      /// @param sendPhoneNumberToProvider Optional. Pass True if the user's phone number should be sent to provider
      /// @param sendEmailToProvider Optional. Pass True if the user's email address should be sent to provider
      /// @param isFlexible Optional. Pass True if the final price depends on the shipping method
      /// @returns the created invoice link as std::string on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#createinvoicelink
      std::string createInvoiceLink(const std::string& title,
                                    const std::string& description,
                                    const std::string& payload,
                                    const std::string& providerToken,
                                    const std::string& currency,
                                    const std::vector<Ptr<LabeledPrice>>& prices,
                                    std::int32_t maxTipAmount = 0,
                                    const std::vector<std::int32_t>& suggestedTipAmounts = std::vector<std::int32_t>(),
                                    const std::string& providerData = "",
                                    const std::string& photoUrl = "",
                                    std::int32_t photoSize = 0,
                                    std::int32_t photoWidth = 0,
                                    std::int32_t photoHeight = 0,
                                    bool needName = false,
                                    bool needPhoneNumber = false,
                                    bool needEmail = false,
                                    bool needShippingAddress = false,
                                    bool sendPhoneNumberToProvider = false,
                                    bool sendEmailToProvider = false,
                                    bool isFlexible = false) const;


      /// @brief If you sent an invoice requesting a shipping address and the parameter isFlexible was specified,
      /// the Bot API will send an Update with a shippingQuery field to the bot.
      /// Use this method to reply to shipping queries. On success, True is returned.
      /// @param shippingQueryId Unique identifier for the query to be answered
      /// @param ok Pass True if delivery to the specified address is possible and False if there are any problems (for example, if delivery to the specified address is not possible)
      /// @param shippingOptions Optional. Array of ShippingOption, Required if ok is True. A JSON-serialized array of available shipping options.
      /// @param errorMessage Optional. Required if ok is False. Error message in human readable form that explains why it is impossible to complete the order (e.g. "Sorry, delivery to your desired address is unavailable').
      /// Telegram will display this message to the user.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#answershippingquery
      bool answerShippingQuery(const std::string& shippingQueryId,
                               bool ok,
                               const std::vector<Ptr<ShippingOption>>& shippingOptions = std::vector<Ptr<ShippingOption>>(),
                               const std::string& errorMessage = "") const;


      /// @brief Once the user has confirmed their payment and shipping details, the Bot API sends the final confirmation in the form of an Update with the field preCheckoutQuery.
      /// Use this method to respond to such pre-checkout queries. On success, True is returned.
      /// @note: The Bot API must receive an answer within 10 seconds after the pre-checkout query was sent.
      /// @param preCheckoutQueryId Unique identifier for the query to be answered
      /// @param ok Specify True if everything is alright (goods are available, etc.) and the bot is ready to proceed with the order. Use False if there are any problems.
      /// @param errorMessage Optional. Required if ok is False. Error message in human readable form that explains the reason for failure to proceed with the checkout
      /// (e.g. "Sorry, somebody just bought the last of our amazing black T-shirts while you were busy filling out your payment details. Please choose a different color or garment!").
      /// Telegram will display this message to the user.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#answerprecheckoutquery
      bool answerPreCheckoutQuery(const std::string& preCheckoutQueryId,
                                  bool ok,
                                  const std::string& errorMessage = "") const;


    public: /// Updates methods  https://core.telegram.org/bots/api#getting-updates
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
      /// @throws Exception on failure
      /// @note Please note that this parameter doesn't affect updates created before the call to the getUpdates, so unwanted updates may be received for a short period of time.
      /// @note This method will not work if an outgoing webhook is set up.
      /// @note In order to avoid getting duplicate updates, recalculate offset after each server response.
      /// @link ref https://core.telegram.org/bots/api#getupdates @endlink
      std::vector<Ptr<Update>> getUpdates(std::int32_t offset, std::int32_t limit = 100, const std::vector<std::string>& allowedUpdates = {}) const;

      /// @brief Use this method to specify a URL and receive incoming updates via an outgoing webhook.
      /// Whenever there is an update for the bot, we will send an HTTPS POST request to the specified URL, containing a JSON-serialized Update.
      /// In case of an unsuccessful request, we will give up after a reasonable amount of attempts.
      /// If you'd like to make sure that the webhook was set by you, you can specify secret data in the parameter secret_token.
      /// If specified, the request will contain a header “X-Telegram-Bot-Api-Secret-Token” with the secret token as content.
      /// @param url HTTPS URL to send updates to. Use an empty string to remove webhook integration
      /// @param certificate Optional. Upload your public key certificate so that the root certificate in use can be checked. See our self-signed guide for details.
      /// @param ipAddress Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
      /// @param maxConnections Optional. The maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40.
      /// Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput.
      /// @param allowedUpdates Optional. A JSON-serialized list of the update types you want your bot to receive.
      /// For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types.
      /// See Update for a complete list of available update types. Specify an empty list to receive all update types except chat_member (default).
      /// If not specified, the previous setting will be used.
      /// Please note that this parameter doesn't affect updates created before the call to the setWebhook, so unwanted updates may be received for a short period of time.
      /// @param dropPendingUpdates Optional. Pass True to drop all pending updates.
      /// @param secretToken Optional. A secret token to be sent in a header “X-Telegram-Bot-Api-Secret-Token” in every webhook request, 1-256 characters. Only characters A-Z, a-z, 0-9, _ and - are allowed.
      /// The header is useful to ensure that the request comes from a webhook set by you.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @note You will not be able to receive updates using Api::getUpdates for as long as an outgoing webhook is set up.
      /// @note To use a self-signed certificate, you need to upload your public key certificate using certificate parameter. Please upload as InputFile, sending a String will not work.
      /// @note Ports currently supported for webhooks: 443, 80, 88, 8443.
      /// If you're having any trouble setting up webhooks, please check out this amazing guide to webhooks. https://core.telegram.org/bots/webhooks
      /// @ref https://core.telegram.org/bots/api#setwebhook
      bool setWebhook(const std::string& url,
                      const std::optional<cpr::File>& certificate = std::nullopt,
                      const std::string& ipAddress = "",
                      std::int32_t maxConnections = 40,
                      const std::vector<std::string>& allowedUpdates = std::vector<std::string>(),
                      bool dropPendingUpdates = false,
                      const std::string& secretToken = "") const;

      /// @brief Use this method to remove webhook integration if you decide to switch back to getUpdates.
      /// @param dropPendingUpdates Optional. Pass True to drop all pending updates.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @note when Bot is not running, updates will remain 24 hours in Telegram server before they get deleted or retrieved by BOT
      /// @note In order for Api::getUpdates() to work, there should be no outgoing webhook set up. See https://core.telegram.org/bots/api#getupdates
      /// @ref https://core.telegram.org/bots/api#deletewebhook
      bool deleteWebhook(bool dropPendingUpdates = false) const;

      /// @brief Use this method to get current webhook status. Requires no parameters. On success, returns a WebhookInfo object.
      /// If the bot is using getUpdates, will return an object with the url field empty.
      /// @returns a WebhookInfo object on success. If the bot is using getUpdates, will return an object with the WebhookInfo::url field empty.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getwebhookinfo
      Ptr<WebhookInfo> getWebhookInfo() const;

    public: /// Updating messages
            /// The following methods allow you to change an existing message in the message history instead of sending a new one with a result of an action.
            /// This is most useful for messages with inline keyboards using callback queries, but can also help reduce clutter in conversations with regular chat bots.
            /// Please note, that it is currently only possible to edit messages without reply_markup or with inline keyboards.
            /// @ref https://core.telegram.org/bots/api#updating-messages
      /// @brief Use this method to edit text and game messages.
      /// @param text New text of the message, 1-4096 characters after entities parsing
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param parseMode Optional. Mode for parsing entities in the message text. See https://core.telegram.org/bots/api#formatting-options for more details.
      /// @param entities Optional. List of special entities that appear in message text, which can be specified instead of parseMode
      /// @param disableWebPagePreview Optional. Disables link previews for links in this message
      /// @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
      /// @returns On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#editmessagetext
      Ptr<Message> editMessageText(const std::string& text,
                                   const std::variant<std::int64_t, std::string>& chatId = 0,
                                   std::int32_t messageId = 0,
                                   const std::string& inlineMessageId = "",
                                   const std::string& parseMode = "",
                                   const std::vector<Ptr<MessageEntity>>& entities = std::vector<Ptr<MessageEntity>>(),
                                   bool disableWebPagePreview = false,
                                   const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to edit captions of messages.
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param caption Optional. New caption of the message, 0-1024 characters after entities parsing
      /// @param parseMode Optional. Mode for parsing entities in the message caption. See https://core.telegram.org/bots/api#formatting-options for more details.
      /// @param captionEntities Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      /// @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
      /// @returns On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#editmessagecaption
      Ptr<Message> editMessageCaption(const std::variant<std::int64_t, std::string>& chatId = 0,
                                      std::int32_t messageId = 0,
                                      const std::string& inlineMessageId = "",
                                      const std::string& caption = "",
                                      const std::string& parseMode = "",
                                      const std::vector<Ptr<MessageEntity>>& captionEntities = std::vector<Ptr<MessageEntity>>(),
                                      const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to edit animation, audio, document, photo, or video messages.
      /// If a message is part of a message album, then it can be edited only to an audio for audio albums, only to a document for document albums and to a photo or a video otherwise.
      /// When an inline message is edited, a new file can't be uploaded; use a previously uploaded file via its fileId or specify a URL.
      /// @param media A JSON-serialized object for a new media content of the message
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
      /// @returns On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#editmessagemedia
      Ptr<Message> editMessageMedia(const Ptr<InputMedia>& media,
                                    const std::variant<std::int64_t, std::string>& chatId = 0,
                                    std::int32_t messageId = 0,
                                    const std::string& inlineMessageId = "",
                                    const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to edit live location messages.
      /// A location can be edited until its livePeriod expires or editing is explicitly disabled by a call to Api::stopMessageLiveLocation.
      /// @param latitude Latitude of new location
      /// @param longitude Longitude of new location
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param horizontalAccuracy Optional. The radius of uncertainty for the location, measured in meters; 0-1500
      /// @param heading Optional. Direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
      /// @param proximityAlertRadius Optional. The maximum distance for proximity alerts about approaching another chat member, in meters. Must be between 1 and 100000 if specified.
      /// @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
      /// @returns On success, the edited Message is returned. Otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#editmessagelivelocation
      Ptr<Message> editMessageLiveLocation(float latitude,
                                           float longitude,
                                           const std::variant<std::int64_t, std::string>& chatId = 0,
                                           std::int32_t messageId = 0,
                                           const std::string& inlineMessageId = "",
                                           float horizontalAccuracy = 0.0f,
                                           std::int32_t heading = 0,
                                           std::int32_t proximityAlertRadius = 0,
                                           const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to stop updating a live location message before livePeriod expires.
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message with live location to stop
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param replyMarkup Optional. A JSON-serialized object for a new inline keyboard.
      /// @returns On success, the edited Message is returned. Otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#stopmessagelivelocation
      Ptr<Message> stopMessageLiveLocation(const std::variant<std::int64_t, std::string>& chatId = 0,
                                           std::int32_t messageId = 0,
                                           const std::string& inlineMessageId = "",
                                           const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to edit only the reply markup of messages.
      /// @param chatId Optional. Required if inlineMessageId is not specified. Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Optional. Required if inlineMessageId is not specified. Identifier of the message to edit
      /// @param inlineMessageId Optional. Required if chatId and messageId are not specified. Identifier of the inline message
      /// @param replyMarkup Optional. A JSON-serialized object for an inline keyboard.
      /// @returns On success, if the edited message is not an inline message, the edited Message is returned, otherwise nullptr is returned.
      /// @ref https://core.telegram.org/bots/api#editmessagereplymarkup
      Ptr<Message> editMessageReplyMarkup(const std::variant<std::int64_t, std::string>& chatId = 0,
                                          std::int32_t messageId = 0,
                                          const std::string& inlineMessageId = "",
                                          const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to stop a poll which was sent by the bot.
      /// @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Identifier of the original message with the poll
      /// @param replyMarkup Optional. A JSON-serialized object for a new message inline keyboard.
      /// @returns On success, the stopped Poll is returned.
      /// @ref https://core.telegram.org/bots/api#stoppoll
      Ptr<Poll> stopPoll(const std::variant<std::int64_t, std::string>& chatId,
                         std::int32_t messageId,
                         const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;


      /// @brief Use this method to delete a message, including service messages, with the following limitations:
      /// - A message can only be deleted if it was sent less than 48 hours ago.
      /// - Service messages about a supergroup, channel, or forum topic creation can't be deleted.
      /// - A dice message in a private chat can only be deleted if it was sent more than 24 hours ago.
      /// - Bots can delete outgoing messages in private chats, groups, and supergroups.
      /// - Bots can delete incoming messages in private chats.
      /// - Bots granted canPostMessages permissions can delete outgoing messages in channels.
      /// - If the bot is an administrator of a group, it can delete any message there.
      /// - If the bot has canDeleteMessages permission in a supergroup or a channel, it can delete any message there.
      ///
      /// @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param messageId Identifier of the message to delete
      /// @returns Returns True on success.
      /// @ref https://core.telegram.org/bots/api#deletemessage
      bool deleteMessage(const std::variant<std::int64_t, std::string>& chatId, std::int32_t messageId) const;

    public: /// Stickers
      /// @brief Use this method to send static .WEBP, animated .TGS, or video .WEBM stickers. On success, the sent Message is returned.
      /// @param chatId Unique identifier for the target chat or username of the target channel (in the format @channelusername)
      /// @param sticker Sticker to send.
      /// - Pass a file_id std::string to send a file that exists on the Telegram servers (recommended),
      /// - Pass an HTTP URL as an std::string for Telegram to get a .WEBP sticker from the Internet, or
      /// - Pass a cpr::File to upload a new .WEBP or .TGS sticker
      /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
      /// @param emoji Optional. Emoji associated with the sticker; only for just uploaded stickers
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyParameters Optional. Description of the message to reply to
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns sent Message object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#sendsticker
      Ptr<Message> sendSticker(const std::variant<std::int64_t, std::string>& chatId,
                               const std::variant<cpr::File, std::string>& sticker,
                               std::int32_t messageThreadId = 0,
                               const std::string& emoji = "",
                               bool disableNotification = false,
                               bool protectContent = false,
                               const Ptr<ReplyParameters>& replyParameters = nullptr,
                               const Ptr<IReplyMarkup>& replyMarkup = nullptr) const;

      /// @brief Use this method to get a sticker set. On success, a StickerSet object is returned.
      /// @param name Name of the sticker set
      /// @returns StickerSet object is returned on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getstickerset
      Ptr<StickerSet> getStickerSet(const std::string& name) const;

      /// @brief Use this method to get information about custom emoji stickers by their identifiers.
      /// @param customEmojiIds List of custom emoji identifiers. At most 200 custom emoji identifiers can be specified.
      /// @returns an Array of Sticker objects on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#getcustomemojistickers
      std::vector<Ptr<Sticker>> getCustomEmojiStickers(const std::vector<std::string>& customEmojiIds) const;

      /// @brief Use this method to upload a file with a sticker for later use in the createNewStickerSet and
      /// addStickerToSet methods (the file can be used multiple times).
      /// @param userId User identifier of sticker file owner
      /// @param sticker A file with the sticker in .WEBP, .PNG, .TGS, or .WEBM format.
      /// See https://core.telegram.org/stickers for technical requirements. [More information on Sending Files »](https://core.telegram.org/bots/api#sending-files)
      /// @param stickerFormat Format of the sticker, must be one of “static”, “animated”, “video”
      /// @returns the uploaded File on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#uploadstickerfile
      Ptr<File> uploadStickerFile(std::int64_t userId,
                                  const cpr::File& sticker,
                                  const std::string& stickerFormat) const;

      /// @brief Use this method to create a new sticker set owned by a user. The bot will be able to edit the sticker set thus created.
      /// @param userId User identifier of created sticker set owner
      /// @param name Short name of sticker set, to be used in t.me/addstickers/ URLs (e.g., animals).
      /// Can contain only English letters, digits and underscores.
      /// Must begin with a letter, can't contain consecutive underscores and must end in "_by_<bot_username>".
      /// <bot_username> is case insensitive. 1-64 characters.
      /// @param title Sticker set title, 1-64 characters
      /// @param stickers A JSON-serialized list of 1-50 initial stickers to be added to the sticker set
      /// @param stickerFormat Format of stickers in the set, must be one of “static”, “animated”, “video”
      /// @param stickerType Optional. Type of stickers in the set, pass “regular”, “mask”, or “custom_emoji”. By default, a regular sticker set is created.
      /// @param needsRepainting Optional. Pass True if stickers in the sticker set must be repainted to the color of text when used in messages,
      /// the accent color if used as emoji status, white on chat photos, or another appropriate color based on context; for custom emoji sticker sets only
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#createnewstickerset
      bool createNewStickerSet(std::int64_t userId,
                               const std::string& name,
                               const std::string& title,
                               const std::vector<Ptr<InputSticker>>& stickers,
                               const std::string& stickerFormat,
                               const std::string& stickerType = "regular",
                               bool needsRepainting = false) const;

      /// @brief Use this method to add a new sticker to a set created by the bot.
      /// The format of the added sticker must match the format of the other stickers in the set.
      /// Emoji sticker sets can have up to 200 stickers. Animated and video sticker sets can have up to 50 stickers.
      /// Static sticker sets can have up to 120 stickers.
      /// @param userId User identifier of created sticker set owner
      /// @param name Sticker set name
      /// @param sticker A JSON-serialized object with information about the added sticker. If exactly the same sticker had already been added to the set, then the set isn't changed.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#addstickertoset
      bool addStickerToSet(std::int64_t userId,
                           const std::string& name,
                           const Ptr<InputSticker>& sticker) const;

      /// @brief Use this method to move a sticker in a set created by the bot to a specific position.
      /// @param sticker File identifier of the sticker
      /// @param position New sticker position in the set, zero-based
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickerpositioninset
      bool setStickerPositionInSet(const std::string& sticker, std::int32_t position) const;

      /// @brief Use this method to delete a sticker from a set created by the bot.
      /// @param sticker File identifier of the sticker
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#deletestickerfromset
      bool deleteStickerFromSet(const std::string& sticker) const;

      /// @brief Use this method to change the list of emoji assigned to a regular or custom emoji sticker.
      /// The sticker must belong to a sticker set created by the bot.
      /// @param sticker File identifier of the sticker
      /// @param emojiList A JSON-serialized list of 1-20 emoji associated with the sticker
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickeremojilist
      bool setStickerEmojiList(const std::string& sticker, const std::vector<std::string>& emojiList) const;

      /// @brief Use this method to change search keywords assigned to a regular or custom emoji sticker.
      /// The sticker must belong to a sticker set created by the bot.
      /// @param sticker File identifier of the sticker
      /// @param keywords Optional. A JSON-serialized list of 0-20 search keywords for the sticker with total length of up to 64 characters
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickerkeywords
      bool setStickerKeywords(const std::string& sticker, const std::vector<std::string>& keywords = std::vector<std::string>()) const;

      /// @brief Use this method to change the mask position of a mask sticker.
      /// The sticker must belong to a sticker set that was created by the bot.
      /// @param sticker File identifier of the sticker
      /// @param maskPosition Optional. A JSON-serialized object with the position where the mask should be placed on faces. Omit the parameter to remove the mask position.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickermaskposition
      bool setStickerMaskPosition(const std::string& sticker,
                                  const Ptr<MaskPosition>& maskPosition = nullptr) const;

      /// @brief Use this method to set the title of a created sticker set.
      /// @param name Sticker set name
      /// @param title Sticker set title, 1-64 characters
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickersettitle
      bool setStickerSetTitle(const std::string& name, const std::string& title) const;

      /// @brief Use this method to set the thumbnail of a regular or mask sticker set.
      /// The format of the thumbnail file must match the format of the stickers in the set.
      /// @param name Sticker set name
      /// @param userId User identifier of created sticker set owner
      /// @param thumbnail Optional. A .WEBP or .PNG image with the thumbnail, must be up to 128 kilobytes in size and have a width and height
      /// of exactly 100px, or a .TGS animation with a thumbnail up to 32 kilobytes in size
      /// (see https://core.telegram.org/stickers#animated-sticker-requirements for animated sticker technical requirements),
      /// or a WEBM video with the thumbnail up to 32 kilobytes in size; see https://core.telegram.org/stickers#video-sticker-requirements
      /// for video sticker technical requirements. Pass a file_id as a String to send a file that already exists on the Telegram servers,
      /// pass an HTTP URL as a String for Telegram to get a file from the Internet, or upload a new one using multipart/form-data.
      /// More information on Sending Files ». Animated and video sticker set thumbnails can't be uploaded via HTTP URL.
      /// If omitted, then the thumbnail is dropped and the first sticker is used as the thumbnail.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setstickersetthumbnail
      bool setStickerSetThumbnail(const std::string& name,
                                  const std::string& title,
                                  const std::optional<std::variant<cpr::File, std::string>>& thumbnail = std::nullopt) const;

      /// @brief Use this method to set the thumbnail of a custom emoji sticker set.
      /// @param name Sticker set name
      /// @param customEmojiId Optional. Custom emoji identifier of a sticker from the sticker set;
      /// Pass an empty string to drop the thumbnail and use the first sticker as the thumbnail.
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#setcustomemojistickersetthumbnail
      bool setCustomEmojiStickerSetThumbnail(const std::string& name, const std::optional<std::string>& customEmojiId = std::nullopt) const;

      /// @brief Use this method to delete a sticker set that was created by the bot.
      /// @param name Sticker set name
      /// @returns True on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#deletestickerset
      bool deleteStickerSet(const std::string& name) const;


    public: /// Inline mode methods. Methods and objects used in the inline mode are described in the Inline mode section. https://core.telegram.org/bots/api#inline-mode
      /// @brief Use this method to send answers to an inline query.
      /// No more than 50 results per query are allowed.
      /// @param inlineQueryId Unique identifier for the answered query
      /// @param results A JSON-serialized array of results for the inline query
      /// @param cacheTime Optional. The maximum amount of time in seconds that the result of the inline query may be cached on the server. Defaults to 300.
      /// @param isPersonal Optional. Pass True if results may be cached on the server side only for the user that sent the query. By default, results may be returned to any user who sends the same query.
      /// @param nextOffset Optional. Pass the offset that a client should send in the next query with the same text to receive more results.
      /// Pass an empty string if there are no more results or if you don't support pagination. Offset length can't exceed 64 bytes.
      /// @param button Optional. A JSON-serialized object describing a button to be shown above inline query results
      /// @returns True on success.
      /// @throws Exception on failure
      /// @note No more than 50 results per query are allowed.
      /// @ref https://core.telegram.org/bots/api#answerinlinequery
      bool answerInlineQuery(const std::string& inlineQueryId,
                             const std::vector<Ptr<InlineQueryResult>>& results,
                             std::int32_t cacheTime = 300,
                             bool isPersonal = false,
                             const std::string& nextOffset = "",
                             const Ptr<InlineQueryResultsButton>& button = nullptr) const;


      /// @brief Use this method to set the result of an interaction with a Web App
      /// and send a corresponding message on behalf of the user to the chat from which the query originated.
      /// @param webAppQueryId Unique identifier for the query to be answered
      /// @param result A JSON-serialized object describing the message to be sent
      /// @returns a SentWebAppMessage object on success.
      /// @throws Exception on failure
      /// @ref https://core.telegram.org/bots/api#answerwebappquery
      Ptr<SentWebAppMessage> answerWebAppQuery(const std::string& webAppQueryId, const Ptr<InlineQueryResult>& result) const;

    public: /// Timeout setters/getters
      /// @brief Set Api URL.
      void setUrl(const std::string& url) noexcept;
      /// @brief Get Api URL.
      const std::string& getUrl() const noexcept;

      /// @brief Set long polling timeout.
      void setLongPollTimeout(const cpr::Timeout& longPollTimeout);
      /// @brief Get long polling timeout.
      cpr::Timeout getLongPollTimeout() const noexcept;

      /// @brief Set Api requests connection timeout.
      void setConnectTimeout(const cpr::ConnectTimeout& timeout) noexcept;
      /// @brief Get Api requests connection timeout.
      cpr::ConnectTimeout getConnectTimeout() const noexcept;

      /// @brief Set Api requests timeout.
      void setTimeout(const cpr::Timeout& timeout);
      /// @brief Get Api requests timeout.
      cpr::Timeout getTimeout() const noexcept;

      /// @brief Set Api file uploads timeout.
      void setUploadFilesTimeout(const cpr::Timeout& timeout) noexcept;
      /// @brief Get Api file uploads timeout.
      cpr::Timeout getUploadFilesTimeout() const noexcept;

      /// @brief Set Api file downloads timeout.
      void setDownloadFilesTimeout(const cpr::Timeout& timeout) noexcept;
      /// @brief Get APi file downloads timeout.
      cpr::Timeout getDownloadFilesTimeout() const noexcept;

    private:
      nl::json sendRequest(const std::string& endpoint, const cpr::Multipart& data = cpr::Multipart({})) const;
  };
}