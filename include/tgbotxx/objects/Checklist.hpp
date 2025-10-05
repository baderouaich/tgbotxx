#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/ChecklistTask.hpp>

namespace tgbotxx {
  /// @brief Describes a checklist.
  /// @ref https://core.telegram.org/bots/api#checklist
  struct Checklist {
    Checklist() = default;
    explicit Checklist(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Title of the checklist
    std::string title;

    /// @brief Optional. Special entities that appear in the checklist title
    std::vector<Ptr<MessageEntity>> titleEntities;

    /// @brief List of tasks in the checklist
    std::vector<Ptr<ChecklistTask>> tasks;

    /// @brief Optional. True, if users other than the creator of the list can add tasks to the list
    bool othersCanAddTasks{};

    /// @brief Optional. True, if users other than the creator of the list can mark tasks as done or not done
    bool othersCanMarkTasksAsDone{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "title_entities", titleEntities);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks);
      OBJECT_SERIALIZE_FIELD(json, "others_can_add_tasks", othersCanAddTasks);
      OBJECT_SERIALIZE_FIELD(json, "others_can_mark_tasks_as_done", othersCanMarkTasksAsDone);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "title_entities", titleEntities, true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks, false);
      OBJECT_DESERIALIZE_FIELD(json, "others_can_add_tasks", othersCanAddTasks, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "others_can_mark_tasks_as_done", othersCanMarkTasksAsDone, false, true);
    }
  };
}