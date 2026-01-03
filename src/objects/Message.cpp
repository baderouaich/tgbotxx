#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChecklistTasksDone.hpp>
#include <tgbotxx/objects/ChecklistTasksAdded.hpp>
#include <tgbotxx/objects/GiveawayCompleted.hpp>
#include <tgbotxx/objects/SuggestedPostApproved.hpp>
#include <tgbotxx/objects/SuggestedPostApprovalFailed.hpp>
#include <tgbotxx/objects/SuggestedPostDeclined.hpp>
#include <tgbotxx/objects/SuggestedPostPaid.hpp>
#include <tgbotxx/objects/SuggestedPostRefunded.hpp>
using namespace tgbotxx;

nl::json Message::toJson() const {
  nl::json json = nl::json::object();
  OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
  OBJECT_SERIALIZE_FIELD(json, "message_thread_id", messageThreadId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "direct_messages_topic", directMessagesTopic);
  OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
  OBJECT_SERIALIZE_FIELD_PTR(json, "sender_chat", senderChat);
  OBJECT_SERIALIZE_FIELD(json, "sender_boost_count", senderBoostCount);
  OBJECT_SERIALIZE_FIELD_PTR(json, "sender_business_bot", senderBusinessBot);
  OBJECT_SERIALIZE_FIELD(json, "date", date);
  OBJECT_SERIALIZE_FIELD(json, "business_connection_id", businessConnectionId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forward_origin", forwardOrigin);
  OBJECT_SERIALIZE_FIELD(json, "is_topic_message", isTopicMessage);
  OBJECT_SERIALIZE_FIELD(json, "is_automatic_forward", isAutomaticForward);
  OBJECT_SERIALIZE_FIELD_PTR(json, "reply_to_message", replyToMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "external_reply", externalReply);
  OBJECT_SERIALIZE_FIELD_PTR(json, "quote", quote);
  OBJECT_SERIALIZE_FIELD(json, "reply_to_checklist_task_id", replyToChecklistTaskId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "reply_to_story", replyToStory);
  OBJECT_SERIALIZE_FIELD_PTR(json, "via_bot", viaBot);
  OBJECT_SERIALIZE_FIELD(json, "edit_date", editDate);
  OBJECT_SERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent);
  OBJECT_SERIALIZE_FIELD(json, "is_from_offline", isFromOffline);
  OBJECT_SERIALIZE_FIELD(json, "is_paid_post", isPaidPost);
  OBJECT_SERIALIZE_FIELD(json, "media_group_id", mediaGroupId);
  OBJECT_SERIALIZE_FIELD(json, "author_signature", authorSignature);
  OBJECT_SERIALIZE_FIELD(json, "paid_star_count", paidStarCount);
  OBJECT_SERIALIZE_FIELD(json, "text", text);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
  OBJECT_SERIALIZE_FIELD_PTR(json, "link_preview_options", linkPreviewOptions);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_info", suggestedPostInfo);
  OBJECT_SERIALIZE_FIELD(json, "effect_id", effectId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "animation", animation);
  OBJECT_SERIALIZE_FIELD_PTR(json, "audio", audio);
  OBJECT_SERIALIZE_FIELD_PTR(json, "document", document);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo);
  OBJECT_SERIALIZE_FIELD_PTR(json, "sticker", sticker);
  OBJECT_SERIALIZE_FIELD_PTR(json, "story", story);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video", video);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video_note", videoNote);
  OBJECT_SERIALIZE_FIELD_PTR(json, "voice", voice);
  OBJECT_SERIALIZE_FIELD(json, "caption", caption);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
  OBJECT_SERIALIZE_FIELD(json, "show_caption_above_media", showCaptionAboveMedia);
  OBJECT_SERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler);
  OBJECT_SERIALIZE_FIELD_PTR(json, "checklist", checklist);
  OBJECT_SERIALIZE_FIELD_PTR(json, "contact", contact);
  OBJECT_SERIALIZE_FIELD_PTR(json, "dice", dice);
  OBJECT_SERIALIZE_FIELD_PTR(json, "game", game);
  OBJECT_SERIALIZE_FIELD_PTR(json, "poll", poll);
  OBJECT_SERIALIZE_FIELD_PTR(json, "venue", venue);
  OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_members", newChatMembers);
  OBJECT_SERIALIZE_FIELD_PTR(json, "left_chat_member", leftChatMember);
  OBJECT_SERIALIZE_FIELD(json, "new_chat_title", newChatTitle);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_photo", newChatPhoto);
  OBJECT_SERIALIZE_FIELD(json, "delete_chat_photo", deleteChatPhoto);
  OBJECT_SERIALIZE_FIELD(json, "group_chat_created", groupChatCreated);
  OBJECT_SERIALIZE_FIELD(json, "supergroup_chat_created", supergroupChatCreated);
  OBJECT_SERIALIZE_FIELD(json, "channel_chat_created", channelChatCreated);
  OBJECT_SERIALIZE_FIELD_PTR(json, "message_auto_delete_timer_changed", messageAutoDeleteTimerChanged);
  OBJECT_SERIALIZE_FIELD(json, "migrate_to_chat_id", migrateToChatId);
  OBJECT_SERIALIZE_FIELD(json, "migrate_from_chat_id", migrateFromChatId);
  // MaybeInaccessibleMessage
  if (std::holds_alternative<Ptr<Message>>(pinnedMessage)) {
    OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", std::get<0>(pinnedMessage));
  } else {
    OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", std::get<1>(pinnedMessage));
  }
  OBJECT_SERIALIZE_FIELD_PTR(json, "invoice", invoice);
  OBJECT_SERIALIZE_FIELD_PTR(json, "successful_payment", successfulPayment);
  OBJECT_SERIALIZE_FIELD_PTR(json, "refunded_payment", refundedPayment);
  OBJECT_SERIALIZE_FIELD_PTR(json, "users_shared", usersShared);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_shared", chatShared);
  OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
  OBJECT_SERIALIZE_FIELD_PTR(json, "unique_gift", uniqueGift);
  OBJECT_SERIALIZE_FIELD(json, "connected_website", connectedWebsite);
  OBJECT_SERIALIZE_FIELD_PTR(json, "write_access_allowed", writeAccessAllowed);
  OBJECT_SERIALIZE_FIELD_PTR(json, "passport_data", passportData);
  OBJECT_SERIALIZE_FIELD_PTR(json, "proximity_alert_triggered", proximityAlertTriggered);
  OBJECT_SERIALIZE_FIELD_PTR(json, "boost_added", boostAdded);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_background_set", chatBackgroundSet);
  OBJECT_SERIALIZE_FIELD_PTR(json, "checklist_tasks_done", checklistTasksDone);
  OBJECT_SERIALIZE_FIELD_PTR(json, "checklist_tasks_added", checklistTasksAdded);
  OBJECT_SERIALIZE_FIELD_PTR(json, "direct_message_price_changed", directMessagePriceChanged);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_created", forumTopicCreated);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_edited", forumTopicEdited);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_closed", forumTopicClosed);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_reopened", forumTopicReopened);
  OBJECT_SERIALIZE_FIELD_PTR(json, "general_forum_topic_hidden", generalForumTopicHidden);
  OBJECT_SERIALIZE_FIELD_PTR(json, "general_forum_topic_unhidden", generalForumTopicUnhidden);
  OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway_created", giveawayCreated);
  OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway", giveaway);
  OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway_winners", giveawayWinners);
  OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway_completed", giveawayCompleted);
  OBJECT_SERIALIZE_FIELD_PTR(json, "paid_message_price_changed", paidMessagePriceChanged);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_approved", suggestedPostApproved);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_approval_failed", suggestedPostApprovalFailed);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_declined", suggestedPostDeclined);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_paid", suggestedPostPaid);
  OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_refunded", suggestedPostRefunded);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video_chat_scheduled", videoChatScheduled);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video_chat_started", videoChatStarted);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video_chat_ended", videoChatEnded);
  OBJECT_SERIALIZE_FIELD_PTR(json, "video_chat_participants_invited", videoChatParticipantsInvited);
  OBJECT_SERIALIZE_FIELD_PTR(json, "web_app_data", webAppData);
  OBJECT_SERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup);
  return json;
}

