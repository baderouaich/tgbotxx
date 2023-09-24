#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object contains basic information about an invoice.
    /// @ref https://core.telegram.org/bots/api#invoice
    struct Invoice {
        explicit Invoice(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Product name
        std::string title;

        /// @brief Product description
        std::string description;

        /// @brief Unique bot deep-linking parameter that can be used to generate this invoice
        std::string startParameter;

        /// @brief Three-letter ISO 4217 currency code
        /// @link currency https://core.telegram.org/bots/payments#supported-currencies @endlink
        std::string currency;

        /// @brief Total price in the smallest units of the currency (integer, not float/double).
        /// For example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in currencies.json,
        /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
        /// @link currencies https://core.telegram.org/bots/payments/currencies.json @endlink
        std::int32_t totalAmount;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "title", title);
          OBJECT_SERIALIZE_FIELD(json, "description", description);
          OBJECT_SERIALIZE_FIELD(json, "start_parameter", startParameter);
          OBJECT_SERIALIZE_FIELD(json, "currency", currency);
          OBJECT_SERIALIZE_FIELD(json, "total_amount", totalAmount);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "description", description, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "start_parameter", startParameter, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "total_amount", totalAmount, 0, false);
        }
    };
}