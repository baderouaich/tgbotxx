#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Sticker.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/GiftBackground.hpp>

namespace tgbotxx {
  /// @brief This object represents a gift that can be sent by the bot.
  /// @ref https://core.telegram.org/bots/api#gift
  struct Gift {
    Gift() = default;
    explicit Gift(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the gift
    std::string id;

    /// @brief The sticker that represents the gift
    Ptr<Sticker> sticker;

    /// @brief The number of Telegram Stars that must be paid to send the sticker
    std::int64_t starCount{};

    /// @brief Optional. The number of Telegram Stars that must be paid to upgrade the gift to a unique one
    std::int64_t upgradeStarCount{};

    /// @brief Optional. True, if the gift can only be purchased by Telegram Premium subscribers
    bool isPremium{};

    /// @brief Optional. True, if the gift can be used (after being upgraded) to customize a user's appearance
    bool hasColors{};

    /// @brief Optional. The total number of the gifts of this type that can be sent; for limited gifts only
    std::int64_t totalCount{};

    /// @brief Optional. The number of remaining gifts of this type that can be sent; for limited gifts only
    std::int64_t remainingCount{};

    /// @brief Optional. The total number of gifts of this type that can be sent by the bot; for limited gifts only
    std::int64_t personalTotalCount{};

    /// @brief Optional. The number of remaining gifts of this type that can be sent by the bot; for limited gifts only
    std::int64_t personalRemainingCount{};

    /// @brief Optional. Information about the chat that published the gift
    Ptr<GiftBackground> background;

    /// @brief Optional. The total number of different unique gifts that can be obtained by upgrading the gift
    std::int64_t uniqueGiftVariantCount{};

    /// @brief Optional. Information about the chat that published the gift
    Ptr<Chat> publisherChat;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sticker", sticker);
      OBJECT_SERIALIZE_FIELD(json, "star_count", starCount);
      OBJECT_SERIALIZE_FIELD(json, "upgrade_star_count", upgradeStarCount);
      OBJECT_SERIALIZE_FIELD(json, "is_premium", isPremium);
      OBJECT_SERIALIZE_FIELD(json, "has_colors", hasColors);
      OBJECT_SERIALIZE_FIELD(json, "total_count", totalCount);
      OBJECT_SERIALIZE_FIELD(json, "remaining_count", remainingCount);
      OBJECT_SERIALIZE_FIELD(json, "personal_total_count", personalTotalCount);
      OBJECT_SERIALIZE_FIELD(json, "personal_remaining_count", personalRemainingCount);
      OBJECT_SERIALIZE_FIELD_PTR(json, "background", background);
      OBJECT_SERIALIZE_FIELD(json, "unique_gift_variant_count", uniqueGiftVariantCount);
      OBJECT_SERIALIZE_FIELD_PTR(json, "publisher_chat", publisherChat);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sticker", sticker, false);
      OBJECT_DESERIALIZE_FIELD(json, "star_count", starCount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "upgrade_star_count", upgradeStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_premium", isPremium, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_colors", hasColors, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "total_count", totalCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "remaining_count", remainingCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "personal_total_count", personalTotalCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "personal_remaining_count", personalRemainingCount, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "background", background, true);
      OBJECT_DESERIALIZE_FIELD(json, "unique_gift_variant_count", uniqueGiftVariantCount, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "publisher_chat", publisherChat, true);
    }
  };
}