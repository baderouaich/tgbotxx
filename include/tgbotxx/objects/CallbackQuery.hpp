#pragma once

#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/User.hpp>
#include <nlohmann/json.hpp>

namespace nl = nlohmann;

namespace tgbotxx {
    /// @brief This object represents an incoming callback query from a callback button in an inline keyboard.
    /// If the button that originated the query was attached to a message sent by the bot, the field message will be present.
    /// If the button was attached to a message sent via the bot (in inline mode), the field inline_message_id will be present.
    /// Exactly one of the fields data or game_short_name will be present.
    /// @ref https://core.telegram.org/bots/api#callbackquery
    struct CallbackQuery {
        explicit CallbackQuery(const nl::json &json) {
          fromJson(json);
        }

        /// @brief Unique identifier for this query
        std::string id;

        /// @brief Sender
        Ptr<User> from;

        /// @brief Optional. Message with the callback button that originated the query.
        /// @note Note that message content and message date will not be available if the message is too old
        Ptr<Message> message;

        /// @brief Optional. Identifier of the message sent via the bot in inline mode, that originated the query.
        std::string inlineMessageId;

        /// @brief Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent.
        /// Useful for high scores in games.
        std::string chatInstance;

        /// @brief Optional. Data associated with the callback button.
        /// @note Be aware that the message originated the query can contain no callback buttons with this data.
        std::string data;

        /// @brief Optional. Short name of a Game to be returned, serves as the unique identifier for the game
        std::string gameShortName;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "id", id);
          OBJECT_SERIALIZE_FIELD_PTR(json, "from", from, nl::json::object());
          OBJECT_SERIALIZE_FIELD_PTR(json, "message", message, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "inline_message_id", inlineMessageId);
          OBJECT_SERIALIZE_FIELD(json, "chat_instance", chatInstance);
          OBJECT_SERIALIZE_FIELD(json, "data", data);
          OBJECT_SERIALIZE_FIELD(json, "game_short_name", gameShortName);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "message", message, true);
          OBJECT_DESERIALIZE_FIELD(json, "inline_message_id", inlineMessageId, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "chat_instance", chatInstance, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "data", data, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "game_short_name", gameShortName, "", true);
        }
    };
}
