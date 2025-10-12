#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief Base class for profile photos to set
  /// @ref https://core.telegram.org/bots/api#inputprofilephoto
  struct InputProfilePhoto {
    InputProfilePhoto() = default;
    explicit InputProfilePhoto(const nl::json& json) {
      _fromJson(json);
    }
    virtual ~InputProfilePhoto() = default;

    /// @brief Type of the profile photo
    std::string type;

    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }

  private:
    void _fromJson(const nl::json& json) {
      fromJson(json);
    }
  };

  /// @brief A static profile photo in the .JPG format
  /// @ref https://core.telegram.org/bots/api#inputprofilephotostatic
  struct InputProfilePhotoStatic : InputProfilePhoto {
    InputProfilePhotoStatic() {
      InputProfilePhoto::type = "static";
    }
    explicit InputProfilePhotoStatic(const nl::json& json) : InputProfilePhoto(json) {
      InputProfilePhoto::type = "static";
    }

    /// @brief The static profile photo. Profile photos can't be reused and can only be uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the photo was uploaded using multipart/form-data
    std::string photo;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const override {
      nl::json json = InputProfilePhoto::toJson();
      OBJECT_SERIALIZE_FIELD(json, "photo", photo);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      InputProfilePhoto::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "photo", photo, "", false);
    }
  };

  /// @brief An animated profile photo in the MPEG4 format
  /// @ref https://core.telegram.org/bots/api#inputprofilephotoanimated
  struct InputProfilePhotoAnimated : InputProfilePhoto {
    InputProfilePhotoAnimated() {
      InputProfilePhoto::type = "animated";
    }
    explicit InputProfilePhotoAnimated(const nl::json& json) : InputProfilePhoto(json) {
      InputProfilePhoto::type = "animated";
    }

    /// @brief The animated profile photo. Profile photos can't be reused and can only be uploaded as a new file,
    /// so you can pass “attach://<file_attach_name>” if the photo was uploaded using multipart/form-data
    std::string animation;

    /// @brief Optional. Timestamp in seconds of the frame that will be used as the static profile photo. Defaults to 0.0
    double mainFrameTimestamp{0.0};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const override {
      nl::json json = InputProfilePhoto::toJson();
      OBJECT_SERIALIZE_FIELD(json, "animation", animation);
      OBJECT_SERIALIZE_FIELD(json, "main_frame_timestamp", mainFrameTimestamp);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      InputProfilePhoto::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "animation", animation, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "main_frame_timestamp", mainFrameTimestamp, 0.0, true);
    }
  };

}
