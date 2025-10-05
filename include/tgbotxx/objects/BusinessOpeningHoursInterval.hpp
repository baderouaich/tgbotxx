#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes an interval of time during which a business is open.
  /// @ref https://core.telegram.org/bots/api#businessopeninghoursinterval
  struct BusinessOpeningHoursInterval {
    BusinessOpeningHoursInterval() = default;
    explicit BusinessOpeningHoursInterval(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The minute's sequence number in a week, starting on Monday, marking the start of the time interval during which the business is open; 0 - 7 * 24 * 60
    std::int32_t openingMinute{};

    /// @brief The minute's sequence number in a week, starting on Monday, marking the end of the time interval during which the business is open; 0 - 8 * 24 * 60
    std::int32_t closingMinute{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "opening_minute", openingMinute);
      OBJECT_SERIALIZE_FIELD(json, "closing_minute", closingMinute);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "opening_minute", openingMinute, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "closing_minute", closingMinute, 0, false);
    }
  };
}