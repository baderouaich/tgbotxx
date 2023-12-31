#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Message.hpp>
using namespace tgbotxx;

nl::json Message::toJson() const {
  nl::json json = nl::json::object();
  OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
  OBJECT_SERIALIZE_FIELD(json, "message_thread_id", messageThreadId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
  OBJECT_SERIALIZE_FIELD_PTR(json, "sender_chat", senderChat);
  OBJECT_SERIALIZE_FIELD(json, "date", date);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forward_from", forwardFrom);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forward_from_chat", forwardFromChat);
  OBJECT_SERIALIZE_FIELD(json, "forward_from_message_id", forwardFromMessageId);
  OBJECT_SERIALIZE_FIELD(json, "forward_signature", forwardSignature);
  OBJECT_SERIALIZE_FIELD(json, "forward_sender_name", forwardSenderName);
  OBJECT_SERIALIZE_FIELD(json, "forward_date", forwardDate);
  OBJECT_SERIALIZE_FIELD(json, "is_topic_message", isTopicMessage);
  OBJECT_SERIALIZE_FIELD(json, "is_automatic_forward", isAutomaticForward);
  OBJECT_SERIALIZE_FIELD_PTR(json, "reply_to_message", replyToMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "via_bot", viaBot);
  OBJECT_SERIALIZE_FIELD(json, "edit_date", editDate);
  OBJECT_SERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent);
  OBJECT_SERIALIZE_FIELD(json, "media_group_id", mediaGroupId);
  OBJECT_SERIALIZE_FIELD(json, "author_signature", authorSignature);
  OBJECT_SERIALIZE_FIELD(json, "text", text);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
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
  OBJECT_SERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler);
  OBJECT_SERIALIZE_FIELD_PTR(json, "contact", contact);
  OBJECT_SERIALIZE_FIELD_PTR(json, "dice", dice);
  OBJECT_SERIALIZE_FIELD_PTR(json, "game", game);
  OBJECT_SERIALIZE_FIELD_PTR(json, "poll", poll);
  OBJECT_SERIALIZE_FIELD_PTR(json, "venue", venue);
  OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_members", newChatMembers);
  OBJECT_SERIALIZE_FIELD_PTR(json, "left_chat_member", leftChatMember);
  OBJECT_SERIALIZE_FIELD(json, "new_chat_title", newChatTitle);
  OBJECT_SERIALIZE_FIELD_PTR(json, "new_chat_photo", newChatPhoto);
  OBJECT_SERIALIZE_FIELD(json, "delete_chat_photo", deleteChatPhoto);
  OBJECT_SERIALIZE_FIELD(json, "group_chat_created", groupChatCreated);
  OBJECT_SERIALIZE_FIELD(json, "supergroup_chat_created", supergroupChatCreated);
  OBJECT_SERIALIZE_FIELD(json, "channel_chat_created", channelChatCreated);
  OBJECT_SERIALIZE_FIELD_PTR(json, "message_auto_delete_timer_changed", messageAutoDeleteTimerChanged);
  OBJECT_SERIALIZE_FIELD(json, "migrate_to_chat_id", migrateToChatId);
  OBJECT_SERIALIZE_FIELD(json, "migrate_from_chat_id", migrateFromChatId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "invoice", invoice);
  OBJECT_SERIALIZE_FIELD_PTR(json, "successful_payment", successfulPayment);
  OBJECT_SERIALIZE_FIELD_PTR(json, "user_shared", userShared);
  OBJECT_SERIALIZE_FIELD_PTR(json, "chat_shared", chatShared);
  OBJECT_SERIALIZE_FIELD(json, "connected_website", connectedWebsite);
  OBJECT_SERIALIZE_FIELD_PTR(json, "write_access_allowed", writeAccessAllowed);
  OBJECT_SERIALIZE_FIELD_PTR(json, "passport_data", passportData);
  OBJECT_SERIALIZE_FIELD_PTR(json, "proximity_alert_triggered", proximityAlertTriggered);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_created", forumTopicCreated);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_edited", forumTopicEdited);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_closed", forumTopicClosed);
  OBJECT_SERIALIZE_FIELD_PTR(json, "forum_topic_reopened", forumTopicReopened);
  OBJECT_SERIALIZE_FIELD_PTR(json, "general_forum_topic_hidden", generalForumTopicHidden);
  OBJECT_SERIALIZE_FIELD_PTR(json, "general_forum_topic_unhidden", generalForumTopicUnhidden);
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
  OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_chat", senderChat, true);
  OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forward_from", forwardFrom, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forward_from_chat", forwardFromChat, true);
  OBJECT_DESERIALIZE_FIELD(json, "forward_from_message_id", forwardFromMessageId, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "forward_signature", forwardSignature, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "forward_sender_name", forwardSenderName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "forward_date", forwardDate, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_topic_message", isTopicMessage, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_automatic_forward", isAutomaticForward, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_to_message", replyToMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "via_bot", viaBot, true);
  OBJECT_DESERIALIZE_FIELD(json, "edit_date", editDate, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "media_group_id", mediaGroupId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "author_signature", authorSignature, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "text", text, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
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
  OBJECT_DESERIALIZE_FIELD(json, "has_media_spoiler", hasMediaSpoiler, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "contact", contact, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "dice", dice, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "game", game, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "poll", poll, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "venue", venue, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "new_chat_members", newChatMembers, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "left_chat_member", leftChatMember, true);
  OBJECT_DESERIALIZE_FIELD(json, "new_chat_title", newChatTitle, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "new_chat_photo", newChatPhoto, true);
  OBJECT_DESERIALIZE_FIELD(json, "delete_chat_photo", deleteChatPhoto, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "group_chat_created", groupChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "supergroup_chat_created", supergroupChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "channel_chat_created", channelChatCreated, false, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "message_auto_delete_timer_changed", messageAutoDeleteTimerChanged, true);
  OBJECT_DESERIALIZE_FIELD(json, "migrate_to_chat_id", migrateToChatId, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "migrate_from_chat_id", migrateFromChatId, 0, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "invoice", invoice, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "successful_payment", successfulPayment, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "user_shared", userShared, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "chat_shared", chatShared, true);
  OBJECT_DESERIALIZE_FIELD(json, "connected_website", connectedWebsite, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "write_access_allowed", writeAccessAllowed, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "passport_data", passportData, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "proximity_alert_triggered", proximityAlertTriggered, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_created", forumTopicCreated, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_edited", forumTopicEdited, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_closed", forumTopicClosed, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "forum_topic_reopened", forumTopicReopened, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "general_forum_topic_hidden", generalForumTopicHidden, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "general_forum_topic_unhidden", generalForumTopicUnhidden, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_scheduled", videoChatScheduled, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_started", videoChatStarted, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_ended", videoChatEnded, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "video_chat_participants_invited", videoChatParticipantsInvited, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app_data", webAppData, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup, true);
}