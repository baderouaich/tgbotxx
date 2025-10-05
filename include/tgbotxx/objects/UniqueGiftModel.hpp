#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Sticker.hpp>

namespace tgbotxx {
  /// @brief This object describes the model of a unique gift.
  /// @ref https://core.telegram.org/bots/api#uniquegiftmodel
  struct UniqueGiftModel {
    UniqueGiftModel() = default;
    explicit UniqueGiftModel(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Name of the model
    std::string name;

    /// @brief The sticker that represents the unique gift
    Ptr<Sticker> sticker;

    /// @brief The number of unique gifts that receive this model for every 1000 gifts upgraded
    std::int32_t rarityPerMille{};

    /// @brief Serializes this object to JSON
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "name", name);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sticker", sticker);
      OBJECT_SERIALIZE_FIELD(json, "rarity_per_mille", rarityPerMille);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sticker", sticker, false);
      OBJECT_DESERIALIZE_FIELD(json, "rarity_per_mille", rarityPerMille, 0, false);
    }
  };
}