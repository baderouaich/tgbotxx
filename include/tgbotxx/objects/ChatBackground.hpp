#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/BackgroundType.hpp>

namespace tgbotxx {

  /// @brief This object represents a chat background.
  /// @ref https://core.telegram.org/bots/api#chatbackground
  struct ChatBackground {
    ChatBackground() = default;
    explicit ChatBackground(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Type of the background
    Ptr<BackgroundType> type;

    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "type", type);
      return json;
    }

    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "type", type, false);
    }
  };

}