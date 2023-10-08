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
        _fromJson(json);
      }

      /// @brief Type of the result.
      std::string type;

      /// @brief File to send. Pass a file_id to send a file that exists on the Telegram servers (recommended),
      /// Pass an HTTP URL for Telegram to get a file from the Internet, or
      /// Pass “attach://<file_attach_name>” to upload a new one using multipart/form-data under <file_attach_name> name.
      /// More information on Sending Files » https://core.telegram.org/bots/api#sending-files
      std::string media;

      /// @brief Optional. Caption of the media to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the media caption.
      /// See https://core.telegram.org/bots/api#formatting-options for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      virtual nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        OBJECT_SERIALIZE_FIELD(json, "media", media);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        return json;
      }

      /// @brief Deserializes this object from JSON
      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "media", media, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
      }

    private:
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };

  /// @brief Represents an animation file (GIF or H.264/MPEG-4 AVC video without sound) to be sent.
  /// @ref https://core.telegram.org/bots/api#inputmediaanimation
  struct InputMediaAnimation : InputMedia {
      InputMediaAnimation() {
        InputMedia::type = "animation";
      }
      explicit InputMediaAnimation(const nl::json& json) {
        InputMedia::fromJson(json);
        InputMedia::type = "animation";
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


      nl::json toJson() const override {
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
        InputMedia::type = "document";
      }
      explicit InputMediaDocument(const nl::json& json) : InputMedia(json) {
        InputMedia::type = "document";
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


      nl::json toJson() const override {
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
        InputMedia::type = "audio";
      }
      explicit InputMediaAudio(const nl::json& json) : InputMedia(json) {
        InputMedia::type = "audio";
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

      nl::json toJson() const override {
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
        InputMedia::type = "photo";
      }
      explicit InputMediaPhoto(const nl::json& json) : InputMedia(json) {
        InputMedia::type = "photo";
      }

      /// @brief Optional. Pass True if the photo needs to be covered with a spoiler animation
      bool hasSpoiler{};

      nl::json toJson() const override {
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
        InputMedia::type = "video";
      }
      explicit InputMediaVideo(const nl::json& json) : InputMedia(json) {
        InputMedia::type = "video";
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


      nl::json toJson() const override {
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