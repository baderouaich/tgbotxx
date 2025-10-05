#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents type of a poll, which is allowed to be created and sent when the corresponding button is pressed.
  /// @ref https://core.telegram.org/bots/api#keyboardbuttonpolltype
  struct KeyboardButtonPollType {
      KeyboardButtonPollType() = default;
      explicit KeyboardButtonPollType(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Optional. “quiz“ or “regular“.
      /// If “quiz“ is passed, the user will be allowed to create only polls in the quiz mode.
      /// If “regular“ is passed, only regular polls will be allowed.
      /// Otherwise, the user will be allowed to create a poll of any type.
      std::string type;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", true);
      }
  };
}