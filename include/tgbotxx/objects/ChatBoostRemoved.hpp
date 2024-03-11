#pragma once
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/ChatBoost.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a boost removed from a chat.
  /// @ref https://core.telegram.org/bots/api#chatboostremoved
  struct ChatBoostRemoved {
      ChatBoostRemoved() = default;
      explicit ChatBoostRemoved(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Chat which was boosted
      Ptr<Chat> chat;

      /// @brief Unique identifier of the boost
      std::string boostID;

      /// @brief Point in time (Unix timestamp) when the boost was removed
      std::time_t removeDate{};

      /// @brief Source of the removed boost
      Ptr<ChatBoostSource> source;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
        OBJECT_SERIALIZE_FIELD(json, "boost_id", boostID);
        OBJECT_SERIALIZE_FIELD(json, "remove_date", removeDate);
        OBJECT_SERIALIZE_FIELD_PTR(json, "source", source);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD(json, "boost_id", boostID, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "remove_date", removeDate, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "source", source, false);
      }
  };
}