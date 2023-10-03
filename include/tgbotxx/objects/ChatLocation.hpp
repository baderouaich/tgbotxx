#pragma once
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Represents a location to which a chat is connected.
  /// @ref https://core.telegram.org/bots/api#chatlocation
  struct ChatLocation {
      ChatLocation() = default;
      explicit ChatLocation(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The location to which the supergroup is connected. Can't be a live location.
      Ptr<Location> location;

      /// @brief Location address; 1-64 characters, as defined by the chat owner
      std::string address;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "location", location, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "address", address);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, false);
        OBJECT_DESERIALIZE_FIELD(json, "address", address, "", false);
      }
  };
}