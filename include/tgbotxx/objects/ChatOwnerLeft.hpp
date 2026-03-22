#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about the chat owner leaving the chat.
  /// @ref https://core.telegram.org/bots/api#chatownerleft
  struct ChatOwnerLeft {
    ChatOwnerLeft() = default;
    explicit ChatOwnerLeft(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. The user which will be the new owner of the chat if the previous owner does not return to the chat
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
      OBJECT_DESERIALIZE_FIELD_PTR(json, "new_owner", newOwner, true);
    }
  };
}
