#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Video.hpp>

namespace tgbotxx {
  /// @brief This object describes paid media. Currently, it can be one of:
  /// - PaidMediaPreview
  /// - PaidMediaPhoto
  /// - PaidMediaVideo
  /// @ref https://core.telegram.org/bots/api#paidmedia
  struct PaidMedia {
    PaidMedia() = default;
    explicit PaidMedia(const nl::json& json) {
      PaidMedia::fromJson(json);
    }
    virtual ~PaidMedia() = default;

    /// @brief Type of the paid media, one of "preview", "photo" or "video"
    std::string type;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief The paid media isn't available before the payment.
  /// @ref https://core.telegram.org/bots/api#paidmediapreview
  struct PaidMediaPreview : PaidMedia {
    PaidMediaPreview() = default;
    explicit PaidMediaPreview(const nl::json& json) {
      PaidMediaPreview::fromJson(json);
      // PaidMedia::type = "preview";
    }

    /// @brief Optional. Media width as defined by the sender
    std::int32_t width{};

    /// @brief Optional. Media height as defined by the sender
    std::int32_t height{};

    /// @brief Optional. Duration of the media in seconds as defined by the sender
    std::int32_t duration{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = PaidMedia::toJson();
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "duration", duration);
      return json;
    }

    void fromJson(const nl::json& json) override {
      PaidMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "duration", duration, 0, true);
    }
  };


  /// @brief The paid media is a photo.
  /// @ref https://core.telegram.org/bots/api#paidmediaphoto
  struct PaidMediaPhoto : PaidMedia {
    PaidMediaPhoto() = default;
    explicit PaidMediaPhoto(const nl::json& json) {
      PaidMediaPhoto::fromJson(json);
      // PaidMedia::type = "photo";
    }

    /// @brief The photo
    std::vector<Ptr<PhotoSize>> photo;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = PaidMedia::toJson();
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo);
      return json;
    }

    void fromJson(const nl::json& json) override {
      PaidMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo, false);
    }
  };


  /// @brief The paid media is a video.
  /// @ref https://core.telegram.org/bots/api#paidmediavideo
  struct PaidMediaVideo : PaidMedia {
    PaidMediaVideo() = default;
    explicit PaidMediaVideo(const nl::json& json) {
      PaidMediaVideo::fromJson(json);
      // PaidMedia::type = "video";
    }

    /// @brief The video
    Ptr<Video> video;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = PaidMedia::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "video", video);
      return json;
    }

    void fromJson(const nl::json& json) override {
      PaidMedia::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "video", video, false);
    }
  };
}