#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object contains information about the color scheme for a user's name, message replies and link previews based on a unique gift.
  /// @ref https://core.telegram.org/bots/api#uniquegiftcolors
  struct UniqueGiftColors {
    UniqueGiftColors() = default;
    explicit UniqueGiftColors(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Custom emoji identifier of the unique gift's model
    std::string modelCustomEmojiId{};

    /// @brief Custom emoji identifier of the unique gift's symbol
    std::string symbolCustomEmojiId{};

    /// @brief Main color used in light themes; RGB format
    std::int32_t lightThemeMainColor{};

    /// @brief List of 1-3 additional colors used in light themes; RGB format
    std::vector<std::int32_t> lightThemeOtherColors;

    /// @brief Main color used in dark themes; RGB format
    std::int32_t darkThemeMainColor{};

    /// @brief List of 1-3 additional colors used in dark themes; RGB format
    std::vector<std::int32_t> darkThemeOtherColors;

    /// @brief Serializes this object to JSON
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "model_custom_emoji_id", modelCustomEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "symbol_custom_emoji_id", symbolCustomEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "light_theme_main_color", lightThemeMainColor);
      OBJECT_SERIALIZE_FIELD(json, "light_theme_other_colors", lightThemeOtherColors);
      OBJECT_SERIALIZE_FIELD(json, "dark_theme_main_color", darkThemeMainColor);
      OBJECT_SERIALIZE_FIELD(json, "dark_theme_other_colors", darkThemeOtherColors);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "model_custom_emoji_id", modelCustomEmojiId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "symbol_custom_emoji_id", symbolCustomEmojiId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "light_theme_main_color", lightThemeMainColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "light_theme_other_colors", lightThemeOtherColors, {}, false);
      OBJECT_DESERIALIZE_FIELD(json, "dark_theme_main_color", darkThemeMainColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "dark_theme_other_colors", darkThemeOtherColors, {}, false);
    }
  };

}
