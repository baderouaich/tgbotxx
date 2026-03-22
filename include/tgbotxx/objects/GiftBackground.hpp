#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object describes the background of a gift.
  /// @ref https://core.telegram.org/bots/api#giftbackground
  struct GiftBackground {
    GiftBackground() = default;
    explicit GiftBackground(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Center color of the background in RGB format
    std::int32_t centerColor{};

    /// @brief Edge color of the background in RGB format
    std::int32_t edgeColor{};

    /// @brief Text color of the background in RGB format
    std::int32_t textColor{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "center_color", centerColor);
      OBJECT_SERIALIZE_FIELD(json, "edge_color", edgeColor);
      OBJECT_SERIALIZE_FIELD(json, "text_color", textColor);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "center_color", centerColor, 0x000000, false);
      OBJECT_DESERIALIZE_FIELD(json, "edge_color", edgeColor, 0x000000, false);
      OBJECT_DESERIALIZE_FIELD(json, "text_color", textColor, 0x000000, false);
    }
  };
}