#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes data sent from a Web App to the bot.
  /// @ref https://core.telegram.org/bots/api#webappdata
  struct WebAppData {
      WebAppData() = default;
      explicit WebAppData(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The data. Be aware that a bad client can send arbitrary data in this field.
      std::string data;

      /// @brief Text of the web_app keyboard button from which the Web App was opened.
      /// @note Be aware that a bad client can send arbitrary data in this field.
      std::string buttonText;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "data", data);
        OBJECT_SERIALIZE_FIELD(json, "button_text", buttonText);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "data", data, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "button_text", buttonText, "", false);
      }
  };
}