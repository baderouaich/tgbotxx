#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents one size of a photo or a file / sticker thumbnail.
  /// @ref https://core.telegram.org/bots/api#photosize
  struct PhotoSize {
      PhotoSize() = default;
      explicit PhotoSize(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Identifier for this file, which can be used to download or reuse the file
      std::string fileId;

      /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
      /// Can't be used to download or reuse the file.
      std::string fileUniqueId;

      /// @brief Photo width
      std::int32_t width{};

      /// @brief Photo height
      std::int32_t height{};

      /// @brief Optional. File size in bytes
      std::int64_t fileSize{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
        OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
        OBJECT_SERIALIZE_FIELD(json, "width", width);
        OBJECT_SERIALIZE_FIELD(json, "height", height);
        OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, true);
      }
  };
}