#pragma once
#include "Object.hpp"
#include <nlohmann/json.hpp>
namespace nl = nlohmann;

namespace tgbotxx {
    struct Message;
    /// @brief This object represents an incoming update.
    /// At most one of the optional parameters can be present in any given update.
    /// @ref https://core.telegram.org/bots/api#update
    struct Update {
        explicit Update(const nl::json& json) {
          fromJson(json);
        }

        /// @brief The update's unique identifier.
        /// Update identifiers start from a certain positive number and increase sequentially.
        /// This ID becomes especially handy if you're using webhooks, since it allows you to ignore repeated updates
        /// or to restore the correct update sequence, should they get out of order.
        /// If there are no new updates for at least a week, then identifier of the next update will be chosen randomly
        /// instead of sequentially.
        std::int32_t updateId;

        /// @brief Optional. New incoming message of any kind — text, photo, sticker, etc.
        Ptr<Message> message;

        /// @brief Optional. New version of a message that is known to the bot and was edited
        Ptr<Message> editedMessage;

        /// @brief Optional. New incoming channel post of any kind — text, photo, sticker, etc.
        Ptr<Message> channelPost;

        /// @brief Optional. New version of a channel post that is known to the bot and was edited
        Ptr<Message> editedChannelPost;

        /// @brief Optional. New incoming inline query
        Ptr<InlineQuery> inlineQuery;

        /// @brief Optional. The result of an inline query that was chosen by a user and sent to their chat partner.
        /// Please see our documentation on the feedback collecting for details on how to enable these updates for your bot.
        Ptr<ChosenInlineResult> chosenInlineResult;

        /// @brief Optional. New incoming callback query
        Ptr<CallbackQuery> callbackQuery;

        /// @brief Optional. New incoming shipping query. Only for invoices with flexible price
        Ptr<ShippingQuery> shippingQuery;

        /// @brief Optional. New incoming pre-checkout query. Contains full information about checkout
        Ptr<PreCheckoutQuery> preCheckoutQuery;

        /// @brief Optional. New poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot
        Ptr<Poll> poll;

        /// @brief Optional. A user changed their answer in a non-anonymous poll. Bots receive new votes only in polls that were sent by the bot itself.
        Ptr<PollAnswer> pollAnswer;

        /// @brief Optional. The bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user.
        Ptr<ChatMemberUpdated> myChatMember;

        /// @brief Optional. A chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates.
        Ptr<ChatMemberUpdated> chatMember;

        /// @brief Optional. Optional. A request to join the chat has been sent. The bot must have the can_invite_users administrator right in the chat to receive these updates.
        Ptr<ChatJoinRequest> chatJoinRequest;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json update = nl::json::object();
          OBJECT_SERIALIZE_FIELD(update, "update_id", updateId);
          OBJECT_SERIALIZE_FIELD_OPT(update, "message", message, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "edited_message", editedMessage, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "channel_post", channelPost, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "edited_channel_post", editedChannelPost, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "inline_query", inlineQuery, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "chosen_inline_result", chosenInlineResult, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "callback_query", callbackQuery, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "shipping_query", shippingQuery, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "pre_checkout_query", preCheckoutQuery, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "poll", poll, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "poll_answer", pollAnswer, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "my_chat_member", myChatMember, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "chat_member", chatMember, nl::json::object());
          OBJECT_SERIALIZE_FIELD_OPT(update, "chat_join_request", chatJoinRequest, nl::json::object());
          return update;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "update_id", updateId, 0);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "message", message);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "edited_message", editedMessage);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "channel_post", channelPost);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "edited_channel_post", editedChannelPost);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "inline_query", inlineQuery);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "chosen_inline_result", chosenInlineResult);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "callback_query", callbackQuery);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "shipping_query", shippingQuery);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "pre_checkout_query", preCheckoutQuery);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "poll", poll);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "poll_answer", pollAnswer);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "my_chat_member", myChatMember);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "chat_member", chatMember);
          OBJECT_DESERIALIZE_FIELD_OPT(json, "chat_join_request", chatJoinRequest);
        }
    };
}