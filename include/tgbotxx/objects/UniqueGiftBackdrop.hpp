#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/UniqueGiftBackdropColors.hpp>

namespace tgbotxx {
  /// @brief This object describes the backdrop of a unique gift.
  /// @ref https://core.telegram.org/bots/api#uniquegiftbackdrop
  struct UniqueGiftBackdrop {
    UniqueGiftBackdrop() = default;
    explicit UniqueGiftBackdrop(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Name of the backdrop
    std::string name;

    /// @brief Colors of the backdrop
    Ptr<UniqueGiftBackdropColors> colors;

    /// @brief The number of unique gifts that receive this backdrop for every 1000 gifts upgraded
    std::int32_t rarityPerMille{};

    /// @brief Serializes this object to JSON
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "name", name);
      OBJECT_SERIALIZE_FIELD_PTR(json, "colors", colors);
      OBJECT_SERIALIZE_FIELD(json, "rarity_per_mille", rarityPerMille);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "colors", colors, false);
      OBJECT_DESERIALIZE_FIELD(json, "rarity_per_mille", rarityPerMille, 0, false);
    }
  };

}
