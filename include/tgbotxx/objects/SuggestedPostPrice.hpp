#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes the price of a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostprice
  struct SuggestedPostPrice {
    SuggestedPostPrice() = default;
    explicit SuggestedPostPrice(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Currency in which the post will be paid.
    /// Currently, must be one of “XTR” for Telegram Stars or “TON” for toncoins
    std::string currency;

    /// @brief The amount of the currency that will be paid for the post in the smallest units of the currency, i.e. Telegram Stars or nanotoncoins.
    /// Currently, price in Telegram Stars must be between 5 and 100000,
    /// and price in nanotoncoins must be between 10000000 and 10000000000000.
    std::int64_t amount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "currency", currency);
      OBJECT_SERIALIZE_FIELD(json, "amount", amount);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, false);
    }
  };
}