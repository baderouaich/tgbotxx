#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief Describes a task in a checklist.
  /// @ref https://core.telegram.org/bots/api#checklisttask
  struct ChecklistTask {
    ChecklistTask() = default;
    explicit ChecklistTask(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the task
    std::int32_t id{};

    /// @brief Text of the task
    std::string text;

    /// @brief Optional. Special entities that appear in the task text
    std::vector<Ptr<MessageEntity>> textEntities;

    /// @brief Optional. User that completed the task; omitted if the task wasn't completed
    Ptr<User> completedByUser;

    /// @brief Optional. Point in time (Unix timestamp) when the task was completed; 0 if the task wasn't completed
    std::time_t completionDate{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities);
      OBJECT_SERIALIZE_FIELD_PTR(json, "completed_by_user", completedByUser);
      OBJECT_SERIALIZE_FIELD(json, "completion_date", completionDate);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "completed_by_user", completedByUser, true);
      OBJECT_DESERIALIZE_FIELD(json, "completion_date", completionDate, 0, true);
    }
  };
}