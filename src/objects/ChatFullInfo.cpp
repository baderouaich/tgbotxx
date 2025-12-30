#include <tgbotxx/objects/ChatFullInfo.hpp>
using namespace tgbotxx;

ChatFullInfo::ChatFullInfo(const nl::json& json) {
  ChatFullInfo::fromJson(json);
}

nl::json ChatFullInfo::toJson() const override {
  nl::json json = Chat::toJson();
  OBJECT_SERIALIZE_FIELD(json, "accent_color_id", accentColorId);
  OBJECT_SERIALIZE_FIELD(json, "max_reaction_count", maxReactionCount);
  OBJECT_SERIALIZE_FIELD_PTR(json, "photo", photo);
  OBJECT_SERIALIZE_FIELD(json, "active_usernames", activeUsernames);
  OBJECT_SERIALIZE_FIELD_PTR(json, "birthdate", birthdate);
  OBJECT_SERIALIZE_FIELD_PTR(json, "business_intro", businessIntro);
  OBJECT_SERIALIZE_FIELD_PTR(json, "business_opening_hours", businessOpeningHours);
  OBJECT_SERIALIZE_FIELD_PTR(json, "personal_chat", personalChat);
  OBJECT_SERIALIZE_FIELD_PTR(json, "parent_chat", parentChat);
  OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "available_reactions", availableReactions);
  OBJECT_SERIALIZE_FIELD(json, "background_custom_emoji_id", backgroundCustomEmojiId);
  OBJECT_SERIALIZE_FIELD(json, "profile_accent_color_id", profileAccentColorId);
  OBJECT_SERIALIZE_FIELD(json, "profile_background_custom_emoji_id", profileBackgroundCustomEmojiId);
  OBJECT_SERIALIZE_FIELD(json, "emoji_status_custom_emoji_id", emojiStatusCustomEmojiId);
  OBJECT_SERIALIZE_FIELD(json, "emoji_status_expiration_date", emojiStatusExpirationDate);
  OBJECT_SERIALIZE_FIELD(json, "bio", bio);
  OBJECT_SERIALIZE_FIELD(json, "has_private_forwards", hasPrivateForwards);
  OBJECT_SERIALIZE_FIELD(json, "has_restricted_voice_and_video_messages", hasRestrictedVoiceAndVideoMessages);
  OBJECT_SERIALIZE_FIELD(json, "join_to_send_messages", joinToSendMessages);
  OBJECT_SERIALIZE_FIELD(json, "join_by_request", joinByRequest);
  OBJECT_SERIALIZE_FIELD(json, "description", description);
  OBJECT_SERIALIZE_FIELD(json, "invite_link", inviteLink);
  OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage);
  OBJECT_SERIALIZE_FIELD_PTR(json, "permissions", permissions);
  OBJECT_SERIALIZE_FIELD(json, "slow_mode_delay", slowModeDelay);
  OBJECT_SERIALIZE_FIELD(json, "unrestrict_boost_count", unrestrictBoostCount);
  OBJECT_SERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime);
  OBJECT_SERIALIZE_FIELD(json, "has_aggressive_anti_spam_enabled", hasAggressiveAntiSpamEnabled);
  OBJECT_SERIALIZE_FIELD(json, "has_hidden_members", hasHiddenMembers);
  OBJECT_SERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent);
  OBJECT_SERIALIZE_FIELD(json, "has_visible_history", hasVisibleHistory);
  OBJECT_SERIALIZE_FIELD(json, "sticker_set_name", stickerSetName);
  OBJECT_SERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet);
  OBJECT_SERIALIZE_FIELD(json, "custom_emoji_sticker_set_name", customEmojiStickerSetName);
  OBJECT_SERIALIZE_FIELD(json, "linked_chat_id", linkedChatId);
  OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
  return json;
}


void ChatFullInfo::fromJson(const nl::json& json) override {
  Chat::fromJson(json);
  OBJECT_DESERIALIZE_FIELD(json, "accent_color_id", accentColorId, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "max_reaction_count", maxReactionCount, 0, false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "photo", photo, true);
  OBJECT_DESERIALIZE_FIELD(json, "active_usernames", activeUsernames, std::vector<std::string>(), true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "birthdate", birthdate, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "business_intro", businessIntro, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "business_opening_hours", businessOpeningHours, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "personal_chat", personalChat, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "parent_chat", parentChat, true);
  OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "available_reactions", availableReactions, true);
  OBJECT_DESERIALIZE_FIELD(json, "background_custom_emoji_id", backgroundCustomEmojiId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "profile_accent_color_id", profileAccentColorId, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "profile_background_custom_emoji_id", profileBackgroundCustomEmojiId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "emoji_status_custom_emoji_id", emojiStatusCustomEmojiId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "emoji_status_expiration_date", emojiStatusExpirationDate, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "bio", bio, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "has_private_forwards", hasPrivateForwards, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_restricted_voice_and_video_messages", hasRestrictedVoiceAndVideoMessages, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "join_to_send_messages", joinToSendMessages, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "join_by_request", joinByRequest, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "invite_link", inviteLink, "", true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "permissions", permissions, true);
  OBJECT_DESERIALIZE_FIELD(json, "slow_mode_delay", slowModeDelay, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "unrestrict_boost_count", unrestrictBoostCount, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime, 0, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_aggressive_anti_spam_enabled", hasAggressiveAntiSpamEnabled, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_hidden_members", hasHiddenMembers, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_visible_history", hasVisibleHistory, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "sticker_set_name", stickerSetName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "custom_emoji_sticker_set_name", customEmojiStickerSetName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "linked_chat_id", linkedChatId, 0, true);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
}
