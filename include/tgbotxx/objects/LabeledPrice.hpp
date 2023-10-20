#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a portion of the price for goods or services.
  /// @ref https://core.telegram.org/bots/api#labeledprice
  struct LabeledPrice {
      LabeledPrice() = default;
      explicit LabeledPrice(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Portion label
      std::string label;

      /// @brief Price of the product in the smallest units of the currency (integer, not float/double).
      /// For example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in currencies.json,
      /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
      std::int32_t amount{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "label", label);
        OBJECT_SERIALIZE_FIELD(json, "amount", amount);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "label", label, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, false);
      }
  };
}