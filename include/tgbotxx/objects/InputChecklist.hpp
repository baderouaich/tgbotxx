#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/InputChecklistTask.hpp>

namespace tgbotxx {
  /// @brief Describes a checklist to create.
  /// @ref https://core.telegram.org/bots/api#inputchecklist
  struct InputChecklist {
    InputChecklist() = default;
    explicit InputChecklist(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Title of the checklist; 1-255 characters after entities parsing
    std::string title;

    /// @brief Optional. Mode for parsing entities in the title. See formatting options for more details.
    std::string parseMode;

    /// @brief Optional. List of special entities that appear in the title,
    /// which can be specified instead of parse_mode.
    /// Currently, only bold, italic, underline, strikethrough, spoiler, and custom_emoji entities are allowed.
    std::vector<Ptr<MessageEntity>> titleEntities;

    /// @brief List of 1-30 tasks in the checklist
    std::vector<Ptr<InputChecklistTask>> tasks;

    /// @brief Optional. Pass True if other users can add tasks to the checklist
    bool othersCanAddTasks{};

    /// @brief Optional. Pass True if other users can mark tasks as done or not done in the checklist
    bool othersCanMarkTasksAsDone{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      OBJECT_SERIALIZE_FIELD(json, "parse_mode", parseMode);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "title_entities", titleEntities);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks);
      OBJECT_SERIALIZE_FIELD(json, "others_can_add_tasks", othersCanAddTasks);
      OBJECT_SERIALIZE_FIELD(json, "others_can_mark_tasks_as_done", othersCanMarkTasksAsDone);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "parse_mode", parseMode, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "title_entities", titleEntities, true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks, false);
      OBJECT_DESERIALIZE_FIELD(json, "others_can_add_tasks", othersCanAddTasks, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "others_can_mark_tasks_as_done", othersCanMarkTasksAsDone, false, true);
    }
  };

}
