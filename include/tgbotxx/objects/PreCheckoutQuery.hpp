#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>

namespace tgbotxx {
    /// @brief This object contains information about an incoming pre-checkout query.
    /// @ref https://core.telegram.org/bots/api#precheckoutquery
    struct PreCheckoutQuery {
        explicit PreCheckoutQuery(const nl::json &json) {
          fromJson(json);
        }

        /// @brief Unique query identifier
        std::string id;

        /// @brief User who sent the query
        Ptr<User> from;

        /// @brief Three-letter ISO 4217 currency code
        /// @note Supported currencies: https://core.telegram.org/bots/payments#supported-currencies
        std::string currency;

        /// @brief Total price in the smallest units of the currency (integer, not float/double).
        /// For example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in currencies.json,
        /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
        std::int64_t totalAmount;

        /// @brief Bot specified invoice payload
        std::string invoicePayload;

        /// @brief Optional. Identifier of the shipping option chosen by the user
        std::string shippingOptionId;

        /// @brief Optional. Order information provided by the user
        Ptr<OrderInfo> orderInfo;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "id", id);
          OBJECT_SERIALIZE_FIELD_PTR(json, "from", from, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "currency", currency);
          OBJECT_SERIALIZE_FIELD(json, "total_amount", totalAmount);
          OBJECT_SERIALIZE_FIELD(json, "invoice_payload", invoicePayload);
          OBJECT_SERIALIZE_FIELD(json, "shipping_option_id", shippingOptionId);
          OBJECT_SERIALIZE_FIELD_PTR(json, "order_info", orderInfo, nl::json::object());
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
          OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "total_amount", totalAmount, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "invoice_payload", invoicePayload, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "shipping_option_id", shippingOptionId, "", true);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "order_info", orderInfo, true);
        }
    };
}
