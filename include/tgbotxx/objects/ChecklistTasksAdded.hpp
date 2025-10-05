#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/ChecklistTask.hpp>

namespace tgbotxx {

  /// @brief Describes a service message about tasks added to a checklist.
  /// @ref https://core.telegram.org/bots/api#checklisttasksadded
  struct ChecklistTasksAdded {
    ChecklistTasksAdded() = default;
    explicit ChecklistTasksAdded(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the checklist to which the tasks were added.
    Ptr<Message> checklistMessage;

    /// @brief List of tasks added to the checklist
    std::vector<Ptr<ChecklistTask>> tasks;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "checklist_message", checklistMessage);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist_message", checklistMessage, true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "tasks", tasks, false);
    }
  };

}
