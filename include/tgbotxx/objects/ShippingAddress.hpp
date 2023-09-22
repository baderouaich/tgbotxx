#pragma once

#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <nlohmann/json.hpp>

namespace nl = nlohmann;

namespace tgbotxx {
    /// @brief This object represents a shipping address.
    /// @ref https://core.telegram.org/bots/api#shippingaddress
    struct ShippingAddress {
        explicit ShippingAddress(const nl::json &json) {
          fromJson(json);
        }

        /// @brief Two-letter ISO 3166-1 alpha-2 country code
        std::string countryCode;

        /// @brief State, if applicable
        std::string state;

        /// @brief City
        std::string city;

        /// @brief First line for the address
        std::string streetLine1;

        /// @brief Second line for the address
        std::string streetLine2;

        /// @brief Address post code
        std::string postCode;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "country_code", countryCode);
          OBJECT_SERIALIZE_FIELD(json, "state", state);
          OBJECT_SERIALIZE_FIELD(json, "city", city);
          OBJECT_SERIALIZE_FIELD(json, "street_line1", streetLine1);
          OBJECT_SERIALIZE_FIELD(json, "street_line2", streetLine2);
          OBJECT_SERIALIZE_FIELD(json, "post_code", postCode);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "country_code", countryCode, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "state", state, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "city", city, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "street_line1", streetLine1, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "street_line2", streetLine2, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "post_code", postCode, "", false);
        }
    };
}
