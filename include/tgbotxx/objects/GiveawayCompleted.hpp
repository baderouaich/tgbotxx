#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about the completion of a giveaway without public winners.
  /// @ref https://core.telegram.org/bots/api#giveawaycompleted
  struct GiveawayCompleted {
    GiveawayCompleted() = default;
    explicit GiveawayCompleted(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Number of winners in the giveaway
    std::int32_t winnerCount{};

    /// @brief Optional. Number of undistributed prizes
    std::int32_t unclaimedPrizeCount{};

    /// @brief Optional. Message with the giveaway that was completed
    Ptr<Message> giveawayMessage;

    /// @brief Optional. True, if the giveaway is a Telegram Star giveaway
    bool isStarGiveaway{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "winner_count", winnerCount);
      OBJECT_SERIALIZE_FIELD(json, "unclaimed_prize_count", unclaimedPrizeCount);
      OBJECT_SERIALIZE_FIELD_PTR(json, "giveaway_message", giveawayMessage);
      OBJECT_SERIALIZE_FIELD(json, "is_star_giveaway", isStarGiveaway);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "winner_count", winnerCount, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "unclaimed_prize_count", unclaimedPrizeCount, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "giveaway_message", giveawayMessage, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_star_giveaway", isStarGiveaway, false, true);
    }
  };

}
