#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Gift.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a regular gift that was sent or received.
  /// @ref https://core.telegram.org/bots/api#giftinfo
  struct GiftInfo {
    GiftInfo() = default;
    explicit GiftInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Information about the gift
    Ptr<Gift> gift;

    /// @brief Optional. Unique identifier of the received gift for the bot; only present for gifts received on behalf of business accounts
    std::string ownedGiftId;

    /// @brief Optional. Number of Telegram Stars that can be claimed by the receiver by converting the gift;
    /// omitted if conversion to Telegram Stars is impossible
    std::int64_t convertStarCount{};

    /// @brief Optional. Number of Telegram Stars that were prepaid by the sender for the ability to upgrade the gift
    std::int64_t prepaidUpgradeStarCount{};

    /// @brief Optional. True, if the gift can be upgraded to a unique gift
    bool canBeUpgraded{};

    /// @brief Optional. Text of the message that was added to the gift
    std::string text;

    /// @brief Optional. Special entities that appear in the text
    std::vector<Ptr<MessageEntity>> entities;

    /// @brief Optional. True, if the sender and gift text are shown only to the gift receiver; otherwise, everyone will be able to see them
    bool isPrivate{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      OBJECT_SERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId);
      OBJECT_SERIALIZE_FIELD(json, "convert_star_count", convertStarCount);
      OBJECT_SERIALIZE_FIELD(json, "prepaid_upgrade_star_count", prepaidUpgradeStarCount);
      OBJECT_SERIALIZE_FIELD(json, "can_be_upgraded", canBeUpgraded);
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
      OBJECT_SERIALIZE_FIELD(json, "is_private", isPrivate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, false);
      OBJECT_DESERIALIZE_FIELD(json, "owned_gift_id", ownedGiftId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "convert_star_count", convertStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "prepaid_upgrade_star_count", prepaidUpgradeStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_be_upgraded", canBeUpgraded, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_private", isPrivate, false, true);
    }
  };
}