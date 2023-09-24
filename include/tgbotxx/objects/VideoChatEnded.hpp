#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a service message about a video chat ended in the chat.
    /// @ref https://core.telegram.org/bots/api#videochatended
    struct VideoChatEnded {
        explicit VideoChatEnded(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Video chat duration in seconds
        std::int32_t duration;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "duration", duration);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, false);
        }
    };
}