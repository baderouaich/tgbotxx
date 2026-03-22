#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/UniqueGift.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a unique gift that was sent or received.
  /// @ref https://core.telegram.org/bots/api#uniquegiftinfo
  struct UniqueGiftInfo {
    UniqueGiftInfo() = default;
    explicit UniqueGiftInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Information about the gift
    Ptr<UniqueGift> gift;

    /// @briefOrigin of the gift. Currently, either:
    /// - “upgrade” for gifts upgraded from regular gifts,
    /// - “transfer” for gifts transferred from other users or channels,
    /// - “resale” for gifts bought from other users,
    /// - “gifted_upgrade” for upgrades purchased after the gift was sent, or
    /// - “offer” for gifts bought or sold through gift purchase offers
    std::string origin;

    /// @brief Optional. For gifts bought from other users, the currency in which the payment for the gift was done.
    /// Currently, one of “XTR” for Telegram Stars or “TON” for toncoins.
    std::string lastResaleCurrency{};

    /// @brief Optional. For gifts bought from other users, the price paid for the gift in either Telegram Stars or nanotoncoins
    std::int64_t lastResaleAmount{};

    /// @brief Optional. Unique identifier of the received gift for the bot;
    /// only present for gifts received on behalf of business accounts
    std::string ownedGiftId;

    /// @brief Optional. Number of Telegram Stars that must be paid to transfer the gift;
    /// omitted if the bot cannot transfer the gift
    std::int64_t transferStarCount{};

    /// @brief Optional. Point in time (Unix timestamp) when the gift can be transferred.
    /// If it is in the past, then the gift can be transferred now
    std::time_t nextTransferDate{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      OBJECT_SERIALIZE_FIELD(json, "origin", origin);
      OBJECT_SERIALIZE_FIELD(json, "last_resale_currency", lastResaleCurrency);
      OBJECT_SERIALIZE_FIELD(json, "last_resale_amount", lastResaleAmount);
      OBJECT_SERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId);
      OBJECT_SERIALIZE_FIELD(json, "transfer_star_count", transferStarCount);
      OBJECT_SERIALIZE_FIELD(json, "next_transfer_date", nextTransferDate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, false);
      OBJECT_DESERIALIZE_FIELD(json, "origin", origin, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "last_resale_currency", lastResaleCurrency, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "last_resale_amount", lastResaleAmount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "transfer_star_count", transferStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "next_transfer_date", nextTransferDate, 0, true);
    }
  };
}