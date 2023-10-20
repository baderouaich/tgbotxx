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
        OBJECT_SERIALIZE_FIELD_PTR(json, "reply_markup", replyMarkup, nl::json::object());
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
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, nl::json::object());
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
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, nl::json::object());
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
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, nl::json::object());
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
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, nl::json::object());
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

      /// @brief Optional. Mode for parsing entities in the video caption.. See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
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
        OBJECT_SERIALIZE_FIELD_PTR(json, "input_message_content", inputMessageContent, nl::json::object());
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


  // TODO: InlineQueryResult*
}