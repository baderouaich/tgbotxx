#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents an inline keyboard button that copies specified text to the clipboard.
  /// @ref https://core.telegram.org/bots/api#copytextbutton
  struct CopyTextButton {
    CopyTextButton() = default;
    explicit CopyTextButton(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The text to be copied to the clipboard; 1-256 characters
    std::string text;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
    }
  };

}
