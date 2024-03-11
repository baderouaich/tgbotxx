#pragma once
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ReactionType.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents a change of a reaction on a message performed by a user.
  /// @ref https://core.telegram.org/bots/api#messagereactionupdated
  struct MessageReactionUpdated {
      MessageReactionUpdated() = default;
      explicit MessageReactionUpdated(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The chat containing the message the user reacted to
      Ptr<Chat> chat;

      /// @brief Unique identifier of the message inside the chat
      std::int32_t messageId{};

      /// @brief Optional. The user that changed the reaction, if the user isn't anonymous
      Ptr<User> user;

      /// @brief Optional. The chat on behalf of which the reaction was changed, if the user is anonymous
      Ptr<Chat> actorChat;

      /// @brief Date of the change in Unix time
      std::time_t date{};

      /// @brief Previous list of reaction types that were set by the user
      std::vector<Ptr<ReactionType>> oldReaction;

      /// @brief New list of reaction types that have been set by the user
      std::vector<Ptr<ReactionType>> newReaction;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
        OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
        OBJECT_SERIALIZE_FIELD_PTR(json, "actor_chat", actorChat);
        OBJECT_SERIALIZE_FIELD(json, "date", date);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "old_reaction", oldReaction);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "new_reaction", newReaction);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "actor_chat", actorChat, true);
        OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "old_reaction", oldReaction, false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "new_reaction", newReaction, false);
      }
  };
}