#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/OrderInfo.hpp>

namespace tgbotxx {
  /// @brief This object contains basic information about a successful payment.
  /// @ref https://core.telegram.org/bots/api#successfulpayment
  struct SuccessfulPayment {
      SuccessfulPayment() = default;
      explicit SuccessfulPayment(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Three-letter ISO 4217 currency code
      /// @link currency https://core.telegram.org/bots/payments#supported-currencies @endlink
      std::string currency;

      /// @brief Total price in the smallest units of the currency (integer, not float/double).
      /// For example, for a price of US$ 1.45 pass amount = 145. See the exp parameter in currencies.json,
      /// it shows the number of digits past the decimal point for each currency (2 for the majority of currencies).
      /// @link currencies https://core.telegram.org/bots/payments/currencies.json @endlink
      std::int32_t totalAmount{};

      /// @brief Bot specified invoice payload
      std::string invoicePayload;

      /// @brief Optional. Identifier of the shipping option chosen by the user
      std::string shippingOptionId;

      /// @brief Optional. Order information provided by the user
      Ptr<OrderInfo> orderInfo;

      /// @brief Telegram payment identifier
      std::string telegramPaymentChargeId;

      /// @brief Provider payment identifier
      std::string providerPaymentChargeId;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "currency", currency);
        OBJECT_SERIALIZE_FIELD(json, "total_amount", totalAmount);
        OBJECT_SERIALIZE_FIELD(json, "invoice_payload", invoicePayload);
        OBJECT_SERIALIZE_FIELD(json, "shipping_option_id", shippingOptionId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "order_info", orderInfo, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "telegram_payment_charge_id", telegramPaymentChargeId);
        OBJECT_SERIALIZE_FIELD(json, "provider_payment_charge_id", providerPaymentChargeId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "total_amount", totalAmount, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "invoice_payload", invoicePayload, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "shipping_option_id", shippingOptionId, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "order_info", orderInfo, true);
        OBJECT_DESERIALIZE_FIELD(json, "telegram_payment_charge_id", telegramPaymentChargeId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "provider_payment_charge_id", providerPaymentChargeId, "", false);
      }
  };
}