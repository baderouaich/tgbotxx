#pragma once
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a venue.
  /// @ref https://core.telegram.org/bots/api#venue
  struct Venue {
      Venue() = default;
      explicit Venue(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Venue location. Can't be a live location
      Ptr<Location> location;

      /// @brief Name of the venue
      std::string title;

      /// @brief Address of the venue
      std::string address;

      /// @brief Optional. Foursquare identifier of the venue
      std::string foursquareId;

      /// @brief Optional. Foursquare type of the venue.
      /// (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
      std::string foursquareType;

      /// @brief Optional. Google Places identifier of the venue
      std::string googlePlaceId;

      /// @brief Optional. Google Places type of the venue. (See supported types.) https://developers.google.com/places/web-service/supported_types
      std::string googlePlaceType;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "address", address);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_id", foursquareId);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_type", foursquareType);
        OBJECT_SERIALIZE_FIELD(json, "google_place_id", googlePlaceId);
        OBJECT_SERIALIZE_FIELD(json, "google_place_type", googlePlaceType);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "address", address, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_id", foursquareId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_type", foursquareType, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_id", googlePlaceId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_type", googlePlaceType, "", true);
      }
  };
}