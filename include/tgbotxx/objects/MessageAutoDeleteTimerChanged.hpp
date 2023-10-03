#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a service message about a change in auto-delete timer settings.
  /// @ref https://core.telegram.org/bots/api#messageautodeletetimerchanged
  struct MessageAutoDeleteTimerChanged {
      MessageAutoDeleteTimerChanged() = default;
      explicit MessageAutoDeleteTimerChanged(const nl::json& json) {
        fromJson(json);
      }
      /// @brief New auto-delete time for messages in the chat; in seconds
      std::int32_t messageAutoDeleteTime{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime, 0, false);
      }
  };
}