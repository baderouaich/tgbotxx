#pragma once
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <tgbotxx/objects/CallbackGame.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>
#include <tgbotxx/objects/Chat.hpp>
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
#include <tgbotxx/objects/InlineKeyboardButton.hpp>
#include <tgbotxx/objects/InlineKeyboardMarkup.hpp>
#include <tgbotxx/objects/InlineQuery.hpp>
#include <tgbotxx/objects/Invoice.hpp>
#include <tgbotxx/objects/IReplyMarkup.hpp>
#include <tgbotxx/objects/KeyboardButton.hpp>
#include <tgbotxx/objects/KeyboardButtonPollType.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestChat.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestUser.hpp>
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/MessageAutoDeleteTimerChanged.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>
#include <tgbotxx/objects/PassportData.hpp>
#include <tgbotxx/objects/PassportFile.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/Poll.hpp>
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
#include <tgbotxx/objects/VideoChatEnded.hpp>
#include <tgbotxx/objects/VideoChatParticipantsInvited.hpp>
#include <tgbotxx/objects/VideoChatScheduled.hpp>
#include <tgbotxx/objects/VideoChatStarted.hpp>
#include <tgbotxx/objects/Video.hpp>
#include <tgbotxx/objects/VideoNote.hpp>
#include <tgbotxx/objects/Voice.hpp>
#include <tgbotxx/objects/WebAppData.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>
#include <tgbotxx/objects/WriteAccessAllowed.hpp>
#include <string>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

namespace nl = nlohmann;

namespace tgbotxx {
    /// @brief Api Methods https://core.telegram.org/bots/api#available-methods
    /// @note All methods in the Bot API are case-insensitive.
    /// @note We support GET and POST HTTP methods. Use either URL query string or application/json or application/x-www-form-urlencoded or multipart/form-data for passing parameters in Bot API requests.
    class Api {
        inline static const std::string BASE_URL = "https://api.telegram.org";
        inline static const cpr::Timeout TIMEOUT = 25 * 1000; // 25s (Telegram server can take up to 25s to reply us (should be longer than long poll timeout)). Max long polling timeout seems to be 50s.
        inline static const cpr::ConnectTimeout CONNECT_TIMEOUT = 20 * 1000; // 20s (Telegram server can take up to 20s to connect with us)
        inline static const std::int32_t LONG_POLL_TIMEOUT = 10; // 10s (calling getUpdates() every 10 seconds)
        const std::string m_token;
        mutable cpr::Session m_session;

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
        /// @param disableWebPagePreview Optional. Disables link previews for links in this message
        /// @param replyToMessageId Optional. If the message is a reply, ID of the original message
        /// @param replyMarkup Optional. Additional interface options. A JSON-serialized object for an inline keyboard, custom reply keyboard, instructions to remove reply keyboard or to force a reply from the user.
        /// @param parseMode Optional. Mode for parsing entities in the message text. See formatting options for more details. https://core.telegram.org/bots/api#formatting-options
        /// @param disableNotification Optional. Sends the message silently. Users will receive a notification with no sound.
        /// @param entities Optional. A JSON-serialized list of special entities that appear in message text, which can be specified instead of parse_mode
        /// @param allowSendingWithoutReply Optional. Pass True if the message should be sent even if the specified replied-to message is not found
        /// @param protectContent Optional. Protects the contents of the sent message from forwarding and saving
        /// @param messageThreadId Optional. Unique identifier for the target message thread (topic) of the forum; for forum supergroups only
        ///        One of InlineKeyboardMarkup or ReplyKeyboardMarkup or ReplyKeyboardRemove or ForceReply.
        /// @returns sent Message object on success.
        /// @ref https://core.telegram.org/bots/api#sendmessage
        Ptr<Message> sendMessage(const std::int64_t& chatId,
                                 const std::string& text,
                                 bool disableWebPagePreview = false,
                                 std::int64_t replyToMessageId = 0,
                                 const Ptr<IReplyMarkup>& replyMarkup = nullptr,
                                 const std::string& parseMode = "",
                                 bool disableNotification = false,
                                 const std::vector<Ptr<MessageEntity>>& entities = std::vector<Ptr<MessageEntity>>(),
                                 bool allowSendingWithoutReply = false,
                                 bool protectContent = false,
                                 std::int64_t messageThreadId = 0) const;

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
        std::vector<Ptr<BotCommand>> getMyCommands( const Ptr<BotCommandScope>& scope = nullptr, const std::string& languageCode = "") const;

        /// Todo: ...

    private:
        nl::json sendRequest(const std::string& endpoint, const cpr::Multipart& data = cpr::Multipart({})) const;
    };
}