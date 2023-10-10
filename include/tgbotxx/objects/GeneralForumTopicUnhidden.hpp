#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about General forum topic unhidden in the chat.
  /// Currently holds no information.
  /// @ref https://core.telegram.org/bots/api#generalforumtopicunhidden
  struct GeneralForumTopicUnhidden {
      GeneralForumTopicUnhidden() = default;
      explicit GeneralForumTopicUnhidden(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson([[maybe_unused]] const nl::json& json) {
      }
  };
}