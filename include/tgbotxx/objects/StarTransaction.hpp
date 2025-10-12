#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/TransactionPartner.hpp>
#include <vector>

namespace tgbotxx {

  /// @brief Describes a Telegram Star transaction.
  /// Note that if the buyer initiates a chargeback with the payment provider from whom they acquired Stars
  /// (e.g., Apple, Google) following this transaction, the refunded Stars will be deducted from the bot's balance.
  /// This is outside of Telegram's control.
  /// @ref https://core.telegram.org/bots/api#startransaction
  struct StarTransaction {
    StarTransaction() = default;
    explicit StarTransaction(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the transaction.
    /// Coincides with the identifier of the original transaction for refund transactions.
    /// Coincides with SuccessfulPayment.telegram_payment_charge_id for successful incoming payments from users.
    std::string id;

    /// @brief Integer amount of Telegram Stars transferred by the transaction
    std::int64_t amount{};

    /// @brief Optional. The number of 1/1000000000 shares of Telegram Stars transferred by the transaction; from 0 to 999999999
    std::int32_t nanostarAmount{};

    /// @brief Date the transaction was created in Unix time
    std::time_t date{};

    /// @brief Optional. Source of an incoming transaction (e.g., a user purchasing goods or services, Fragment refunding a failed withdrawal). Only for incoming transactions
    Ptr<TransactionPartner> source;

    /// @brief Optional. Receiver of an outgoing transaction (e.g., a user for a purchase refund, Fragment for a withdrawal). Only for outgoing transactions
    Ptr<TransactionPartner> receiver;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD(json, "amount", amount);
      OBJECT_SERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount);
      OBJECT_SERIALIZE_FIELD(json, "date", date);
      OBJECT_SERIALIZE_FIELD_PTR(json, "source", source);
      OBJECT_SERIALIZE_FIELD_PTR(json, "receiver", receiver);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "source", source, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "receiver", receiver, true);
    }
  };


}
