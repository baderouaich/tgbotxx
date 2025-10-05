#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Sticker.hpp>

namespace tgbotxx {
  /// @brief This object describes the colors of the backdrop of a unique gift.
  /// @ref https://core.telegram.org/bots/api#uniquegiftbackdropcolors
  struct UniqueGiftBackdropColors {
    UniqueGiftBackdropColors() = default;
    explicit UniqueGiftBackdropColors(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The color in the center of the backdrop in RGB format
    std::int32_t centerColor{};

    /// @brief The color on the edges of the backdrop in RGB format
    std::int32_t edgeColor{};

    /// @brief The color to be applied to the symbol in RGB format
    std::int32_t symbolColor{};

    /// @brief The color for the text on the backdrop in RGB format
    std::int32_t textColor{};

    /// @brief Serializes this object to JSON
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "center_color", centerColor);
      OBJECT_SERIALIZE_FIELD(json, "edge_color", edgeColor);
      OBJECT_SERIALIZE_FIELD(json, "symbol_color", symbolColor);
      OBJECT_SERIALIZE_FIELD(json, "text_color", textColor);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "center_color", centerColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "edge_color", edgeColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "symbol_color", symbolColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "text_color", textColor, 0, false);
    }
  };

}
