#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about checklist tasks marked as done or not done.
  /// @ref https://core.telegram.org/bots/api#checklisttasksdone
  struct ChecklistTasksDone {
    ChecklistTasksDone() = default;
    explicit ChecklistTasksDone(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the checklist whose tasks were marked as done or not done.
    /// Note: reply_to_message is excluded even if it was a reply.
    Ptr<Message> checklistMessage;

    /// @brief Optional. Identifiers of the tasks that were marked as done
    std::vector<std::int32_t> markedAsDoneTaskIds;

    /// @brief Optional. Identifiers of the tasks that were marked as not done
    std::vector<std::int32_t> markedAsNotDoneTaskIds;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "checklist_message", checklistMessage);
      OBJECT_SERIALIZE_FIELD(json, "marked_as_done_task_ids", markedAsDoneTaskIds);
      OBJECT_SERIALIZE_FIELD(json, "marked_as_not_done_task_ids", markedAsNotDoneTaskIds);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "checklist_message", checklistMessage, true);
      OBJECT_DESERIALIZE_FIELD(json, "marked_as_done_task_ids", markedAsDoneTaskIds, {}, true);
      OBJECT_DESERIALIZE_FIELD(json, "marked_as_not_done_task_ids", markedAsNotDoneTaskIds, {}, true);
    }
  };

}