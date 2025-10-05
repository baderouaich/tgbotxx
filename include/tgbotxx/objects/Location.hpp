#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a point on the map.
  /// @ref https://core.telegram.org/bots/api#location
  struct Location {
    Location() = default;
    explicit Location(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Latitude as defined by sender
    float latitude{};

    /// @brief Longitude as defined by sender
    float longitude{};

    /// @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500
    float horizontalAccuracy{};

    /// @brief Optional. Time relative to the message sending date, during which the location can be updated, in seconds.
    /// For active live locations only.
    std::int32_t livePeriod{};

    /// @brief Optional. The direction in which user is moving, in degrees; 1-360.
    /// For active live locations only.
    std::int32_t heading{};


    /// @brief Optional. Maximum distance for proximity alerts about approaching another chat member, in meters.
    /// For sent live locations only.
    std::int32_t proximityAlertRadius{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
      OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
      OBJECT_SERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy);
      OBJECT_SERIALIZE_FIELD(json, "live_period", livePeriod);
      OBJECT_SERIALIZE_FIELD(json, "heading", heading);
      OBJECT_SERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy, 0.0f, true);
      OBJECT_DESERIALIZE_FIELD(json, "live_period", livePeriod, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "heading", heading, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius, 0, true);
    }
  };
}