#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a voice note.
    /// @ref https://core.telegram.org/bots/api#voice
    struct Voice {
        explicit Voice(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Identifier for this file, which can be used to download or reuse the file
        std::string fileId;

        /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
        /// Can't be used to download or reuse the file.
        std::string fileUniqueId;

        /// @brief Duration of the audio in seconds as defined by sender
        std::int32_t duration;

        /// @brief Optional. MIME type of the file as defined by sender
        std::string mimeType;

        /// @brief Optional. File size in bytes.
        /// It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
        /// But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
        std::int64_t fileSize;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
          OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
          OBJECT_SERIALIZE_FIELD(json, "duration", duration);
          OBJECT_SERIALIZE_FIELD(json, "mime_type", mimeType);
          OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "mime_type", mimeType, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, true);
        }
    };
}