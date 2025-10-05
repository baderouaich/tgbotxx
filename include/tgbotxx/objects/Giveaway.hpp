#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief This object represents a message about a scheduled giveaway.
  /// @ref https://core.telegram.org/bots/api#giveaway
  struct Giveaway {
    Giveaway() = default;
    explicit Giveaway(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The list of chats which the user must join to participate in the giveaway
    std::vector<Ptr<Chat>> chats;

    /// @brief Point in time (Unix timestamp) when winners of the giveaway will be selected
    std::time_t winnersSelectionDate{};

    /// @brief The number of users which are supposed to be selected as winners of the giveaway
    std::int32_t winnerCount{};

    /// @brief Optional. True, if only users who join the chats after the giveaway started should be eligible to win
    bool onlyNewMembers{};

    /// @brief Optional. True, if the list of giveaway winners will be visible to everyone
    bool hasPublicWinners{};

    /// @brief Optional. Description of additional giveaway prize
    std::string prizeDescription;

    /// @brief Optional. A list of two-letter ISO 3166-1 alpha-2 country codes indicating the countries from which
    /// eligible users for the giveaway must come. If empty, then all users can participate in the giveaway.
    /// Users with a phone number that was bought on Fragment can always participate in giveaways.
    /// @link ISO 3166-1 alpha-2: https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2 @endlink
    std::vector<std::string> countryCodes;

    /// @brief Optional. The number of Telegram Stars to be split between giveaway winners; for Telegram Star giveaways only
    std::int64_t prizeStarCount{};

    /// @brief Optional. The number of months the Telegram Premium subscription won from the giveaway will be active for; for Telegram Premium giveaways only
    std::int32_t premiumSubscriptionMonthCount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "chats", chats);
      OBJECT_SERIALIZE_FIELD(json, "winners_selection_date", winnersSelectionDate);
      OBJECT_SERIALIZE_FIELD(json, "winner_count", winnerCount);
      OBJECT_SERIALIZE_FIELD(json, "only_new_members", onlyNewMembers);
      OBJECT_SERIALIZE_FIELD(json, "has_public_winners", hasPublicWinners);
      OBJECT_SERIALIZE_FIELD(json, "prize_description", prizeDescription);
      OBJECT_SERIALIZE_FIELD(json, "country_codes", countryCodes);
      OBJECT_SERIALIZE_FIELD(json, "prize_star_count", prizeStarCount);
      OBJECT_SERIALIZE_FIELD(json, "premium_subscription_month_count", premiumSubscriptionMonthCount);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "chats", chats, false);
      OBJECT_DESERIALIZE_FIELD(json, "winners_selection_date", winnersSelectionDate, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "winner_count", winnerCount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "only_new_members", onlyNewMembers, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_public_winners", hasPublicWinners, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "prize_description", prizeDescription, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "country_codes", countryCodes, {}, true);
      OBJECT_DESERIALIZE_FIELD(json, "prize_star_count", prizeStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "premium_subscription_month_count", premiumSubscriptionMonthCount, 0, true);
    }
  };
}