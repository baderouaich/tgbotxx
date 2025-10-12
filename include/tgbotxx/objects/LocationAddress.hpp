#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <string>

namespace tgbotxx {

  /// @brief Describes the physical address of a location.
  /// @ref https://core.telegram.org/bots/api#locationaddress
  struct LocationAddress {
    LocationAddress() = default;
    explicit LocationAddress(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The two-letter ISO 3166-1 alpha-2 country code of the country where the location is located
    std::string countryCode;

    /// @brief Optional. State of the location
    std::string state;

    /// @brief Optional. City of the location
    std::string city;

    /// @brief Optional. Street address of the location
    std::string street;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "country_code", countryCode);
      OBJECT_SERIALIZE_FIELD(json, "state", state);
      OBJECT_SERIALIZE_FIELD(json, "city", city);
      OBJECT_SERIALIZE_FIELD(json, "street", street);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "country_code", countryCode, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "state", state, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "city", city, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "street", street, "", true);
    }
  };

}
