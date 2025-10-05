#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a change in the price of paid messages within a chat.
  /// @ref https://core.telegram.org/bots/api#paidmessagepricechanged
  struct PaidMessagePriceChanged {
    PaidMessagePriceChanged() = default;
    explicit PaidMessagePriceChanged(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The new number of Telegram Stars that must be paid by non-administrator users for each message
    std::int64_t paidMessageStarCount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "paid_message_star_count", paidMessageStarCount);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "paid_message_star_count", paidMessageStarCount, 0, false);
    }
  };
}
