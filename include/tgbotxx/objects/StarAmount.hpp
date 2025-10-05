#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes an amount of Telegram Stars.
  /// @ref https://core.telegram.org/bots/api#staramount
  struct StarAmount {
    StarAmount() = default;
    explicit StarAmount(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Integer amount of Telegram Stars, rounded to 0; can be negative
    std::int64_t amount{};

    /// @brief Optional. The number of 1/1000000000 shares of Telegram Stars;
    /// from -999999999 to 999999999; can be negative if and only if amount is non-positive
    std::int64_t nanostarAmount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "amount", amount);
      OBJECT_SERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount, 0, true);
    }
  };

}
