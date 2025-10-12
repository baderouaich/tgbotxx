#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/StoryAreaPosition.hpp>
#include <tgbotxx/objects/StoryAreaType.hpp>

namespace tgbotxx {

  /// @brief Describes a clickable area on a story media
  /// @ref https://core.telegram.org/bots/api#storyarea
  struct StoryArea {
    StoryArea() = default;
    explicit StoryArea(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Position of the area
    Ptr<StoryAreaPosition> position;

    /// @brief Type of the area
    Ptr<StoryAreaType> type;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "position", position);
      OBJECT_SERIALIZE_FIELD_PTR(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "position", position, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "type", type, false);
    }
  };

}
