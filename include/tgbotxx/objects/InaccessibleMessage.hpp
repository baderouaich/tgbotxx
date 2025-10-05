#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief This object describes a message that was deleted or is otherwise inaccessible to the bot.
  /// @ref https://core.telegram.org/bots/api#inaccessiblemessage
  struct InaccessibleMessage {
    InaccessibleMessage() = default;
    explicit InaccessibleMessage(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Chat the message belonged to
    Ptr<Chat> chat;

    /// @brief Unique message identifier inside the chat
    std::int32_t messageId{};

    /// @brief Always 0. The field can be used to differentiate regular and inaccessible messages.
    std::time_t date{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
      OBJECT_SERIALIZE_FIELD(json, "date", date);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
    }
  };
}
