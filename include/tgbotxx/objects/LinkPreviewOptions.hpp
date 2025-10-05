#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes the options used for link preview generation.
  /// @ref https://core.telegram.org/bots/api#linkpreviewoptions
  struct LinkPreviewOptions {
    LinkPreviewOptions() = default;
    explicit LinkPreviewOptions(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. True, if the link preview is disabled
    bool isDisabled{};

    /// @brief Optional. URL to use for the link preview. If empty, then the first URL found in the message text will be used
    std::string url;

    /// @brief Optional. True, if the media in the link preview is supposed to be shrunk;
    /// ignored if the URL isn't explicitly specified or media size change isn't supported for the preview
    bool preferSmallMedia{};

    /// @brief Optional. True, if the media in the link preview is supposed to be enlarged;
    /// ignored if the URL isn't explicitly specified or media size change isn't supported for the preview
    bool preferLargeMedia{};

    /// @brief Optional. True, if the link preview must be shown above the message text;
    /// otherwise, the link preview will be shown below the message text
    bool showAboveText{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "is_disabled", isDisabled);
      OBJECT_SERIALIZE_FIELD(json, "url", url);
      OBJECT_SERIALIZE_FIELD(json, "prefer_small_media", preferSmallMedia);
      OBJECT_SERIALIZE_FIELD(json, "prefer_large_media", preferLargeMedia);
      OBJECT_SERIALIZE_FIELD(json, "show_above_text", showAboveText);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "is_disabled", isDisabled, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "url", url, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "prefer_small_media", preferSmallMedia, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "prefer_large_media", preferLargeMedia, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "show_above_text", showAboveText, false, true);
    }
  };
}