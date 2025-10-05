#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/StarAmount.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a successful payment for a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostpaid
  struct SuggestedPostPaid {
    SuggestedPostPaid() = default;
    explicit SuggestedPostPaid(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the suggested post
    Ptr<Message> suggestedPostMessage;

    /// @brief Currency in which the payment was made ("XTR" for Stars or "TON" for toncoins)
    std::string currency;

    /// @brief Optional. The amount of the currency that was received (nanotoncoins for TON)
    std::int64_t amount{};

    /// @brief Optional. The amount of Telegram Stars that was received
    Ptr<StarAmount> starAmount;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage);
      OBJECT_SERIALIZE_FIELD(json, "currency", currency);
      OBJECT_SERIALIZE_FIELD(json, "amount", amount);
      OBJECT_SERIALIZE_FIELD_PTR(json, "star_amount", starAmount);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage, true);
      OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "star_amount", starAmount, true);
    }
  };

}
