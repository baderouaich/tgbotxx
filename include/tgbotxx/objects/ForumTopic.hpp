#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a forum topic.
  /// @ref https://core.telegram.org/bots/api#forumtopic
  struct ForumTopic {
      ForumTopic() = default;
      explicit ForumTopic(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique identifier of the forum topic
      std::int32_t messageThreadId{};

      /// @brief Name of the topic
      std::string name;

      /// @brief Color of the topic icon in RGB format
      std::int32_t iconColor{};

      /// @brief Optional. Unique identifier of the custom emoji shown as the topic icon
      std::int32_t iconCustomEmojiId{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "message_thread_id", messageThreadId);
        OBJECT_SERIALIZE_FIELD(json, "name", name);
        OBJECT_SERIALIZE_FIELD(json, "icon_color", iconColor);
        OBJECT_SERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "message_thread_id", messageThreadId, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "icon_color", iconColor, 0x000000, false);
        OBJECT_DESERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId, 0, true);
      }
  };
}