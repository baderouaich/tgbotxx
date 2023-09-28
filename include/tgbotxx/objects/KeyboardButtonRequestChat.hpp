#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>

namespace tgbotxx {
    /// @brief This object defines the criteria used to request a suitable chat.
    /// The identifier of the selected chat will be shared with the bot when the corresponding button is pressed.
    /// More about requesting chats » https://core.telegram.org/bots/features#chat-and-user-selection
    /// @ref https://core.telegram.org/bots/api#keyboardbuttonrequestchat
    struct KeyboardButtonRequestChat {
        explicit KeyboardButtonRequestChat(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Signed 32-bit identifier of the request, which will be received back in the ChatShared object.
        /// @note Must be unique within the message
        std::int32_t requestId;

        /// @brief Pass True to request a channel chat, pass False to request a group or a supergroup chat.
        bool chatIsChannel;

        /// @brief Optional. Pass True to request a forum supergroup, pass False to request a non-forum chat.
        /// If not specified, no additional restrictions are applied.
        bool chatIsForum;

        /// @brief Optional. Pass True to request a supergroup or a channel with a username, pass False to request a chat without a username.
        /// If not specified, no additional restrictions are applied.
        bool chatHasUsername;

        /// @brief Optional. Pass True to request a chat owned by the user. Otherwise, no additional restrictions are applied.
        bool chatIsCreated;

        /// @brief Optional. A JSON-serialized object listing the required administrator rights of the user in the chat.
        /// The rights must be a superset of bot_administrator_rights.
        /// If not specified, no additional restrictions are applied.
        Ptr<ChatAdministratorRights> userAdministratorRights;

        /// @brief Optional. A JSON-serialized object listing the required administrator rights of the bot in the chat.
        /// The rights must be a subset of user_administrator_rights.
        /// If not specified, no additional restrictions are applied.
        Ptr<ChatAdministratorRights> botAdministratorRights;

        /// @brief Optional. Pass True to request a chat with the bot as a member. Otherwise, no additional restrictions are applied.
        bool botIsMember;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "request_id", requestId);
          OBJECT_SERIALIZE_FIELD(json, "chat_is_channel", chatIsChannel);
          OBJECT_SERIALIZE_FIELD(json, "chat_is_forum", chatIsForum);
          OBJECT_SERIALIZE_FIELD(json, "chat_has_username", chatHasUsername);
          OBJECT_SERIALIZE_FIELD(json, "chat_is_created", chatIsCreated);
          OBJECT_SERIALIZE_FIELD_PTR(json, "user_administrator_rights", userAdministratorRights, nl::json::object());
          OBJECT_SERIALIZE_FIELD_PTR(json, "bot_administrator_rights", botAdministratorRights, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "bot_is_member", botIsMember);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
            OBJECT_DESERIALIZE_FIELD(json, "request_id", requestId, 0, false);
            OBJECT_DESERIALIZE_FIELD(json, "chat_is_channel", chatIsChannel, false, false);
            OBJECT_DESERIALIZE_FIELD(json, "chat_is_forum", chatIsForum, false, true);
            OBJECT_DESERIALIZE_FIELD(json, "chat_has_username", chatHasUsername, false, true);
            OBJECT_DESERIALIZE_FIELD(json, "chat_is_created", chatIsCreated, false, true);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "user_administrator_rights", userAdministratorRights, true);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "bot_administrator_rights", botAdministratorRights, true);
            OBJECT_DESERIALIZE_FIELD(json, "bot_is_member", botIsMember, false, true);
        }
    };
}