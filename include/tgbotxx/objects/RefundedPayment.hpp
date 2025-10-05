#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object contains basic information about a refunded payment.
  /// @ref https://core.telegram.org/bots/api#refundedpayment
  struct RefundedPayment {
    RefundedPayment() = default;
    explicit RefundedPayment(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Three-letter ISO 4217 currency code, or “XTR” for payments in Telegram Stars. Currently, always “XTR”
    /// @link https://t.me/BotNews/90 @endlink
    /// @link https://core.telegram.org/bots/payments#supported-currencies @endlink
    std::string currency;

    /// @brief Total refunded price in the smallest units of the currency (integer, not float/double).
    /// For example, for a price of US$ 1.45, total_amount = 145.
    /// See the exp parameter in currencies.json, it shows the number of digits past the decimal point
    /// for each currency (2 for the majority of currencies).
    /// @link https://core.telegram.org/bots/payments/currencies.json @endlink
    std::int64_t totalAmount{};

    /// @brief Bot-specified invoice payload
    std::string invoicePayload;

    /// @brief Telegram payment identifier
    std::string telegramPaymentChargeId;

    /// @brief Optional. Provider payment identifier
    std::string providerPaymentChargeId;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "currency", currency);
      OBJECT_SERIALIZE_FIELD(json, "total_amount", totalAmount);
      OBJECT_SERIALIZE_FIELD(json, "invoice_payload", invoicePayload);
      OBJECT_SERIALIZE_FIELD(json, "telegram_payment_charge_id", telegramPaymentChargeId);
      OBJECT_SERIALIZE_FIELD(json, "provider_payment_charge_id", providerPaymentChargeId);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "currency", currency, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "total_amount", totalAmount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "invoice_payload", invoicePayload, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "telegram_payment_charge_id", telegramPaymentChargeId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "provider_payment_charge_id", providerPaymentChargeId, "", true);
    }
  };
}