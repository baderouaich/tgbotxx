#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/BusinessOpeningHoursInterval.hpp>

namespace tgbotxx {
  /// @brief Describes the opening hours of a business.
  /// @ref https://core.telegram.org/bots/api#businessopeninghours
  struct BusinessOpeningHours {
    BusinessOpeningHours() = default;
    explicit BusinessOpeningHours(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique name of the time zone for which the opening hours are defined
    std::string timeZoneName;

    /// @brief List of time intervals describing business opening hours
    std::vector<Ptr<BusinessOpeningHoursInterval>> openingHours;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "time_zone_name", timeZoneName);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "opening_hours", openingHours);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "time_zone_name", timeZoneName, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "opening_hours", openingHours, false);
    }
  };
}