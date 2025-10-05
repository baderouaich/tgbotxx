#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Location.hpp>

namespace tgbotxx {
  /// @brief Contains information about the location of a Telegram Business account.
  /// @ref https://core.telegram.org/bots/api#businesslocation
  struct BusinessLocation {
    BusinessLocation() = default;
    explicit BusinessLocation(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Address of the business
    std::string address;

    /// @brief Optional. Location of the business
    Ptr<Location> location;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "address", address);
      OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "address", address, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
    }
  };
}