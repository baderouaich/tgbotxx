#pragma once
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ReactionCount.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents reaction changes on a message with anonymous reactions.
  /// @ref https://core.telegram.org/bots/api#messagereactioncountupdated
  struct MessageReactionCountUpdated {
      MessageReactionCountUpdated() = default;
      explicit MessageReactionCountUpdated(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The chat containing the message
      Ptr<Chat> chat;

      /// @brief Unique message identifier inside the chat
      std::int32_t messageId{};

      /// @brief Date of the change in Unix time
      std::time_t date{};

      /// @brief List of reactions that are present on the message
      std::vector<Ptr<ReactionCount>> reactions;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
        OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
        OBJECT_SERIALIZE_FIELD(json, "date", date);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "reactions", reactions);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "reactions", reactions, false);
      }
  };
}