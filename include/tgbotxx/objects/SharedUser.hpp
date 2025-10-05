#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
  /// @brief This object contains information about a user that was shared with the bot using a KeyboardButtonRequestUsers button.
  /// @ref https://core.telegram.org/bots/api#shareduser
  struct SharedUser {
    SharedUser() = default;
    explicit SharedUser(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Identifier of the shared user.
    /// This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
    /// But it has at most 52 significant bits, so 64-bit integers or double-precision float types are safe for storing these identifiers.
    /// The bot may not have access to the user and could be unable to use this identifier,
    /// unless the user is already known to the bot by some other means.
    std::int64_t userId{};

    /// @brief Optional. First name of the user, if the name was requested by the bot
    std::string firstName;

    /// @brief Optional. Last name of the user, if the name was requested by the bot
    std::string lastName;

    /// @brief Optional. Username of the user, if the username was requested by the bot
    std::string username;

    /// @brief Optional. Available sizes of the chat photo, if the photo was requested by the bot
    std::vector<Ptr<PhotoSize>> photo;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "user_id", userId);
      OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
      OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
      OBJECT_SERIALIZE_FIELD(json, "username", username);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "user_id", userId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "username", username, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo, true);
    }
  };
}