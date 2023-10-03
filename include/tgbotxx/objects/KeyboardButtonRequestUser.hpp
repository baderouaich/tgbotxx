#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object defines the criteria used to request a suitable user.
  /// The identifier of the selected user will be shared with the bot when the corresponding button is pressed.
  /// More about requesting users » https://core.telegram.org/bots/features#chat-and-user-selection
  /// @ref https://core.telegram.org/bots/api#keyboardbuttonrequestuser
  struct KeyboardButtonRequestUser {
      KeyboardButtonRequestUser() = default;
      explicit KeyboardButtonRequestUser(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Signed 32-bit identifier of the request, which will be received back in the UserShared object.
      /// @note Must be unique within the message
      std::int32_t requestId{};

      /// @brief Optional. Pass True to request a bot, pass False to request a regular user. If not specified, no additional restrictions are applied.
      bool userIsBot{};

      /// @brief Optional. Pass True to request a premium user, pass False to request a non-premium user. If not specified, no additional restrictions are applied.
      bool userIsPremium{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "request_id", requestId);
        OBJECT_SERIALIZE_FIELD(json, "user_is_bot", userIsBot);
        OBJECT_SERIALIZE_FIELD(json, "user_is_premium", userIsPremium);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "request_id", requestId, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "user_is_bot", userIsBot, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "user_is_premium", userIsPremium, false, true);
      }
  };
}