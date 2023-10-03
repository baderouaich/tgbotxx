#pragma once
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
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
      inline static const cpr::Timeout TIMEOUT = 25 * 1000;               // 25s (Telegram server can take up to 25s to reply us (should be longer than long poll timeout)). Max long polling timeout seems to be 50s.
      inline static const cpr::ConnectTimeout CONNECT_TIMEOUT = 20 * 1000;// 20s (Telegram server can take up to 20s to connect with us)
      inline static const std::int32_t LONG_POLL_TIMEOUT = 10;            // 10s (calling getUpdates() every 10 seconds)
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
      /// @returns the sent Message is returned on success.
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
      /// @param parseMode Optional. Mode for parsing entities in the message text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
      /// @param captionEntities Optional. A JSON-serialized list of special entities that appear in the new caption, which can be specified instead of parseMode
      /// @param hasSpoiler Optional. Pass True if the photo needs to be covered with a spoiler animation
      /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
      /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
      /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
      /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
      /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
      ///                    One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
      /// @returns the sent Message is returned on success.
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
      /// @param parseMode Optional. Mode for parsing entities in the message text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
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

    public:/// @defgroup Commands
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