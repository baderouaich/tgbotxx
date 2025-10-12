#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>

namespace tgbotxx {

  /// @brief Describes a task to add to a checklist.
  /// @ref https://core.telegram.org/bots/api#inputchecklisttask
  struct InputChecklistTask {
    InputChecklistTask() = default;
    explicit InputChecklistTask(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the task; must be positive and unique among all task identifiers currently present in the checklist
    std::int32_t id{};

    /// @brief Text of the task; 1-100 characters after entities parsing
    std::string text;

    /// @brief Optional. Mode for parsing entities in the text. See formatting options for more details.
    std::string parseMode;

    /// @brief Optional. List of special entities that appear in the text, which can be specified instead of parse_mode.
    /// Currently, only bold, italic, underline, strikethrough, spoiler, and custom_emoji entities are allowed.
    std::vector<Ptr<MessageEntity>> textEntities;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities, true);
    }
  };

}
