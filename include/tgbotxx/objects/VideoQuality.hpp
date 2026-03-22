#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a video file of a specific quality.
  /// @ref https://core.telegram.org/bots/api#videoquality
  struct VideoQuality {
    VideoQuality() = default;
    explicit VideoQuality(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Identifier for this file, which can be used to download or reuse the file
    std::string fileId;

    /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
    /// Can't be used to download or reuse the file.
    std::string fileUniqueId;

    /// @brief Video width
    std::int32_t width{};

    /// @brief Video height
    std::int32_t height{};

    /// @brief Codec that was used to encode the video, for example, “h264”, “h265”, or “av01”
    std::string codec;

    /// @brief Optional. File size in bytes.
    /// It can be bigger than 2^31 and some programming languages may have difficulty/silent defects in interpreting it.
    /// But it has at most 52 significant bits, so a signed 64-bit integer or double-precision float type are safe for storing this value.
    std::int64_t fileSize{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
      OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "codec", codec);
      OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "codec", codec, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, true);
    }
  };
}