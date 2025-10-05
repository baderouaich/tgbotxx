#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents a message about the completion of a giveaway with public winners.
  /// @ref https://core.telegram.org/bots/api#giveawaywinners
  struct GiveawayWinners {
    GiveawayWinners() = default;
    explicit GiveawayWinners(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The chat that created the giveaway
    Ptr<Chat> chat;

    /// @brief Identifier of the message with the giveaway in the chat
    std::int32_t giveawayMessageId{};

    /// @brief Point in time (Unix timestamp) when winners of the giveaway were selected
    std::time_t winnersSelectionDate{};

    /// @brief Total number of winners in the giveaway
    std::int32_t winnerCount{};

    /// @brief List of up to 100 winners of the giveaway
    std::vector<Ptr<User>> winners;

    /// @brief Optional. The number of other chats the user had to join in order to be eligible for the giveaway
    std::int32_t additionalChatCount{};

    /// @brief Optional. The number of Telegram Stars that were split between giveaway winners; for Telegram Star giveaways only
    std::int64_t prizeStarCount{};

    /// @brief Optional. The number of months the Telegram Premium subscription won from the giveaway will be active for; for Telegram Premium giveaways only
    std::int32_t premiumSubscriptionMonthCount{};

    /// @brief Optional. Number of undistributed prizes
    std::int32_t unclaimedPrizeCount{};

    /// @brief Optional. True, if only users who had joined the chats after the giveaway started were eligible to win
    bool onlyNewMembers{};

    /// @brief Optional. True, if the giveaway was canceled because the payment for it was refunded
    bool wasRefunded{};

    /// @brief Optional. Description of additional giveaway prize
    std::string prizeDescription{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "giveaway_message_id", giveawayMessageId);
      OBJECT_SERIALIZE_FIELD(json, "winners_selection_date", winnersSelectionDate);
      OBJECT_SERIALIZE_FIELD(json, "winner_count", winnerCount);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "winners", winners);
      OBJECT_SERIALIZE_FIELD(json, "additional_chat_count", additionalChatCount);
      OBJECT_SERIALIZE_FIELD(json, "prize_star_count", prizeStarCount);
      OBJECT_SERIALIZE_FIELD(json, "premium_subscription_month_count", premiumSubscriptionMonthCount);
      OBJECT_SERIALIZE_FIELD(json, "unclaimed_prize_count", unclaimedPrizeCount);
      OBJECT_SERIALIZE_FIELD(json, "only_new_members", onlyNewMembers);
      OBJECT_SERIALIZE_FIELD(json, "was_refunded", wasRefunded);
      OBJECT_SERIALIZE_FIELD(json, "prize_description", prizeDescription);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD(json, "giveaway_message_id", giveawayMessageId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "winners_selection_date", winnersSelectionDate, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "winner_count", winnerCount, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "winners", winners, false);
      OBJECT_DESERIALIZE_FIELD(json, "additional_chat_count", additionalChatCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "prize_star_count", prizeStarCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "premium_subscription_month_count", premiumSubscriptionMonthCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "unclaimed_prize_count", unclaimedPrizeCount, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "only_new_members", onlyNewMembers, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "was_refunded", wasRefunded, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "prize_description", prizeDescription, "", true);
    }
  };
}