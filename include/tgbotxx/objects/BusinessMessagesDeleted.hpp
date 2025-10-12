#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {

  /// @brief This object is received when messages are deleted from a connected business account.
  /// @ref https://core.telegram.org/bots/api#businessmessagesdeleted
  struct BusinessMessagesDeleted {
    BusinessMessagesDeleted() = default;
    explicit BusinessMessagesDeleted(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the business connection
    std::string businessConnectionId;

    /// @brief Information about a chat in the business account.
    /// The bot may not have access to the chat or the corresponding user.
    Ptr<Chat> chat;

    /// @brief The list of identifiers of deleted messages in the chat of the business account
    std::vector<std::int32_t> messageIds;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "business_connection_id", businessConnectionId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "message_ids", messageIds);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "business_connection_id", businessConnectionId, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD(json, "message_ids", messageIds, {}, false);
    }
  };

}
