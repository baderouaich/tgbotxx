#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a message about a forwarded story in the chat.
  /// Currently holds no information.
  /// @ref https://core.telegram.org/bots/api#story
  struct Story {
      Story() = default;
      explicit Story(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
      }
  };
}