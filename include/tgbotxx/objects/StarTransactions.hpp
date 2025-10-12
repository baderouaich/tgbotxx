#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/StarTransaction.hpp>
#include <vector>

namespace tgbotxx {

  /// @brief Contains a list of Telegram Star transactions.
  /// @ref https://core.telegram.org/bots/api#startransactions
  struct StarTransactions {
    StarTransactions() = default;
    explicit StarTransactions(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The list of transactions
    std::vector<Ptr<StarTransaction>> transactions;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "transactions", transactions);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "transactions", transactions, false);
    }
  };
}