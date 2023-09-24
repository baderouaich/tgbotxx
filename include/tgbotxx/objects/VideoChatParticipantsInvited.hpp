#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
    /// @brief This object represents a service message about new members invited to a video chat.
    /// @ref https://core.telegram.org/bots/api#videochatparticipantsinvited
    struct VideoChatParticipantsInvited {
        explicit VideoChatParticipantsInvited(const nl::json& json) {
          fromJson(json);
        }

        /// @brief New members that were invited to the video chat
        std::vector<Ptr<User>> users;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "users", users);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "users", users, false);
        }
    };
}