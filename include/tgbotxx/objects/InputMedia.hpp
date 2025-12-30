#pragma once
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents the content of a media message to be sent. It should be one of:
  /// - InputMediaAnimation
  /// - InputMediaDocument
  /// - InputMediaAudio
  /// - InputMediaPhoto
  /// - InputMediaVideo
  /// @ref https://core.telegram.org/bots/api#inputmedia
  struct InputMedia {
    InputMedia() = default;
    explicit InputMedia(const nl::json& json) {
      InputMedia::fromJson(json);
    }
    virtual ~InputMedia() = default;

    /// @brief Type of the result.
    std::string type;

    /// @brief File to send.
    /// - Pass a file_id std::string to send a file that exists on the Telegram servers (recommended),
    /// - Pass an HTTP URL std::string for Telegram to get a file from the Internet, or
    /// - Pass a cpr::File to upload a local file
    /// The latter will internally use “attach://<file_attach_name>” with multipart/form-data under <file_attach_name> name to upload the local file.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::variant<std::monostate, cpr::File, std::string> media{};

    /// @brief Optional. Caption of the media to be sent, 0-1024 characters after entities parsing
    std::string caption;

    /// @brief Optional. Mode for parsing entities in the media caption.
    /// See https://core.telegram.org/bots/api#formatting-options for more details.
    std::string parseMode;

    /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
    std::vector<Ptr<MessageEntity>> captionEntities;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
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
      OBJECT_SERIALIZE_FIELD(json, "caption", caption);
      OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      // media variant, we can't get a local file from remote, so it's always a URL or file id std::string.
      OBJECT_DESERIALIZE_FIELD(json, "media", std::get<std::string>(media), "", false);
      OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
    }
  };

  /// @brief Represents an animation file (GIF or H.264/MPEG-4 AVC video without sound) to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediaanimation
  struct InputMediaAnimation : InputMedia {
    InputMediaAnimation() {
      type = "animation";
    }
    explicit InputMediaAnimation(const nl::json& json) {
      InputMediaAnimation::fromJson(json);
    }

    /// @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
    /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    /// Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::string thumbnail;

    /// @brief Optional. Animation width
    std::int32_t width{};

    /// @brief Optional. Animation height
    std::int32_t height{};

    /// @brief Optional. Animation duration in seconds
    std::int32_t duration{};

    /// @brief Optional. Pass True if the animation needs to be covered with a spoiler animation
    bool hasSpoiler{};


    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      OBJECT_SERIALIZE_FIELD(json, "has_spoiler", hasSpoiler);
      return json;
    }
    void fromJson(const nl::json& json) override {
      InputMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "thumbnail", thumbnail, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_spoiler", hasSpoiler, false, true);
    }
  };


  /// @brief Represents a general file to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediadocument
  struct InputMediaDocument : InputMedia {
    InputMediaDocument() {
      type = "document";
    }
    explicit InputMediaDocument(const nl::json& json) {
      InputMediaDocument::fromJson(json);
    }

    /// @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
    /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    /// Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::string thumbnail;

    /// @brief Optional. Disables automatic server-side content type detection for files uploaded using multipart/form-data.
    /// Always True, if the document is sent as part of an album.
    bool disableContentTypeDetection{};


    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "disable_content_type_detection", disableContentTypeDetection);
      return json;
    }
    void fromJson(const nl::json& json) override {
      InputMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "thumbnail", thumbnail, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "disable_content_type_detection", disableContentTypeDetection, false, true);
    }
  };


  /// @brief Represents an audio file to be treated as music to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediaaudio
  struct InputMediaAudio : InputMedia {
    InputMediaAudio() {
      type = "audio";
    }
    explicit InputMediaAudio(const nl::json& json) {
      InputMediaAudio::fromJson(json);
    }

    /// @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
    /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    /// Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::string thumbnail;

    /// @brief Optional. Duration of the audio in seconds
    std::int32_t duration{};

    /// @brief Optional. Performer of the audio
    std::string performer;

    /// @brief Optional. Title of the audio
    std::string title;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      OBJECT_SERIALIZE_FIELD(json, "performer", performer);
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      return json;
    }
    void fromJson(const nl::json& json) override {
      InputMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "thumbnail", thumbnail, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "performer", performer, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
    }
  };


  /// @brief Represents a photo to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediaphoto
  struct InputMediaPhoto : InputMedia {
    InputMediaPhoto() {
      type = "photo";
    }
    explicit InputMediaPhoto(const nl::json& json) {
      InputMediaPhoto::fromJson(json);
    }

    /// @brief Optional. Pass True if the photo needs to be covered with a spoiler animation
    bool hasSpoiler{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "has_spoiler", hasSpoiler);
      return json;
    }
    void fromJson(const nl::json& json) override {
      InputMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "has_spoiler", hasSpoiler, false, true);
    }
  };


  /// @brief Represents a video to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediavideo
  struct InputMediaVideo : InputMedia {
    InputMediaVideo() {
      type = "video";
    }
    explicit InputMediaVideo(const nl::json& json) {
      InputMediaVideo::fromJson(json);
    }

    /// @brief Optional. Thumbnail of the file sent; can be ignored if thumbnail generation for the file is supported server-side.
    /// The thumbnail should be in JPEG format and less than 200 kB in size. A thumbnail's width and height should not exceed 320.
    /// Ignored if the file is not uploaded using multipart/form-data. Thumbnails can't be reused and can be only uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the thumbnail was uploaded using multipart/form-data under <file_attach_name>.
    /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
    std::string thumbnail;

    /// @brief Optional. Video width
    std::int32_t width{};

    /// @brief Optional. Video height
    std::int32_t height{};

    /// @brief Optional. Video duration in seconds
    std::int32_t duration{};

    /// @brief Optional. Pass True if the uploaded video is suitable for streaming
    bool supportsStreaming{};

    /// @brief Optional. Pass True if the animation needs to be covered with a spoiler animation
    bool hasSpoiler{};


    [[nodiscard]] nl::json toJson() const override {
      nl::json json = InputMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      OBJECT_SERIALIZE_FIELD(json, "supports_streaming", supportsStreaming);
      OBJECT_SERIALIZE_FIELD(json, "has_spoiler", hasSpoiler);
      return json;
    }
    void fromJson(const nl::json& json) override {
      InputMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "thumbnail", thumbnail, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "supports_streaming", supportsStreaming, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_spoiler", hasSpoiler, false, true);
    }
  };

}