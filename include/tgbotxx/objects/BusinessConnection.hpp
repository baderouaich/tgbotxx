#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/BusinessBotRights.hpp>

namespace tgbotxx {

  /// @brief Describes the connection of the bot with a business account.
  /// @ref https://core.telegram.org/bots/api#businessconnection
  struct BusinessConnection {
    BusinessConnection() = default;
    explicit BusinessConnection(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the business connection
    std::string id;

    /// @brief Business account user that created the business connection
    Ptr<User> user;

    /// @brief Identifier of a private chat with the user who created the business connection.
    /// This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects
    /// in interpreting it. But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
    std::int64_t userChatId{};

    /// @brief Date the connection was established in Unix time
    std::int32_t date{};

    /// @brief Optional. Rights of the business bot
    Ptr<BusinessBotRights> rights;

    /// @brief True, if the connection is active
    bool isEnabled{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      OBJECT_SERIALIZE_FIELD(json, "user_chat_id", userChatId);
      OBJECT_SERIALIZE_FIELD(json, "date", date);
      OBJECT_SERIALIZE_FIELD_PTR(json, "rights", rights);
      OBJECT_SERIALIZE_FIELD(json, "is_enabled", isEnabled);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
      OBJECT_DESERIALIZE_FIELD(json, "user_chat_id", userChatId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "rights", rights, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_enabled", isEnabled, false, false);
    }
  };

}
