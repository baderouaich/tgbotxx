#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief This object represents a story. .
  /// @ref https://core.telegram.org/bots/api#story
  struct Story {
    Story() = default;
    explicit Story(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Chat that posted the story
    Ptr<Chat> chat;

    /// @brief Unique identifier for the story in the chat
    std::int32_t id{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
    }
  };
}