#pragma once
#include <tgbotxx/objects/ChatJoinRequest.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/ChosenInlineResult.hpp>
#include <tgbotxx/objects/InlineQuery.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/PreCheckoutQuery.hpp>
#include <tgbotxx/objects/ShippingQuery.hpp>
#include <tgbotxx/objects/ChatMemberUpdated.hpp>
#include <vector>
#include <tgbotxx/utils/Ptr.hpp>

namespace tgbotxx {
    class Api;
    struct Message;
    struct Update;

    class Bot {
        Ptr<Api> m_api;
        std::vector<Ptr<Update>> m_updates;
        std::int32_t m_lastUpdateId;
        bool m_running;

    public:
        /// @brief Constructs a new Bot object
        /// @param token Bot token from the BotFather
        explicit Bot(const std::string& token);

        /// @brief Start the bot
        void start();

        /// @brief Stop the bot
        void stop();

    public: /// Bot Callbacks
        /// @brief Called before Bot starts receiving updates (triggered by Bot::start())
        /// Use this callback to initialize your code, set commands..
        virtual void onStart() {}

        /// @brief Called when Bot is about to be stopped (triggered by Bot::stop())
        /// Cleanup your code in this callback (close handles, backup data...)
        virtual void onStop() {}

        /// @brief Called when a new message is received of any kind - text, photo, sticker, etc.
        /// @param message Received message object
        virtual void onAnyMessage(const Ptr<Message>& message) {}

        /// @brief Called when a non-command message is received of any kind - text, photo, sticker, etc.
        /// @param message Received non-command message object
        virtual void onNonCommandMessage(const Ptr<Message>& message) {}

        /// @brief Called when a new command is received (messages with leading '/' char).
        /// @param command Received command object
        virtual void onCommand(const Ptr<Message>& command) {}

        /// @brief Called when an unknown command is received (messages with leading '/' char).
        /// @param message Received unknown command object
        /// @note Known commands are set with Bot::setCommands()
        virtual void onUnknownCommand(const Ptr<Message>& message) {}

        /// @brief Called when a new version of a message that is known to the bot and was edited
        /// @param editedMessage Edited Message object
        virtual void onEditedMessage(const Ptr<Message>& editedMessage) {}

        /// @brief Called when a new incoming inline query is received
        /// @param inlineQuery InlineQuery object
        virtual void onInlineQuery(const Ptr<InlineQuery>& inlineQuery) {}

        /// @brief Called when the result of an inline query that was chosen by a user and sent to their chat partner.
        /// @note Please see our documentation on the feedback collecting for details on how to enable these updates for your bot. https://core.telegram.org/bots/inline#collecting-feedback
        /// @param chosenInlineResult ChosenInlineResult object
        virtual void onChosenInlineResult(const Ptr<ChosenInlineResult>& chosenInlineResult) {}

        /// @brief Called when a new incoming callback query is received
        /// @param callbackQuery CallbackQuery object
        virtual void onCallbackQuery(const Ptr<CallbackQuery>& callbackQuery) {}

        /// @brief Called when a new incoming shipping query is received.
        /// @note Only for invoices with flexible price
        /// @param shippingQuery ShippingQuery object
        virtual void onShippingQuery(const Ptr<ShippingQuery>& shippingQuery) {}

        /// @brief Called when a new incoming pre-checkout query is received. Contains full information about checkout
        /// @param preCheckoutQuery PreCheckoutQuery object
        virtual void onPreCheckoutQuery(const Ptr<PreCheckoutQuery>& preCheckoutQuery) {}

        /// @brief Called when a new poll state is received.
        /// @note Bots receive only updates about stopped polls and polls, which are sent by the bot
        /// @param poll Poll object
        virtual void onPoll(const Ptr<Poll>& poll) {}

        /// @brief Called when a user changed their answer in a non-anonymous poll.
        /// @note Bots receive new votes only in polls that were sent by the bot itself.
        /// @param pollAnswer PollAnswer object
        virtual void onPollAnswer(const Ptr<PollAnswer>& pollAnswer) {}

        /// @brief Called when the bot's chat member status was updated in a chat.
        /// @note For private chats, this update is received only when the bot is blocked or unblocked by the user.
        /// @param myChatMemberUpdated ChatMemberUpdated object
        virtual void onMyChatMember(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) {}

        /// @brief Called when a chat member's status was updated in a chat.
        /// @note The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates.
        /// @param chatMemberUpdated ChatMemberUpdated object
        virtual void onChatMember(const Ptr<ChatMemberUpdated>& chatMemberUpdated) {}

        /// @brief Called when a A request to join the chat has been sent.
        /// @note The bot must have the can_invite_users administrator right in the chat to receive these updates.
        /// @param chatJoinRequest ChatJoinRequest object
        virtual void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) {}


    protected: /// Getters
        const Ptr<Api>& getApi() const noexcept;
        const Ptr<Api>& api() const noexcept { return getApi(); }

    private:
        /// @brief Dispatch update to callbacks
        /// @param update: Update to dispatch
        void dispatch(const Ptr<Update>& update);
        /// @brief Dispatch a message to callbacks.
        /// A Message can be a Command, EditedMessage, Normal Message, Channel Post... this function will dispatch accordingly
        /// @param message: Message to dispatch
        void dispatchMessage(const Ptr<Message>& message);
    };

}