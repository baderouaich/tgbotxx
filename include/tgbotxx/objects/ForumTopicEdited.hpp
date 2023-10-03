#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about an edited forum topic.
  /// @ref https://core.telegram.org/bots/api#forumtopicedited
  struct ForumTopicEdited {
      ForumTopicEdited() = default;
      explicit ForumTopicEdited(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Optional. New name of the topic, if it was edited
      std::string name;

      /// @brief Optional. New identifier of the custom emoji shown as the topic icon, if it was edited; an empty string if the icon was removed
      std::string iconCustomEmojiId;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "name", name);
        OBJECT_SERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId, "", true);
      }
  };
}