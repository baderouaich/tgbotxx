#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief This object describes the types of gifts that can be gifted to a user or a chat.
  /// @ref https://core.telegram.org/bots/api#acceptedgifttypes
  struct AcceptedGiftTypes {
    AcceptedGiftTypes() = default;
    explicit AcceptedGiftTypes(const nl::json& json) {
      fromJson(json);
    }

    /// @brief True, if unlimited regular gifts are accepted
    bool unlimitedGifts{};

    /// @brief True, if limited regular gifts are accepted
    bool limitedGifts{};

    /// @brief True, if unique gifts or gifts that can be upgraded to unique for free are accepted
    bool uniqueGifts{};

    /// @brief True, if a Telegram Premium subscription is accepted
    bool premiumSubscription{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "unlimited_gifts", unlimitedGifts);
      OBJECT_SERIALIZE_FIELD(json, "limited_gifts", limitedGifts);
      OBJECT_SERIALIZE_FIELD(json, "unique_gifts", uniqueGifts);
      OBJECT_SERIALIZE_FIELD(json, "premium_subscription", premiumSubscription);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "unlimited_gifts", unlimitedGifts, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "limited_gifts", limitedGifts, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "unique_gifts", uniqueGifts, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "premium_subscription", premiumSubscription, false, false);
    }
  };

}
