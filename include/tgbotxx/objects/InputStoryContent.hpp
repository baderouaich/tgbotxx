#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief Base class for story content to post
  /// @ref https://core.telegram.org/bots/api#inputstorycontentphoto
  struct InputStoryContent {
    InputStoryContent() = default;
    explicit InputStoryContent(const nl::json& json) {
      InputStoryContent::fromJson(json);
    }
    virtual ~InputStoryContent() = default;

    /// @brief Type of the story content
    std::string type;

    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief Describes a photo to post as a story
  /// @ref https://core.telegram.org/bots/api#inputstorycontentphoto
  struct InputStoryContentPhoto : InputStoryContent {
    InputStoryContentPhoto() {
      type = "photo";
    }
    explicit InputStoryContentPhoto(const nl::json& json) {
      InputStoryContentPhoto::fromJson(json);
    }

    /// @brief The photo to post as a story. Must be 1080x1920 and <= 10MB. Can't be reused.
    std::string photo;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputStoryContent::toJson();
      OBJECT_SERIALIZE_FIELD(json, "photo", photo);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      InputStoryContent::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "photo", photo, "", false);
    }
  };

  /// @brief Describes a video to post as a story
  /// @ref https://core.telegram.org/bots/api#inputstorycontentvideo
  struct InputStoryContentVideo : InputStoryContent {
    InputStoryContentVideo() {
      type = "video";
    }
    explicit InputStoryContentVideo(const nl::json& json) {
      InputStoryContentVideo::fromJson(json);
    }

    /// @brief The video to post as a story. Must be 720x1280, H.265, streamable, <= 30MB. Can't be reused.
    std::string video;

    /// @brief Optional. Precise duration of the video in seconds; 0-60
    double duration{0.0};

    /// @brief Optional. Timestamp in seconds of the frame that will be used as the static cover for the story. Defaults to 0.0
    double coverFrameTimestamp{0.0};

    /// @brief Optional. True if the video has no sound
    bool isAnimation{false};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputStoryContent::toJson();
      OBJECT_SERIALIZE_FIELD(json, "video", video);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      OBJECT_SERIALIZE_FIELD(json, "cover_frame_timestamp", coverFrameTimestamp);
      OBJECT_SERIALIZE_FIELD(json, "is_animation", isAnimation);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      InputStoryContent::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "video", video, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0.0, true);
      OBJECT_DESERIALIZE_FIELD(json, "cover_frame_timestamp", coverFrameTimestamp, 0.0, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_animation", isAnimation, false, true);
    }
  };

}
