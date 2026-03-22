#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about an ownership change in the chat.
  /// @ref https://core.telegram.org/bots/api#chatownerchanged
  struct ChatOwnerChanged {
    ChatOwnerChanged() = default;
    explicit ChatOwnerChanged(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The new owner of the chat
    Ptr<User> newOwner;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "new_owner", newOwner);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "new_owner", newOwner, false);
    }
  };
}
