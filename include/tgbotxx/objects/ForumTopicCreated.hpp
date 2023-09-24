#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents a service message about a new forum topic created in the chat.
    /// @ref https://core.telegram.org/bots/api#forumtopiccreated
    struct ForumTopicCreated {
        explicit ForumTopicCreated(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Name of the topic
        std::string name;

        /// @brief Color of the topic icon in RGB format
        std::int32_t iconColor;

        /// @brief Optional. Unique identifier of the custom emoji shown as the topic icon
        std::string iconCustomEmojiId;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "name", name);
          OBJECT_SERIALIZE_FIELD(json, "icon_color", iconColor);
          OBJECT_SERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "icon_color", iconColor, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "icon_custom_emoji_id", iconCustomEmojiId, "", true);
        }
    };
}