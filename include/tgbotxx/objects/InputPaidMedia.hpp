#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <variant>
#include <cpr/file.h>

namespace tgbotxx {

  /// @brief Base class describing paid media to send
  /// @ref https://core.telegram.org/bots/api#inputpaidmedia
  struct InputPaidMedia {
    InputPaidMedia() = default;
    explicit InputPaidMedia(const nl::json& json) {
      InputPaidMedia::fromJson(json);
    }
    virtual ~InputPaidMedia() = default;

    /// @brief Type of the media
    std::string type;

    /// @brief File to send.
    /// - Pass a file_id std::string to send a file that exists on the Telegram servers (recommended),
    /// - Pass an HTTP URL std::string for Telegram to get a file from the Internet, or
    /// - Pass a cpr::File to upload a local file
    /// The latter will internally use “attach://<file_attach_name>” with multipart/form-data under <file_attach_name> name to upload the local file.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::variant<std::monostate, cpr::File, std::string> media{};

    /// @brief Serializes this object to JSON
    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      if (not std::holds_alternative<std::monostate>(media)) {
        // media variant
        if (std::holds_alternative<cpr::File>(media))
          json["media"] = std::get<cpr::File>(media).filepath;
        else
          json["media"] = std::get<std::string>(media);
      }
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      // media variant, we can't get a local file from remote, so it's always a URL or file id std::string.
      OBJECT_DESERIALIZE_FIELD(json, "media", std::get<std::string>(media), "", false);
    }
  };

  /// @brief The paid media to send is a photo
  struct InputPaidMediaPhoto : InputPaidMedia {
    InputPaidMediaPhoto() {
      type = "photo";
    }
    explicit InputPaidMediaPhoto(const nl::json& json) {
      InputPaidMediaPhoto::fromJson(json);
    }

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputPaidMedia::toJson();
      return json;
    }

    void fromJson(const nl::json& json) override {
      InputPaidMedia::fromJson(json);
    }
  };

  /// @brief The paid media to send is a video
  struct InputPaidMediaVideo : InputPaidMedia {
    InputPaidMediaVideo() {
      type = "video";
    }
    explicit InputPaidMediaVideo(const nl::json& json) {
      InputPaidMediaVideo::fromJson(json);
    }

    /// @brief Optional. Thumbnail of the file sent
    std::string thumbnail;

    /// @brief Optional. Cover for the video in the message
    std::string cover;

    /// @brief Optional. Start timestamp for the video
    std::time_t startTimestamp{};

    /// @brief Optional. Video width
    std::int32_t width{};

    /// @brief Optional. Video height
    std::int32_t height{};

    /// @brief Optional. Video duration in seconds
    std::time_t duration{};

    /// @brief Optional. True if the uploaded video is suitable for streaming
    bool supportsStreaming{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputPaidMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "cover", cover);
      OBJECT_SERIALIZE_FIELD(json, "start_timestamp", startTimestamp);
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      OBJECT_SERIALIZE_FIELD(json, "supports_streaming", supportsStreaming);
      return json;
    }

    void fromJson(const nl::json& json) override {
      InputPaidMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "thumbnail", thumbnail, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "cover", cover, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "start_timestamp", startTimestamp, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "supports_streaming", supportsStreaming, false, true);
    }
  };

}
