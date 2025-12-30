#include <tgbotxx/objects/CallbackQuery.hpp>
#include <tgbotxx/objects/Message.hpp>
using namespace tgbotxx;

CallbackQuery::CallbackQuery(const nl::json& json) {
  fromJson(json);
}

nl::json CallbackQuery::toJson() const {
  nl::json json = nl::json::object();
  OBJECT_SERIALIZE_FIELD(json, "id", id);
  OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
  // MaybeInaccessibleMessage
  std::visit([&json](const auto& msg) { OBJECT_SERIALIZE_FIELD_PTR(json, "message", msg); }, message);
  OBJECT_SERIALIZE_FIELD(json, "inline_message_id", inlineMessageId);
  OBJECT_SERIALIZE_FIELD(json, "chat_instance", chatInstance);
  OBJECT_SERIALIZE_FIELD(json, "data", data);
  OBJECT_SERIALIZE_FIELD(json, "game_short_name", gameShortName);
  return json;
}

void CallbackQuery::fromJson(const nl::json& json) {
  OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
  OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
  // MaybeInaccessibleMessage
  if (json.contains("message")) {
    // date: Always 0. The field can be used to differentiate regular and inaccessible messages.
    const bool isInaccessibleMessage = json["message"].contains("date") && json["message"]["date"].get<std::time_t>() == 0;
    if (isInaccessibleMessage) {
      message = makePtr<InaccessibleMessage>();
      auto& inaccessibleMessage = std::get<Ptr<InaccessibleMessage>>(message);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "message", inaccessibleMessage, true);
    } else { // Regular message
      message = makePtr<Message>();
      auto& regularMessage = std::get<Ptr<Message>>(message);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "message", regularMessage, true);
    }
  }
  OBJECT_DESERIALIZE_FIELD(json, "inline_message_id", inlineMessageId, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "chat_instance", chatInstance, "", false);
  OBJECT_DESERIALIZE_FIELD(json, "data", data, "", true);
  OBJECT_DESERIALIZE_FIELD(json, "game_short_name", gameShortName, "", true);
}