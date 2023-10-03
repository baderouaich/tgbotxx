#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a chat photo.
  /// @ref https://core.telegram.org/bots/api#chatphoto
  struct ChatPhoto {
      ChatPhoto() = default;
      explicit ChatPhoto(const nl::json& json) {
        fromJson(json);
      }

      /// @brief File identifier of small (160x160) chat photo. This file_id can be used only for photo download and only for as long as the photo is not changed.
      std::string smallFileId;

      /// @brief Unique file identifier of small (160x160) chat photo, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file.
      std::string smallFileUniqueId;

      /// @brief File identifier of big (640x640) chat photo. This file_id can be used only for photo download and only for as long as the photo is not changed.
      std::string bigFileId;

      /// @brief Unique file identifier of big (640x640) chat photo, which is supposed to be the same over time and for different bots. Can't be used to download or reuse the file.
      std::string bigFileUniqueId;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "small_file_id", smallFileId);
        OBJECT_SERIALIZE_FIELD(json, "small_file_unique_id", smallFileUniqueId);
        OBJECT_SERIALIZE_FIELD(json, "big_file_id", bigFileId);
        OBJECT_SERIALIZE_FIELD(json, "big_file_unique_id", bigFileUniqueId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "small_file_id", smallFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "small_file_unique_id", smallFileUniqueId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "big_file_id", bigFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "big_file_unique_id", bigFileUniqueId, "", false);
      }
  };
}