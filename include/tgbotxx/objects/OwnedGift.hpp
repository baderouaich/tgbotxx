#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Gift.hpp>
#include <tgbotxx/objects/UniqueGift.hpp>

namespace tgbotxx {

  /// @brief Base class for a gift owned by a user or a chat
  /// Can be either OwnedGiftRegular or OwnedGiftUnique
  struct OwnedGift {
    OwnedGift() = default;
    explicit OwnedGift(const nl::json& json) {
      OwnedGift::fromJson(json);
    }
    virtual ~OwnedGift() = default;

    /// @brief Type of the gift: "regular" or "unique"
    std::string type;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief Describes a regular gift owned by a user or a chat
  struct OwnedGiftRegular : OwnedGift {
    OwnedGiftRegular() = default;
    explicit OwnedGiftRegular(const nl::json& json) {
      OwnedGiftRegular::fromJson(json);
      // OwnedGift::type = "regular";
    }
    ~OwnedGiftRegular() override = default;

    /// @brief Information about the regular gift
    Ptr<Gift> gift;

    /// @brief Optional. Unique identifier of the gift for the bot; for gifts received on behalf of business accounts only
    std::string ownedGiftId;

    /// @brief Optional. Sender of the gift if it is a known user
    Ptr<User> senderUser;

    /// @brief Date the gift was sent in Unix time
    std::int64_t sendDate{};

    /// @brief Optional. Text of the message that was added to the gift
    std::string text;

    /// @brief Optional. Special entities that appear in the text
    std::vector<Ptr<MessageEntity>> entities;

    /// @brief Optional. True, if the sender and gift text are shown only to the gift receiver
    bool isPrivate{};

    /// @brief Optional. True, if the gift is displayed on the account's profile page; for gifts received on behalf of business accounts only
    bool isSaved{};

    /// @brief Optional. True, if the gift can be upgraded to a unique gift; for gifts received on behalf of business accounts only
    bool canBeUpgraded{};

    /// @brief Optional. True, if the gift was refunded and isn't available anymore
    bool wasRefunded{};

    /// @brief Optional. Number of Telegram Stars that can be claimed by the receiver instead of the gift
    std::int32_t convertStarCount{};

    /// @brief Optional. Number of Telegram Stars that were paid by the sender for the ability to upgrade the gift
    std::int32_t prepaidUpgradeStarCount{};

    /// @brief Serializes this object to JSON
    nl::json toJson() const override {
      nl::json json = OwnedGift::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      OBJECT_SERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sender_user", senderUser);
      OBJECT_SERIALIZE_FIELD(json, "send_date", sendDate);
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
      OBJECT_SERIALIZE_FIELD(json, "is_private", isPrivate);
      OBJECT_SERIALIZE_FIELD(json, "is_saved", isSaved);
      OBJECT_SERIALIZE_FIELD(json, "can_be_upgraded", canBeUpgraded);
      OBJECT_SERIALIZE_FIELD(json, "was_refunded", wasRefunded);
      OBJECT_SERIALIZE_FIELD(json, "convert_star_count", convertStarCount);
      OBJECT_SERIALIZE_FIELD(json, "prepaid_upgrade_star_count", prepaidUpgradeStarCount);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      OwnedGift::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, false);
      OBJECT_DESERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_user", senderUser, true);
      OBJECT_DESERIALIZE_FIELD(json, "send_date", sendDate, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_private", isPrivate, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_saved", isSaved, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_be_upgraded", canBeUpgraded, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "was_refunded", wasRefunded, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "convert_star_count", convertStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "prepaid_upgrade_star_count", prepaidUpgradeStarCount, 0, true);
    }
  };

  /// @brief Describes a unique gift owned by a user or a chat
  struct OwnedGiftUnique : OwnedGift {
    OwnedGiftUnique() = default;
    explicit OwnedGiftUnique(const nl::json& json) {
      OwnedGiftUnique::fromJson(json);
    }
    ~OwnedGiftUnique() override = default;

    /// @brief Information about the unique gift
    Ptr<UniqueGift> gift;

    /// @brief Optional. Unique identifier of the received gift for the bot; for gifts received on behalf of business accounts only
    std::string ownedGiftId;

    /// @brief Optional. Sender of the gift if it is a known user
    Ptr<User> senderUser;

    /// @brief Date the gift was sent in Unix time
    std::int64_t sendDate{};

    /// @brief Optional. True, if the gift is displayed on the account's profile page; for gifts received on behalf of business accounts only
    bool isSaved{};

    /// @brief Optional. True, if the gift can be transferred to another owner; for gifts received on behalf of business accounts only
    bool canBeTransferred{};

    /// @brief Optional. Number of Telegram Stars that must be paid to transfer the gift
    std::int32_t transferStarCount{};

    /// @brief Optional. Point in time (Unix timestamp) when the gift can be transferred. If it is in the past, then the gift can be transferred now
    std::int64_t nextTransferDate{};

    /// @brief Serializes this object to JSON
    [[nodiscard]] nl::json toJson() const override {
      nl::json json = OwnedGift::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      OBJECT_SERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sender_user", senderUser);
      OBJECT_SERIALIZE_FIELD(json, "send_date", sendDate);
      OBJECT_SERIALIZE_FIELD(json, "is_saved", isSaved);
      OBJECT_SERIALIZE_FIELD(json, "can_be_transferred", canBeTransferred);
      OBJECT_SERIALIZE_FIELD(json, "transfer_star_count", transferStarCount);
      OBJECT_SERIALIZE_FIELD(json, "next_transfer_date", nextTransferDate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      OwnedGift::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, false);
      OBJECT_DESERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_user", senderUser, true);
      OBJECT_DESERIALIZE_FIELD(json, "send_date", sendDate, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_saved", isSaved, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_be_transferred", canBeTransferred, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "transfer_star_count", transferStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "next_transfer_date", nextTransferDate, 0, true);
    }
  };

}
