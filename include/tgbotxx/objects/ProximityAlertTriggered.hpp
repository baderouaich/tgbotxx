#pragma once
#include "nlohmann/json_fwd.hpp"
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
    /// @brief This object represents the content of a service message, sent whenever a user in the chat triggers a proximity alert set by another user.
    /// @ref https://core.telegram.org/bots/api#proximityalerttriggered
    struct ProximityAlertTriggered {
        explicit ProximityAlertTriggered(const nl::json& json) {
          fromJson(json);
        }

        /// @brief User that triggered the alert
        Ptr<User> traveler;

        /// @brief User that set the alert
        Ptr<User> watcher;

        /// @brief The distance between the users
        std::int32_t distance;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD_PTR(json, "traveler", traveler, nl::json::object());
          OBJECT_SERIALIZE_FIELD_PTR(json, "watcher", watcher, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "distance", distance);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD_PTR(json, "traveler", traveler, false);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "watcher", watcher, false);
          OBJECT_DESERIALIZE_FIELD(json, "distance", distance, 0, false);
        }
    };
}