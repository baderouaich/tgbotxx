#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/SuggestedPostPrice.hpp>

namespace tgbotxx {
  /// @brief Contains parameters of a post that is being suggested by the bot.
  /// @ref https://core.telegram.org/bots/api#suggestedpostparameters
  struct SuggestedPostParameters {
    SuggestedPostParameters() = default;
    explicit SuggestedPostParameters(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Proposed price for the post. If the field is omitted, then the post is unpaid.
    Ptr<SuggestedPostPrice> price;

    /// @brief Optional. Proposed send date of the post. If specified, then the date must be between 300 second
    /// and 2678400 seconds (30 days) in the future. If the field is omitted, then the post can be published at any time
    /// within 30 days at the sole discretion of the user who approves it.
    std::time_t sendDate{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "price", price);
      OBJECT_SERIALIZE_FIELD(json, "send_date", sendDate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "price", price, true);
      OBJECT_DESERIALIZE_FIELD(json, "send_date", sendDate, 0, true);
    }
  };

}
