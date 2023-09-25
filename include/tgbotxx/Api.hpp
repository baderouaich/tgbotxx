#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Animation.hpp>
#include <tgbotxx/objects/Audio.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/BotCommandScope.hpp>
#include <tgbotxx/objects/CallbackGame.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
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
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/MessageAutoDeleteTimerChanged.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>
#include <tgbotxx/objects/PassportData.hpp>
#include <tgbotxx/objects/PassportFile.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/PollOption.hpp>
#include <tgbotxx/objects/PreCheckoutQuery.hpp>
#include <tgbotxx/objects/ProximityAlertTriggered.hpp>
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
    class Update;
    class BotCommand;
    class BotCommandScope;

    class Api {
        inline static const std::string BASE_URL = "https://api.telegram.org";
        inline static const cpr::Timeout TIMEOUT = 25 * 1000; // 25s (Telegram server can take up to 25s to reply us (should be longer than long poll timeout))
        inline static const cpr::ConnectTimeout CONNECT_TIMEOUT = 20 * 1000; // 20s (Telegram server can take up to 20s to connect with us)
        inline static const std::int32_t LONG_POLL_TIMEOUT = 10; // 10s (calling getUpdates() evert 10 seconds)
        std::string m_token;

    public:
        /// @brief Constructs Api object.
        /// @param token: Bot Token from FatherBot.
        Api(const std::string& token);

    public: /// @defgroup Api Methods
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
        /// @param A JSON-serialized list of the update types you want your bot to receive.
        /// For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types.
        /// See Update for a complete list of available update types. Specify an empty list to receive all update types
        /// except chat_member (default). If not specified, the previous setting will be used.
        /// @note: Please note that this parameter doesn't affect updates created before the call to the getUpdates,
        /// so unwanted updates may be received for a short period of time.
        /// @returns an Array of Update objects.
        /// @note This method will not work if an outgoing webhook is set up.
        /// @note In order to avoid getting duplicate updates, recalculate offset after each server response.
        /// @link ref https://core.telegram.org/bots/api#getupdates @endlink
        std::vector<Ptr<Update>> getUpdates(std::int32_t offset, std::int32_t limit = 100, std::int32_t timeout = LONG_POLL_TIMEOUT, const std::vector<std::string>& allowedUpdates = {}) const;

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