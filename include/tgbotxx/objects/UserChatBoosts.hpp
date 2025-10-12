#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ChatBoost.hpp>

namespace tgbotxx {

  /// @brief This object represents a list of boosts added to a chat by a user.
  /// @ref https://core.telegram.org/bots/api#userchatboosts
  struct UserChatBoosts {
    UserChatBoosts() = default;
    explicit UserChatBoosts(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The list of boosts added to the chat by the user
    std::vector<Ptr<ChatBoost>> boosts;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "boosts", boosts);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "boosts", boosts, false);
    }
  };

}
