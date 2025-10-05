#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a change in the price of direct messages sent to a channel chat.
  /// @ref https://core.telegram.org/bots/api#directmessagepricechanged
  struct DirectMessagePriceChanged {
    DirectMessagePriceChanged() = default;
    explicit DirectMessagePriceChanged(const nl::json& json) {
      fromJson(json);
    }

    /// @brief True, if direct messages are enabled for the channel chat; false otherwise
    bool areDirectMessagesEnabled{};

    /// @brief Optional. The new number of Telegram Stars that must be paid by users for each direct message
    std::int64_t directMessageStarCount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "are_direct_messages_enabled", areDirectMessagesEnabled);
      OBJECT_SERIALIZE_FIELD(json, "direct_message_star_count", directMessageStarCount);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "are_direct_messages_enabled", areDirectMessagesEnabled, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "direct_message_star_count", directMessageStarCount, 0, true);
    }
  };
}
