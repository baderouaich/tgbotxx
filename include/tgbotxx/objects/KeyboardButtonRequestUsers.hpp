#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief TThis object defines the criteria used to request suitable users.
  /// Information about the selected users will be shared with the bot when the corresponding button is pressed.
  /// More about requesting users » https://core.telegram.org/bots/features#chat-and-user-selection
  /// @ref https://core.telegram.org/bots/api#keyboardbuttonrequestusers
  struct KeyboardButtonRequestUsers {
    KeyboardButtonRequestUsers() = default;
    explicit KeyboardButtonRequestUsers(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Signed 32-bit identifier of the request, which will be received back in the UsersShared object.
    /// @link https://core.telegram.org/bots/api#usersshared @endlink
    /// @note Must be unique within the message
    std::int32_t requestId{};

    /// @brief Optional. Pass True to request a bot, pass False to request a regular user. If not specified, no additional restrictions are applied.
    bool userIsBot{};

    /// @brief Optional. Pass True to request a premium user, pass False to request a non-premium user. If not specified, no additional restrictions are applied.
    bool userIsPremium{};

    /// @brief Optional. The maximum number of users to be selected; 1-10. Defaults to 1.
    std::int32_t maxQuantity{1};

    /// @brief Optional. Pass True to request the users' first and last names
    bool requestName{};

    /// @brief Optional. Pass True to request the users' usernames
    bool requestUsername{};

    /// @brief Optional. Pass True to request the users' photos
    bool requestPhoto{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "request_id", requestId);
      OBJECT_SERIALIZE_FIELD(json, "user_is_bot", userIsBot);
      OBJECT_SERIALIZE_FIELD(json, "user_is_premium", userIsPremium);
      OBJECT_SERIALIZE_FIELD(json, "max_quantity", maxQuantity);
      OBJECT_SERIALIZE_FIELD(json, "request_name", requestName);
      OBJECT_SERIALIZE_FIELD(json, "request_username", requestUsername);
      OBJECT_SERIALIZE_FIELD(json, "request_photo", requestPhoto);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "request_id", requestId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "user_is_bot", userIsBot, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "user_is_premium", userIsPremium, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "max_quantity", maxQuantity, 1, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_name", requestName, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_username", requestUsername, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_photo", requestPhoto, false, true);
    }
  };
}