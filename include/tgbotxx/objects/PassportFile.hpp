#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a file uploaded to Telegram Passport.
    /// Currently all Telegram Passport files are in JPEG format when decrypted and don't exceed 10MB.
    /// @ref https://core.telegram.org/bots/api#passportfile
    struct PassportFile {
        explicit PassportFile(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Identifier for this file, which can be used to download or reuse the file
        std::string fileId;

        /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
        /// Can't be used to download or reuse the file.
        std::string fileUniqueId;

        /// @brief File size in bytes
        std::int64_t fileSize;

        /// @brief Unix time when the file was uploaded
        std::time_t fileDate;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
          OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
          OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
          OBJECT_SERIALIZE_FIELD(json, "file_date", fileDate);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "file_date", fileDate, 0, false);
        }
    };
}