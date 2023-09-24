#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a service message about a video chat scheduled in the chat.
    /// @ref https://core.telegram.org/bots/api#videochatscheduled
    struct VideoChatScheduled {
        explicit VideoChatScheduled(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Point in time (Unix timestamp) when the video chat is supposed to be started by a chat administrator
        std::time_t startDate;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "start_date", startDate);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "start_date", startDate, 0, false);
        }
    };
}