#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about the creation of a scheduled giveaway.
  /// @ref https://core.telegram.org/bots/api#giveawaycreated
  struct GiveawayCreated {
    GiveawayCreated() = default;
    explicit GiveawayCreated(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. The number of Telegram Stars to be split between giveaway winners
    std::int32_t prizeStarCount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "prize_star_count", prizeStarCount);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "prize_star_count", prizeStarCount, 0, true);
    }
  };
}