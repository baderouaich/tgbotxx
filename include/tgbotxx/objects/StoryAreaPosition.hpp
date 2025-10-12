#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief Describes the position of a clickable area within a story
  /// @ref https://core.telegram.org/bots/api#storyareaposition
  struct StoryAreaPosition {
    StoryAreaPosition() = default;
    explicit StoryAreaPosition(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The abscissa of the area's center, as a percentage of the media width
    float xPercentage{};

    /// @brief The ordinate of the area's center, as a percentage of the media height
    float yPercentage{};

    /// @brief The width of the area's rectangle, as a percentage of the media width
    float widthPercentage{};

    /// @brief The height of the area's rectangle, as a percentage of the media height
    float heightPercentage{};

    /// @brief The clockwise rotation angle of the rectangle, in degrees; 0-360
    float rotationAngle{};

    /// @brief The radius of the rectangle corner rounding, as a percentage of the media width
    float cornerRadiusPercentage{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "x_percentage", xPercentage);
      OBJECT_SERIALIZE_FIELD(json, "y_percentage", yPercentage);
      OBJECT_SERIALIZE_FIELD(json, "width_percentage", widthPercentage);
      OBJECT_SERIALIZE_FIELD(json, "height_percentage", heightPercentage);
      OBJECT_SERIALIZE_FIELD(json, "rotation_angle", rotationAngle);
      OBJECT_SERIALIZE_FIELD(json, "corner_radius_percentage", cornerRadiusPercentage);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "x_percentage", xPercentage, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "y_percentage", yPercentage, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "width_percentage", widthPercentage, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "height_percentage", heightPercentage, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "rotation_angle", rotationAngle, 0.0f, false);
      OBJECT_DESERIALIZE_FIELD(json, "corner_radius_percentage", cornerRadiusPercentage, 0.0f, false);
    }
  };

}
