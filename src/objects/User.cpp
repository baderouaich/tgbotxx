#include <tgbotxx/objects/User.hpp>
using namespace tgbotxx;

User::User(const nl::json &json) {
  fromJson(json);
}
nl::json User::toJson() const {
  nl::json user = nl::json::object();
  OBJECT_SERIALIZE_FIELD(user, "id", id);
  OBJECT_SERIALIZE_FIELD(user, "is_bot", isBot);
  OBJECT_SERIALIZE_FIELD(user, "first_name", firstName);
  OBJECT_SERIALIZE_FIELD(user, "last_name", lastName);
  OBJECT_SERIALIZE_FIELD(user, "username", username);
  OBJECT_SERIALIZE_FIELD(user, "language_code", languageCode);
  OBJECT_SERIALIZE_FIELD(user, "is_premium", isPremium);
  OBJECT_SERIALIZE_FIELD(user, "added_to_attachment_menu", addedToAttachmentMenu);
  OBJECT_SERIALIZE_FIELD(user, "can_join_groups", canJoinGroups);
  OBJECT_SERIALIZE_FIELD(user, "can_read_all_group_messages", canReadAllGroupMessages);
  OBJECT_SERIALIZE_FIELD(user, "supports_inline_queries", supportsInlineQueries);
  OBJECT_SERIALIZE_FIELD(user, "can_connect_to_business", canConnectToBusiness);
  OBJECT_SERIALIZE_FIELD(user, "has_main_web_app", hasMainWebApp);
  return user;
}

void User::fromJson(const nl::json &json) {
  OBJECT_DESERIALIZE_FIELD(json, "id", id, -1, false);
  OBJECT_DESERIALIZE_FIELD(json, "is_bot", isBot, false, false);
  OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", false);
  OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "username", username, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "language_code", languageCode, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "is_premium", isPremium, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "added_to_attachment_menu", addedToAttachmentMenu, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "can_join_groups", canJoinGroups, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "can_read_all_group_messages", canReadAllGroupMessages, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "supports_inline_queries", supportsInlineQueries, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "can_connect_to_business", canConnectToBusiness, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "has_main_web_app", hasMainWebApp, false, true);
}