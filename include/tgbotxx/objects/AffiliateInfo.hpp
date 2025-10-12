#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {

  /// @brief Contains information about the affiliate that received a commission via a transaction
  /// @ref https://core.telegram.org/bots/api#affiliateinfo
  struct AffiliateInfo {
    AffiliateInfo() = default;
    explicit AffiliateInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. The bot or user that received an affiliate commission
    Ptr<User> affiliateUser;

    /// @brief Optional. The chat that received an affiliate commission
    Ptr<Chat> affiliateChat;

    /// @brief The number of Telegram Stars received by the affiliate for each 1000 Stars received by the bot
    std::int32_t commissionPerMille{};

    /// @brief Integer amount of Telegram Stars received by the affiliate from the transaction; can be negative for refunds
    std::int32_t amount{};

    /// @brief Optional. The number of 1/1000000000 shares of Telegram Stars received by the affiliate; can be negative for refunds
    std::int32_t nanostarAmount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "affiliate_user", affiliateUser);
      OBJECT_SERIALIZE_FIELD_PTR(json, "affiliate_chat", affiliateChat);
      OBJECT_SERIALIZE_FIELD(json, "commission_per_mille", commissionPerMille);
      OBJECT_SERIALIZE_FIELD(json, "amount", amount);
      OBJECT_SERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "affiliate_user", affiliateUser, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "affiliate_chat", affiliateChat, true);
      OBJECT_DESERIALIZE_FIELD(json, "commission_per_mille", commissionPerMille, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "amount", amount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "nanostar_amount", nanostarAmount, 0, true);
    }
  };

}
