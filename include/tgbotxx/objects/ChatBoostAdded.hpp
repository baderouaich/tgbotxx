#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about a user boosting a chat.
  /// @ref https://core.telegram.org/bots/api#chatboostadded
  struct ChatBoostAdded {
    ChatBoostAdded() = default;
    explicit ChatBoostAdded(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Number of boosts added by the user
    std::int32_t boostCount{};

    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "boost_count", boostCount);
      return json;
    }

    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "boost_count", boostCount, 0, false);
    }
  };

}
