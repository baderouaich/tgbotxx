#pragma once
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChatBoost.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a boost added to a chat or changed.
  /// @ref https://core.telegram.org/bots/api#chatboostupdated
  struct ChatBoostUpdated {
      ChatBoostUpdated() = default;
      explicit ChatBoostUpdated(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Chat which was boosted
      Ptr<Chat> chat;

      /// @brief Information about the chat boost
      Ptr<ChatBoost> boost;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
        OBJECT_SERIALIZE_FIELD_PTR(json, "boost", boost);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "boost", boost, false);
      }
  };
}