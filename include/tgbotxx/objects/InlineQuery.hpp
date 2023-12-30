#pragma once
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents an incoming inline query. When the user sends an empty query,
  /// your bot could return some default or trending results.
  /// @ref https://core.telegram.org/bots/api#inlinequery
  struct InlineQuery {
      InlineQuery() = default;
      explicit InlineQuery(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique identifier for this query
      std::string id;

      /// @brief Sender
      Ptr<User> from;

      /// @brief Text of the query (up to 256 characters)
      std::string query;

      /// @brief Offset of the results to be returned, can be controlled by the bot
      std::string offset;

      /// @brief Optional. Type of the chat, from which the inline query was sent.
      /// Can be either “sender” for a private chat with the inline query sender, “private”, “group”, “supergroup”, or “channel”.
      /// The chat type should be always known for requests sent from official clients and most third-party clients, unless the request was sent from a secret chat
      std::string chatType;

      /// @brief Optional. Sender location, only for bots that request user location
      Ptr<Location> location;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "id", id);
        OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
        OBJECT_SERIALIZE_FIELD(json, "query", query);
        OBJECT_SERIALIZE_FIELD(json, "offset", offset);
        OBJECT_SERIALIZE_FIELD(json, "chat_type", chatType);
        OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
        OBJECT_DESERIALIZE_FIELD(json, "query", query, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "offset", offset, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "chat_type", chatType, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
      }
  };
}
