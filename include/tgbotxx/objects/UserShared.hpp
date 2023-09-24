#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object contains information about the user whose identifier was shared with the bot using a KeyboardButtonRequestUser button.
    /// @ref https://core.telegram.org/bots/api#usershared
    struct UserShared {
        explicit UserShared(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Identifier of the request
        std::int32_t requestId;

        /// @brief Identifier of the shared user.
        /// This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects
        /// in interpreting it. But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are
        /// safe for storing this identifier. The bot may not have access to the user and could be unable to use this identifier,
        /// unless the user is already known to the bot by some other means.
        std::int64_t userId;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "request_id", requestId);
          OBJECT_SERIALIZE_FIELD(json, "user_id", userId);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "request_id", requestId, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "user_id", userId, 0, false);
        }
    };
}