#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/ChatJoinRequest.hpp>
#include <tgbotxx/objects/ChatMemberUpdated.hpp>
#include <tgbotxx/objects/ChosenInlineResult.hpp>
#include <tgbotxx/objects/InlineQuery.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Poll.hpp>
#include <tgbotxx/objects/PollAnswer.hpp>
#include <tgbotxx/objects/PreCheckoutQuery.hpp>
#include <tgbotxx/objects/ShippingQuery.hpp>
#include <tgbotxx/objects/MessageReactionUpdated.hpp>
#include <tgbotxx/objects/MessageReactionCountUpdated.hpp>
#include <tgbotxx/objects/ChatBoostUpdated.hpp>
#include <tgbotxx/objects/ChatBoostRemoved.hpp>
#include <tgbotxx/objects/BusinessConnection.hpp>
#include <tgbotxx/objects/BusinessMessagesDeleted.hpp>
#include <tgbotxx/objects/PaidMediaPurchased.hpp>

using namespace tgbotxx;

Update::Update(const nl::json &json) {
  fromJson(json);
}

nl::json Update::toJson() const {
  nl::json json = nl::json::object();
  OBJECT_SERIALIZE_FIELD(json, "update_id", updateId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "message", message);
  OBJECT_SERIALIZE_FIELD_PTR(json, "edited_message", editedMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "channel_post", channelPost);
  OBJECT_SERIALIZE_FIELD_PTR(json, "edited_channel_post", editedChannelPost);
  OBJECT_SERIALIZE_FIELD_PTR(json, "business_connection", businessConnection);
  OBJECT_SERIALIZE_FIELD_PTR(json, "business_message", businessMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "edited_business_message", editedBusinessMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "deleted_business_messages", deletedBusinessMessages);
  OBJECT_SERIALIZE_FIELD_PTR(json, "message_reaction", messageReaction);
  OBJECT_SERIALIZE_FIELD_PTR(json, "message_reaction_count", messageReactionCount);
  OBJECT_SERIALIZE_FIELD_PTR(json, "inline_query", inlineQuery);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chosen_inline_result", chosenInlineResult);
  OBJECT_SERIALIZE_FIELD_PTR(json, "callback_query", callbackQuery);
  OBJECT_SERIALIZE_FIELD_PTR(json, "shipping_query", shippingQuery);
  OBJECT_SERIALIZE_FIELD_PTR(json, "pre_checkout_query", preCheckoutQuery);
  OBJECT_SERIALIZE_FIELD_PTR(json, "purchased_paid_media", purchasedPaidMedia);
  OBJECT_SERIALIZE_FIELD_PTR(json, "poll", poll);
  OBJECT_SERIALIZE_FIELD_PTR(json, "poll_answer", pollAnswer);
  OBJECT_SERIALIZE_FIELD_PTR(json, "my_chat_member", myChatMember);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_member", chatMember);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_join_request", chatJoinRequest);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_boost", chatBoost);
  OBJECT_SERIALIZE_FIELD_PTR(json, "removed_chat_boost", removedChatBoost);
  return json;
}


void Update::fromJson(const nl::json &json) {
  OBJECT_DESERIALIZE_FIELD(json, "update_id", updateId, 0, false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "message", message, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "edited_message", editedMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "channel_post", channelPost, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "edited_channel_post", editedChannelPost, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "business_connection", businessConnection, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "business_message", businessMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "edited_business_message", editedBusinessMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "deleted_business_messages", deletedBusinessMessages, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "message_reaction", messageReaction, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "inline_query", inlineQuery, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chosen_inline_result", chosenInlineResult, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "callback_query", callbackQuery, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "shipping_query", shippingQuery, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "pre_checkout_query", preCheckoutQuery, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "purchased_paid_media", purchasedPaidMedia, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "poll", poll, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "poll_answer", pollAnswer, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "my_chat_member", myChatMember, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_member", chatMember, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_join_request", chatJoinRequest, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_boost", chatBoost, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "removed_chat_boost", removedChatBoost, true);
}