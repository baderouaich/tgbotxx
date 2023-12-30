#pragma once
#include <tgbotxx/objects/InlineKeyboardMarkup.hpp>
#include <tgbotxx/objects/InputMessageContent.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Base class of all inline query results
  /// This object represents one result of an inline query. Telegram clients currently support results of the following 20 types:
  /// - InlineQueryResultCachedAudio
  /// - InlineQueryResultCachedDocument
  /// - InlineQueryResultCachedGif
  /// - InlineQueryResultCachedMpeg4Gif
  /// - InlineQueryResultCachedPhoto
  /// - InlineQueryResultCachedSticker
  /// - InlineQueryResultCachedVideo
  /// - InlineQueryResultCachedVoice
  /// - InlineQueryResultArticle
  /// - InlineQueryResultAudio
  /// - InlineQueryResultContact
  /// - InlineQueryResultGame
  /// - InlineQueryResultDocument
  /// - InlineQueryResultGif
  /// - InlineQueryResultLocation
  /// - InlineQueryResultMpeg4Gif
  /// - InlineQueryResultPhoto
  /// - InlineQueryResultVenue
  /// - InlineQueryResultVideo
  /// - InlineQueryResultVoice
  /// @note All URLs passed in inline query results will be available to end users and therefore must be assumed to be public.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresult
  struct InlineQueryResult {
      InlineQueryResult() = default;
      explicit InlineQueryResult(const nl::json& json) {
        _fromJson(json);
      }

      /// @brief Type of the result
      std::string type;

      /// @brief Unique identifier for this result, 1-64 bytes
      std::string id;

      /// @brief Optional. Inline keyboard attached to the message
      Ptr<InlineKeyboardMarkup> replyMarkup;

      virtual nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        OBJECT_SERIALIZE_FIELD(json, "id", id);
        OBJECT_SERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup);
        return json;
      }

      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup, true);
      }

    private:
      void _fromJson(const nl::json& json) { // to avoid calling virtual method fromJson() from constructor
        fromJson(json);
      }
  };


  /// @brief Represents a link to an article or web page.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultarticle
  struct InlineQueryResultArticle : InlineQueryResult {
      InlineQueryResultArticle() {
        InlineQueryResult::type = "article";
      }
      explicit InlineQueryResultArticle(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "article";
      }

      /// @brief Title of the result
      std::string title;

      /// @brief Content of the message to be sent
      Ptr<InputMessageContent> inputMessageContent{};

      /// @brief Optional. URL of the result
      std::string url;

      /// @brief Optional. Pass True if you don't want the URL to be shown in the message
      bool hideUrl{};

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Url of the thumbnail for the result
      std::string thumbnailUrl;

      /// @brief Optional. Thumbnail width
      std::int32_t thumbnailWidth{};

      /// @brief Optional. Thumbnail height
      std::int32_t thumbnailHeight{};

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        OBJECT_SERIALIZE_FIELD(json, "url", url);
        OBJECT_SERIALIZE_FIELD(json, "hide_url", hideUrl);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, false);
        OBJECT_DESERIALIZE_FIELD(json, "url", url, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "hide_url", hideUrl, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight, 0, true);
      }
  };

  /// @brief Represents a link to a photo. By default, this photo will be sent by the user with optional caption.
  /// Alternatively, you can use input_message_content to send a message with the specified content instead of the photo.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultphoto
  struct InlineQueryResultPhoto : InlineQueryResult {
      InlineQueryResultPhoto() {
        InlineQueryResult::type = "photo";
      }
      explicit InlineQueryResultPhoto(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "photo";
      }

      /// @brief A valid URL of the photo. Photo must be in JPEG format. Photo size must not exceed 5MB
      std::string photoUrl;

      /// @brief URL of the thumbnail for the photo
      std::string thumbnailUrl;

      /// @brief Optional. Width of the photo
      std::int32_t photoWidth{};

      /// @brief Optional. Height of the photo
      std::int32_t photoHeight{};

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Caption of the photo to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the photo caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the photo
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "photo_url", photoUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "photo_width", photoWidth);
        OBJECT_SERIALIZE_FIELD(json, "photo_height", photoHeight);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "photo_url", photoUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "photo_width", photoWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "photo_height", photoHeight, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

  /// @brief Represents a link to an animated GIF file. By default, this animated GIF file will be sent by the user with optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the animation.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultgif
  struct InlineQueryResultGif : InlineQueryResult {
      InlineQueryResultGif() {
        InlineQueryResult::type = "gif";
      }
      explicit InlineQueryResultGif(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "gif";
      }

      /// @brief A valid URL for the GIF file. File size must not exceed 1MB
      std::string gifUrl;

      /// @brief Optional. Width of the GIF
      std::int32_t gifWidth{};

      /// @brief Optional. Height of the GIF
      std::int32_t gifHeight{};

      /// @brief Optional. Duration of the GIF in seconds
      std::int32_t gifDuration{};

      /// @brief URL of the static (JPEG or GIF) or animated (MPEG4) thumbnail for the result
      std::string thumbnailUrl;

      /// @brief Optional. MIME type of the thumbnail, must be one of “image/jpeg”, “image/gif”, or “video/mp4”. Defaults to “image/jpeg”
      std::string thumbnailMimeType;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Caption of the GIF file to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the GIF animation
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "gif_url", gifUrl);
        OBJECT_SERIALIZE_FIELD(json, "gif_width", gifWidth);
        OBJECT_SERIALIZE_FIELD(json, "gif_height", gifHeight);
        OBJECT_SERIALIZE_FIELD(json, "gif_duration", gifDuration);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_mime_type", thumbnailMimeType);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "gif_url", gifUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "gif_width", gifWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "gif_height", gifHeight, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "gif_duration", gifDuration, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_mime_type", thumbnailMimeType, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

  /// @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound).
  /// By default, this animated MPEG-4 file will be sent by the user with optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the animation.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultmpeg4gif
  struct InlineQueryResultMpeg4Gif : InlineQueryResult {
      InlineQueryResultMpeg4Gif() {
        InlineQueryResult::type = "mpeg4_gif";
      }
      explicit InlineQueryResultMpeg4Gif(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "mpeg4_gif";
      }

      /// @brief A valid URL for the MPEG4 file. File size must not exceed 1MB
      std::string mpeg4Url;

      /// @brief Optional. Video width
      std::int32_t mpeg4Width{};

      /// @brief Optional. Video height
      std::int32_t mpeg4Height{};

      /// @brief Optional. Video duration in seconds
      std::int32_t mpeg4Duration{};

      /// @brief URL of the static (JPEG or GIF) or animated (MPEG4) thumbnail for the result
      std::string thumbnailUrl;

      /// @brief Optional. MIME type of the thumbnail, must be one of “image/jpeg”, “image/gif”, or “video/mp4”. Defaults to “image/jpeg”
      std::string thumbnailMimeType;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the video animation
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "mpeg4_url", mpeg4Url);
        OBJECT_SERIALIZE_FIELD(json, "mpeg4_width", mpeg4Width);
        OBJECT_SERIALIZE_FIELD(json, "mpeg4_height", mpeg4Height);
        OBJECT_SERIALIZE_FIELD(json, "mpeg4_duration", mpeg4Duration);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_mime_type", thumbnailMimeType);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "mpeg4_url", mpeg4Url, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "mpeg4_width", mpeg4Width, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "mpeg4_height", mpeg4Height, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "mpeg4_duration", mpeg4Duration, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_mime_type", thumbnailMimeType, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to a page containing an embedded video player or a video file.
  /// By default, this video file will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the video.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultvideo
  /// @note If an InlineQueryResultVideo message contains an embedded video (e.g., YouTube), you must replace its content using inputMessageContent.
  struct InlineQueryResultVideo : InlineQueryResult {
      InlineQueryResultVideo() {
        InlineQueryResult::type = "video";
      }
      explicit InlineQueryResultVideo(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "video";
      }

      /// @brief A valid URL for the embedded video player or video file
      std::string videoUrl;

      /// @brief MIME type of the content of the video URL, “text/html” or “video/mp4”
      std::string mimeType;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief URL of the thumbnail (JPEG only) for the video
      std::string thumbnailUrl;

      /// @brief Optional. Caption of the video to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the video caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Video width
      std::int32_t videoWidth{};

      /// @brief Optional. Video height
      std::int32_t videoHeight{};

      /// @brief Optional. Video duration in seconds
      std::int32_t videoDuration{};

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Content of the message to be sent instead of the video.
      /// This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video).
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "video_url", videoUrl);
        OBJECT_SERIALIZE_FIELD(json, "mime_type", mimeType);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD(json, "video_width", videoWidth);
        OBJECT_SERIALIZE_FIELD(json, "video_height", videoHeight);
        OBJECT_SERIALIZE_FIELD(json, "video_duration", videoDuration);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "video_url", videoUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "mime_type", mimeType, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "video_width", videoWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "video_height", videoHeight, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "video_duration", videoDuration, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to an MP3 audio file.
  /// By default, this audio file will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the audio.
  struct InlineQueryResultAudio : InlineQueryResult {
      InlineQueryResultAudio() {
        InlineQueryResult::type = "audio";
      }
      explicit InlineQueryResultAudio(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "audio";
      }

      /// @brief A valid URL for the audio file
      std::string audioUrl;

      /// @brief Title
      std::string title;

      /// @brief Optional. Caption, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the audio caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Performer
      std::string performer;

      /// @brief Optional. Audio duration in seconds
      std::int32_t audioDuration{};

      /// @brief Optional. Content of the message to be sent instead of the video.
      /// This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video).
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "audio_url", audioUrl);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD(json, "performer", performer);
        OBJECT_SERIALIZE_FIELD(json, "audio_duration", audioDuration);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "audio_url", audioUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "performer", performer, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "audio_duration", audioDuration, 0, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to a voice recording in an .OGG container encoded with OPUS.
  /// By default, this voice recording will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the voice message.
  /// @note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them.
  struct InlineQueryResultVoice : InlineQueryResult {
      InlineQueryResultVoice() {
        InlineQueryResult::type = "voice";
      }
      explicit InlineQueryResultVoice(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "voice";
      }

      /// @brief A valid URL for the voice recording
      std::string voiceUrl;

      /// @brief Recording title
      std::string title;

      /// @brief Optional. Caption, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the voice caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Performer
      std::string performer;

      /// @brief Optional. Recording duration in seconds
      std::int32_t voiceDuration{};

      /// @brief Optional. Content of the message to be sent instead of the video.
      /// This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video).
      Ptr<InputMessageContent> inputMessageContent;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "voice_url", voiceUrl);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD(json, "performer", performer);
        OBJECT_SERIALIZE_FIELD(json, "voice_duration", voiceDuration);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "audio_url", voiceUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "performer", performer, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "voice_duration", voiceDuration, 0, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

  /// @brief Represents a link to a file. By default, this file will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the file.
  /// Currently, only .PDF and .ZIP files can be sent using this method.
  /// @note: This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them.
  struct InlineQueryResultDocument : InlineQueryResult {
      InlineQueryResultDocument() {
        InlineQueryResult::type = "document";
      }
      explicit InlineQueryResultDocument(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "document";
      }

      /// @brief Title for the result
      std::string title;

      /// @brief Optional. Caption of the document to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the document caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief A valid URL for the file
      std::string documentUrl;

      /// @brief MIME type of the content of the file, either “application/pdf” or “application/zip”
      std::string mimeType;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Content of the message to be sent instead of the video.
      /// This field is required if InlineQueryResultVideo is used to send an HTML-page as a result (e.g., a YouTube video).
      Ptr<InputMessageContent> inputMessageContent;

      /// @brief Optional. URL of the thumbnail (JPEG only) for the file
      std::string thumbnailUrl;

      /// @brief Optional. Thumbnail width;
      std::int32_t thumbnailWidth{};

      /// @brief Optional. Thumbnail height;
      std::int32_t thumbnailHeight{};

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD(json, "document_url", documentUrl);
        OBJECT_SERIALIZE_FIELD(json, "mime_type", mimeType);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "document_url", documentUrl, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "mime_type", mimeType, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight, 0, true);
      }
  };

  /// @brief Represents a location on a map.
  /// By default, the location will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the location.
  struct InlineQueryResultLocation : InlineQueryResult {
      InlineQueryResultLocation() {
        InlineQueryResult::type = "location";
      }
      explicit InlineQueryResultLocation(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "location";
      }

      /// @brief Location latitude in degrees
      float latitude{};

      /// @brief Location longitude in degrees
      float longitude{};

      /// @brief Location title
      std::string title;

      /// @brief Optional. The radius of uncertainty for the location, measured in meters; 0-1500
      float horizontalAccuracy{};

      /// @brief Optional. Period in seconds for which the location can be updated, should be between 60 and 86400.
      std::int32_t livePeriod{};

      /// @brief Optional. For live locations, a direction in which the user is moving, in degrees. Must be between 1 and 360 if specified.
      std::int32_t heading{};

      /// @brief Optional. For live locations, a maximum distance for proximity alerts about approaching another chat member, in meters.
      /// Must be between 1 and 100000 if specified.
      std::int32_t proximityAlertRadius{};

      /// @brief Optional. Content of the message to be sent instead of the location.
      Ptr<InputMessageContent> inputMessageContent;

      /// @brief Optional. URL of the thumbnail (JPEG only) for the file
      std::string thumbnailUrl;

      /// @brief Optional. Thumbnail width;
      std::int32_t thumbnailWidth{};

      /// @brief Optional. Thumbnail height;
      std::int32_t thumbnailHeight{};

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
        OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy);
        OBJECT_SERIALIZE_FIELD(json, "live_period", livePeriod);
        OBJECT_SERIALIZE_FIELD(json, "heading", heading);
        OBJECT_SERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "horizontal_accuracy", horizontalAccuracy, 0.0f, true);
        OBJECT_DESERIALIZE_FIELD(json, "live_period", livePeriod, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "heading", heading, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "proximity_alert_radius", proximityAlertRadius, 0, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight, 0, true);
      }
  };

  /// @brief Represents a venue. By default, the venue will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the venue.
  struct InlineQueryResultVenue : InlineQueryResult {
      InlineQueryResultVenue() {
        InlineQueryResult::type = "venue";
      }
      explicit InlineQueryResultVenue(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "venue";
      }

      /// @brief Latitude of the venue location in degrees
      float latitude{};

      /// @brief Longitude of the venue location in degrees
      float longitude{};

      /// @brief Title of the venue
      std::string title;

      /// @brief Address of the venue
      std::string address;

      /// @brief Optional. Foursquare identifier of the venue if known
      std::string foursquareId;

      /// @brief Optional. Foursquare type of the venue, if known.
      /// (For example, “arts_entertainment/default”, “arts_entertainment/aquarium” or “food/icecream”.)
      std::string foursquareType;

      /// @brief Optional. Google Places identifier of the venue
      std::string googlePlaceId;

      /// @brief Optional. Google Places type of the venue. (See [supported types](https://developers.google.com/places/web-service/supported_types).)
      std::string googlePlaceType;

      /// @brief Optional. Content of the message to be sent instead of the venue.
      Ptr<InputMessageContent> inputMessageContent;

      /// @brief Optional. URL of the thumbnail (JPEG only) for the file
      std::string thumbnailUrl;

      /// @brief Optional. Thumbnail width;
      std::int32_t thumbnailWidth{};

      /// @brief Optional. Thumbnail height;
      std::int32_t thumbnailHeight{};

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "latitude", latitude);
        OBJECT_SERIALIZE_FIELD(json, "longitude", longitude);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "address", address);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_id", foursquareId);
        OBJECT_SERIALIZE_FIELD(json, "foursquare_type", foursquareType);
        OBJECT_SERIALIZE_FIELD(json, "google_place_id", googlePlaceId);
        OBJECT_SERIALIZE_FIELD(json, "google_place_type", googlePlaceType);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "latitude", latitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "longitude", longitude, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "address", address, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_id", foursquareId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "foursquare_type", foursquareType, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_id", googlePlaceId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "google_place_type", googlePlaceType, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight, 0, true);
      }
  };


  /// @brief Represents a venue. By default, the venue will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the venue.
  struct InlineQueryResultContact : InlineQueryResult {
      InlineQueryResultContact() {
        InlineQueryResult::type = "contact";
      }
      explicit InlineQueryResultContact(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "contact";
      }

      /// @brief Contact's phone number
      std::string phoneNumber;

      /// @brief Contact's first name
      std::string firstName;

      /// @brief Optional. Contact's last name
      std::string lastName;

      /// @brief Optional. Additional data about the contact in the form of a vCard, 0-2048 bytes
      std::string vcard;

      /// @brief Optional. Content of the message to be sent instead of the contact.
      Ptr<InputMessageContent> inputMessageContent;

      /// @brief Optional. Url of the thumbnail for the result
      std::string thumbnailUrl;

      /// @brief Optional. Thumbnail width;
      std::int32_t thumbnailWidth{};

      /// @brief Optional. Thumbnail height;
      std::int32_t thumbnailHeight{};

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "phone_number", phoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
        OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
        OBJECT_SERIALIZE_FIELD(json, "vcard", vcard);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth);
        OBJECT_SERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "phone_number", phoneNumber, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "vcard", vcard, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_url", thumbnailUrl, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_width", thumbnailWidth, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "thumbnail_height", thumbnailHeight, 0, true);
      }
  };


  /// @brief Represents a Game.
  /// @note This will only work in Telegram versions released after October 1, 2016. Older clients will not display any inline results if a game result is among them.
  struct InlineQueryResultGame : InlineQueryResult {
      InlineQueryResultGame() {
        InlineQueryResult::type = "game";
      }
      explicit InlineQueryResultGame(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "game";
      }

      /// @brief Short name of the game
      std::string gameShortName;

      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "game_short_name", gameShortName);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "game_short_name", gameShortName, "", false);
      }
  };


  /// @brief Represents a link to a photo stored on the Telegram servers. By default, this photo will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
  struct InlineQueryResultCachedPhoto : InlineQueryResult {
      InlineQueryResultCachedPhoto() {
        InlineQueryResult::type = "photo";
      }
      explicit InlineQueryResultCachedPhoto(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "photo";
      }

      /// @brief A valid file identifier of the photo
      std::string photoFileId;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Caption of the photo to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the photo caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the photo.
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "photo_file_id", photoFileId);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "photo_file_id", photoFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to an animated GIF file stored on the Telegram servers.
  /// By default, this animated GIF file will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
  struct InlineQueryResultCachedGif : InlineQueryResult {
      InlineQueryResultCachedGif() {
        InlineQueryResult::type = "gif";
      }
      explicit InlineQueryResultCachedGif(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "gif";
      }

      /// @brief A valid file identifier for the GIF file
      std::string gifFileId;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Caption of the GIF file to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the GIF caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the GIF.
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "gif_file_id", gifFileId);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "gif_file_id", gifFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

  /// @brief Represents a link to a video animation (H.264/MPEG-4 AVC video without sound) stored on the Telegram servers.
  /// By default, this animated MPEG-4 file will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
  struct InlineQueryResultCachedMpeg4Gif : InlineQueryResult {
      InlineQueryResultCachedMpeg4Gif() {
        InlineQueryResult::type = "mpeg4_gif";
      }
      explicit InlineQueryResultCachedMpeg4Gif(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "mpeg4_gif";
      }

      /// @brief A valid file identifier for the MPEG4 file
      std::string mpeg4FileId;

      /// @brief Optional. Title for the result
      std::string title;

      /// @brief Optional. Caption of the MPEG-4 file to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the MPEG-4 caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Optional. Content of the message to be sent instead of the video animation
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "mpeg4_file_id", mpeg4FileId);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "mpeg4_file_id", mpeg4FileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

  /// @brief Represents a link to a sticker stored on the Telegram servers.
  /// By default, this sticker will be sent by the user.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
  /// @note This will only work in Telegram versions released after 9 April, 2016 for static stickers and after 06 July, 2019 for animated stickers. Older clients will ignore them.
  struct InlineQueryResultCachedSticker : InlineQueryResult {
      InlineQueryResultCachedSticker() {
        InlineQueryResult::type = "sticker";
      }
      explicit InlineQueryResultCachedSticker(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "sticker";
      }

      /// @brief A valid file identifier of the sticker
      std::string stickerFileId;

      /// @brief Optional. Optional. Content of the message to be sent instead of the sticker
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "sticker_file_id", stickerFileId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "sticker_file_id", stickerFileId, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to a file stored on the Telegram servers.
  /// By default, this file will be sent by the user with an optional caption.
  /// Alternatively, you can use inputMessageContent to send a message with the specified content instead of the photo.
  /// @note This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them.
  struct InlineQueryResultCachedDocument : InlineQueryResult {
      InlineQueryResultCachedDocument() {
        InlineQueryResult::type = "document";
      }
      explicit InlineQueryResultCachedDocument(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "document";
      }

      /// @brief Title for the result
      std::string title;

      /// @brief A valid file identifier for the file
      std::string documentFileId;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Caption of the document to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the document caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the document.
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "document_file_id", documentFileId);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "document_file_id", documentFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to a video file stored on the Telegram servers.
  /// By default, this video file will be sent by the user with an optional caption
  struct InlineQueryResultCachedVideo : InlineQueryResult {
      InlineQueryResultCachedVideo() {
        InlineQueryResult::type = "video";
      }
      explicit InlineQueryResultCachedVideo(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "video";
      }

      /// @brief A valid file identifier for the video file
      std::string videoFileId;

      /// @brief Title for the result
      std::string title;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Caption of the video to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the document caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the video caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the video.
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "video_file_id", videoFileId);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "video_file_id", videoFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to a voice message stored on the Telegram servers.
  /// By default, this voice message will be sent by the user.
  /// @note This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them.
  struct InlineQueryResultCachedVoice : InlineQueryResult {
      InlineQueryResultCachedVoice() {
        InlineQueryResult::type = "voice";
      }
      explicit InlineQueryResultCachedVoice(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "voice";
      }

      /// @brief A valid file identifier for the voice message
      std::string voiceFileId;

      /// @brief Voice message title
      std::string title;

      /// @brief Optional. Short description of the result
      std::string description;

      /// @brief Optional. Caption of the voice to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the voice caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the voice caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the voice.
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "voice_file_id", voiceFileId);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "voice_file_id", voiceFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };


  /// @brief Represents a link to an MP3 audio file stored on the Telegram servers.
  /// By default, this audio file will be sent by the user.
  /// @note This will only work in Telegram versions released after 9 April, 2016. Older clients will ignore them.
  struct InlineQueryResultCachedAudio : InlineQueryResult {
      InlineQueryResultCachedAudio() {
        InlineQueryResult::type = "audio";
      }
      explicit InlineQueryResultCachedAudio(const nl::json& json) : InlineQueryResult(json) {
        InlineQueryResult::type = "audio";
      }

      /// @brief A valid file identifier for the audio file
      std::string audioFileId;

      /// @brief Optional. Caption of the audio to be sent, 0-1024 characters after entities parsing
      std::string caption;

      /// @brief Optional. Mode for parsing entities in the audio caption. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string parseMode;

      /// @brief Optional. List of special entities that appear in the voice caption, which can be specified instead of parseMode
      std::vector<Ptr<MessageEntity>> captionEntities;

      /// @brief Optional. Content of the message to be sent instead of the audio
      Ptr<InputMessageContent> inputMessageContent;


      nl::json toJson() const override {
        nl::json json = InlineQueryResult::toJson();
        OBJECT_SERIALIZE_FIELD(json, "audio_file_id", audioFileId);
        OBJECT_SERIALIZE_FIELD(json, "caption", caption);
        OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent);
        return json;
      }

      void fromJson(const nl::json& json) override {
        InlineQueryResult::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "audio_file_id", audioFileId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "caption", caption, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "caption_entities", captionEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, true);
      }
  };

}