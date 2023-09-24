#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a file ready to be downloaded.
    ///
    /// The file can be downloaded via the link https://api.telegram.org/file/bot<token>/<file_path>.
    /// It is guaranteed that the link will be valid for at least 1 hour.
    /// When the link expires, a new one can be requested by calling getFile.
    ///
    /// @note The maximum file size to download is 20 MB
    /// @ref https://core.telegram.org/bots/api#file
    struct File {
        explicit File(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Identifier for this file, which can be used to download or reuse the file
        std::string fileId;

        /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
        /// Can't be used to download or reuse the file.
        std::string fileUniqueId;

        /// @brief Optional. File size in bytes.
        /// It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
        /// But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
        std::int64_t fileSize;

        /// @brief Optional. File path. Use https://api.telegram.org/file/bot<token>/<file_path> to get the file.
        std::string filePath;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
          OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
          OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
          OBJECT_SERIALIZE_FIELD(json, "file_path", filePath);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, true);
          OBJECT_DESERIALIZE_FIELD(json, "file_path", filePath, "", true);
        }
    };
}