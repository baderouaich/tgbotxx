#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief Base class representing the state of a revenue withdrawal operation
  /// @ref https://core.telegram.org/bots/api#revenuewithdrawalstate
  struct RevenueWithdrawalState {
    RevenueWithdrawalState() = default;
    explicit RevenueWithdrawalState(const nl::json& json) {
      _fromJson(json);
    }
    virtual ~RevenueWithdrawalState() = default;

    /// @brief Type of the state
    std::string type;

    /// @brief Serializes this object to JSON
    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }

  private:
    /// @brief Avoid calling virtual fromJson in constructor
    void _fromJson(const nl::json& json) {
      fromJson(json);
    }
  };

  /// @brief The withdrawal is in progress
  struct RevenueWithdrawalStatePending : RevenueWithdrawalState {
    RevenueWithdrawalStatePending() {
      RevenueWithdrawalState::type = "pending";
    }
    explicit RevenueWithdrawalStatePending(const nl::json& json) : RevenueWithdrawalState(json) {
      RevenueWithdrawalState::type = "pending";
    }
  };

  /// @brief The withdrawal succeeded
  struct RevenueWithdrawalStateSucceeded : RevenueWithdrawalState {
    RevenueWithdrawalStateSucceeded() {
      RevenueWithdrawalState::type = "succeeded";
    }
    explicit RevenueWithdrawalStateSucceeded(const nl::json& json) : RevenueWithdrawalState(json) {
      RevenueWithdrawalState::type = "succeeded";
    }

    /// @brief Date the withdrawal was completed in Unix time
    std::time_t date{};

    /// @brief An HTTPS URL that can be used to see transaction details
    std::string url;

    nl::json toJson() const override {
      nl::json json = RevenueWithdrawalState::toJson();
      OBJECT_SERIALIZE_FIELD(json, "date", date);
      OBJECT_SERIALIZE_FIELD(json, "url", url);
      return json;
    }

    void fromJson(const nl::json& json) override {
      RevenueWithdrawalState::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "url", url, "", false);
    }
  };

  /// @brief The withdrawal failed and the transaction was refunded
  struct RevenueWithdrawalStateFailed : RevenueWithdrawalState {
    RevenueWithdrawalStateFailed() {
      RevenueWithdrawalState::type = "failed";
    }
    explicit RevenueWithdrawalStateFailed(const nl::json& json) : RevenueWithdrawalState(json) {
      RevenueWithdrawalState::type = "failed";
    }
  };

}
