#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Forward declarations
  struct CallbackQuery;
  struct ChatJoinRequest;
  struct ChatMemberUpdated;
  struct ChosenInlineResult;
  struct InlineQuery;
  struct Message;
  struct Poll;
  struct PollAnswer;
  struct PreCheckoutQuery;
  struct ShippingQuery;
  struct MessageReactionUpdated;
  struct MessageReactionCountUpdated;
  struct ChatBoostUpdated;
  struct ChatBoostRemoved;
  struct BusinessConnection;
  struct BusinessMessagesDeleted;
  struct PaidMediaPurchased;

  /// @brief This object represents an incoming update.
  /// At most one of the optional parameters can be present in any given update.
  /// @ref https://core.telegram.org/bots/api#update
  struct Update {
      Update() = default;
      explicit Update(const nl::json& json);

      /// @brief The update's unique identifier. Update identifiers start from a certain positive number and increase sequentially.
      /// This ID becomes especially handy if you're using webhooks, since it allows you to ignore repeated updates
      /// or to restore the correct update sequence, should they get out of order.
      /// If there are no new updates for at least a week, then identifier of the next update will be chosen randomly
      /// instead of sequentially.
      std::int32_t updateId{};

      /// @brief Optional. New incoming message of any kind — text, photo, sticker, etc.
      Ptr<Message> message;

      /// @brief Optional. New version of a message that is known to the bot and was edited
      Ptr<Message> editedMessage;

      /// @brief Optional. New incoming channel post of any kind — text, photo, sticker, etc.
      Ptr<Message> channelPost;

      /// @brief Optional. New version of a channel post that is known to the bot and was edited
      Ptr<Message> editedChannelPost;

      /// @brief Optional. The bot was connected to or disconnected from a business account, or a user edited an existing connection with the bot
      Ptr<BusinessConnection> businessConnection;

      /// @brief Optional. New message from a connected business account
      Ptr<Message> businessMessage;

      /// @brief Optional. New version of a message from a connected business account
      Ptr<Message> editedBusinessMessage;

      /// @brief Optional. Messages were deleted from a connected business account
      Ptr<BusinessMessagesDeleted> deletedBusinessMessages;

      /// @brief Optional. A reaction to a message was changed by a user. The bot must be an administrator in the chat and
      /// must explicitly specify "message_reaction" in the list of allowed_updates to receive these updates. The update isn't
      /// received for reactions set by bots.
      Ptr<MessageReactionUpdated> messageReaction;

      /// @brief Optional. Reactions to a message with anonymous reactions were changed. The bot must be an administrator in the
      /// chat and must explicitly specify "message_reaction_count" in the list of allowed_updates to receive these updates.
      /// The updates are grouped and can be sent with delay up to a few minutes.
      Ptr<MessageReactionCountUpdated> messageReactionCount;

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

      /// @brief Optional. A user purchased paid media with a non-empty payload sent by the bot in a non-channel chat
      Ptr<PaidMediaPurchased> purchasedPaidMedia;

      /// @brief Optional. New poll state. Bots receive only updates about stopped polls and polls, which are sent by the bot
      Ptr<Poll> poll;

      /// @brief Optional. A user changed their answer in a non-anonymous poll. Bots receive new votes only in polls that were sent by the bot itself.
      Ptr<PollAnswer> pollAnswer;

      /// @brief Optional. The bot's chat member status was updated in a chat. For private chats, this update is received only when the bot is blocked or unblocked by the user.
      Ptr<ChatMemberUpdated> myChatMember;

      /// @brief Optional. A chat member's status was updated in a chat. The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates.
      Ptr<ChatMemberUpdated> chatMember;

      /// @brief Optional. A request to join the chat has been sent. The bot must have the can_invite_users administrator right in the chat to receive these updates.
      Ptr<ChatJoinRequest> chatJoinRequest;

      /// @brief Optional. A chat boost was added or changed. The bot must be an administrator in the chat to receive these updates.
      Ptr<ChatBoostUpdated> chatBoost;

      /// @brief Optional. A boost was removed from a chat. The bot must be an administrator in the chat to receive these updates.
      Ptr<ChatBoostRemoved> removedChatBoost;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      [[nodiscard]] nl::json toJson() const;

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json);
  };
}