void Message::fromJson(const nl::json& json) {
  OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
  OBJECT_DESERIALIZE_FIELD(json, "message_thread_id", messageThreadId, 0, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "direct_messages_topic", directMessagesTopic, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_chat", senderChat, true);
  OBJECT_DESERIALIZE_FIELD(json, "sender_boost_count", senderBoostCount, 0, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_business_bot", senderBusinessBot, true);
  OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
  OBJECT_DESERIALIZE_FIELD(json, "business_connection_id", businessConnectionId, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forward_origin", forwardOrigin, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_topic_message", isTopicMessage, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_automatic_forward", isAutomaticForward, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_to_message", replyToMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "external_reply", externalReply, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "quote", quote, true);
  OBJECT_DESERIALIZE_FIELD(json, "reply_to_checklist_task_id", replyToChecklistTaskId, 0, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_to_story", replyToStory, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "via_bot", viaBot, true);
  OBJECT_DESERIALIZE_FIELD(json, "edit_date", editDate, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_from_offline", isFromOffline, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_paid_post", isPaidPost, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "media_group_id", mediaGroupId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "author_signature", authorSignature, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "paid_star_count", paidStarCount, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "text", text, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "link_preview_options", linkPreviewOptions, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_info", suggestedPostInfo, true);
  OBJECT_DESERIALIZE_FIELD(json, "effect_id", effectId, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "animation", animation, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "audio", audio, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "document", document, true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "sticker", sticker, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "story", story, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video", video, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_note", videoNote, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "voice", voice, true);
  OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
  OBJECT_DESERIALIZE_FIELD(json, "show_caption_above_media", showCaptionAboveMedia, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist", checklist, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "contact", contact, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "dice", dice, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "game", game, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "poll", poll, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "venue", venue, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_members", newChatMembers, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "left_chat_member", leftChatMember, true);
  OBJECT_DESERIALIZE_FIELD(json, "new_chat_title", newChatTitle, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_photo", newChatPhoto, true);
  OBJECT_DESERIALIZE_FIELD(json, "delete_chat_photo", deleteChatPhoto, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "group_chat_created", groupChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "supergroup_chat_created", supergroupChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "channel_chat_created", channelChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "message_auto_delete_timer_changed", messageAutoDeleteTimerChanged, true);
  OBJECT_DESERIALIZE_FIELD(json, "migrate_to_chat_id", migrateToChatId, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "migrate_from_chat_id", migrateFromChatId, 0, true);
  // MaybeInaccessibleMessage
  if (json.contains("pinned_message")) {
    // date: Always 0. The field can be used to differentiate regular and inaccessible messages.
    const bool isInaccessibleMessage = json["pinned_message"].contains("date") && json["pinned_message"]["date"].get<std::time_t>() == 0;
    if (isInaccessibleMessage) {
      pinnedMessage = makePtr<InaccessibleMessage>();
      auto& inaccessibleMessage = std::get<Ptr<InaccessibleMessage>>(pinnedMessage);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "pinned_message", inaccessibleMessage, true);
    } else { // Regular message
      pinnedMessage = makePtr<Message>();
      auto& regularMessage = std::get<Ptr<Message>>(pinnedMessage);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "pinned_message", regularMessage, true);
    }
  }
  OBJECT_DESERIALIZE_FIELD_PTR(json, "invoice", invoice, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "successful_payment", successfulPayment, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "refunded_payment", refundedPayment, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "users_shared", usersShared, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_shared", chatShared, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "unique_gift", uniqueGift, true);
  OBJECT_DESERIALIZE_FIELD(json, "connected_website", connectedWebsite, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "write_access_allowed", writeAccessAllowed, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "passport_data", passportData, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "proximity_alert_triggered", proximityAlertTriggered, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "boost_added", boostAdded, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_background_set", chatBackgroundSet, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist_tasks_done", checklistTasksDone, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist_tasks_added", checklistTasksAdded, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "direct_message_price_changed", directMessagePriceChanged, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_created", forumTopicCreated, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_edited", forumTopicEdited, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_closed", forumTopicClosed, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_reopened", forumTopicReopened, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "general_forum_topic_hidden", generalForumTopicHidden, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "general_forum_topic_unhidden", generalForumTopicUnhidden, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway_created", giveawayCreated, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway", giveaway, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway_winners", giveawayWinners, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway_completed", giveawayCompleted, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "paid_message_price_changed", paidMessagePriceChanged, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_approved", suggestedPostApproved, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_approval_failed", suggestedPostApprovalFailed, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_declined", suggestedPostDeclined, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_paid", suggestedPostPaid, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_refunded", suggestedPostRefunded, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_scheduled", videoChatScheduled, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_started", videoChatStarted, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_ended", videoChatEnded, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_participants_invited", videoChatParticipantsInvited, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app_data", webAppData, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup, true);
}