#include <tgbotxx/objects/Chat.hpp>
using namespace tgbotxx;

Chat::Chat(const nl::json& json) {
  _fromJson(json);
}

void Chat::_fromJson(const nl::json& json) {
  fromJson(json);
}

std::optional<std::string> Chat::TypeToString(const Type type) noexcept {
  if (type == Type::Private) return "private";
  if (type == Type::Group) return "group";
  if (type == Type::Supergroup) return "supergroup";
  if (type == Type::Channel) return "channel";
  return std::nullopt;
}

std::optional<Chat::Type> Chat::StringToType(const std::string& str) noexcept {
  if (str == "private") return Type::Private;
  if (str == "group") return Type::Group;
  if (str == "supergroup") return Type::Supergroup;
  if (str == "channel") return Type::Channel;
  return std::nullopt;
}



nl::json Chat::toJson() const {
  nl::json json = nl::json::object();
  OBJECT_SERIALIZE_FIELD(json, "id", id);
  OBJECT_SERIALIZE_FIELD_ENUM(json, Type, "type", type);
  OBJECT_SERIALIZE_FIELD(json, "title", title);
  OBJECT_SERIALIZE_FIELD(json, "username", username);
  OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
  OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
  OBJECT_SERIALIZE_FIELD(json, "is_forum", isForum);
  OBJECT_SERIALIZE_FIELD(json, "is_direct_messages", isDirectMessages);
  return json;
}

void Chat::fromJson(const nl::json& json) {
  OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
  OBJECT_DESERIALIZE_FIELD_ENUM(json, Type, "type", type, 0, false);
  OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "username", username, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "is_forum", isForum, false, true);
  OBJECT_DESERIALIZE_FIELD(json, "is_direct_messages", isDirectMessages, false, true);
}
