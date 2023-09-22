#pragma once
#include "Object.hpp"
#include <string>

namespace tgbotxx {
    /// @brief Base class of all bot commands scopes
    /// This object represents the scope to which bot commands are applied. Currently, the following 7 scopes are supported:
    ///    BotCommandScopeDefault
    ///    BotCommandScopeAllPrivateChats
    ///    BotCommandScopeAllGroupChats
    ///    BotCommandScopeAllChatAdministrators
    ///    BotCommandScopeChat
    ///    BotCommandScopeChatAdministrators
    ///    BotCommandScopeChatMember
    /// @ref https://core.telegram.org/bots/api#botcommandscope
    struct BotCommandScope {
        explicit BotCommandScope(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Scope type.
        std::string type;

        nl::json toJson() const {
          nl::json scope = nl::json::object();
          OBJECT_SERIALIZE_FIELD(scope, "type", type);
          return scope;
        }

        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "type", type, "");
        }
    };

    /// @brief Represents the default scope of bot commands. Default commands are used if no commands with a narrower
    /// scope are specified for the user.
    struct BotCommandScopeDefault : BotCommandScope {
        explicit BotCommandScopeDefault(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "default";
        }
    };

    /// @brief Represents the scope of bot commands, covering all private chats.
    struct BotCommandScopeAllPrivateChats : BotCommandScope {
        explicit BotCommandScopeAllPrivateChats(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "all_private_chats";
        }
    };

    /// @brief Represents the scope of bot commands, covering all group and supergroup chats.
    struct BotCommandScopeAllGroupChats : BotCommandScope {
        explicit BotCommandScopeAllGroupChats(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "all_group_chats";
        }
    };

    /// @brief Represents the scope of bot commands, covering all group and supergroup chat administrators.
    struct BotCommandScopeAllChatAdministrators : BotCommandScope {
        explicit BotCommandScopeAllChatAdministrators(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "all_chat_administrators";
        }
    };

    /// @brief Represents the scope of bot commands, covering a specific chat.
    struct BotCommandScopeChat : BotCommandScope {
        explicit BotCommandScopeChat(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "chat";
        }

        /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
        std::int64_t chatId;

        nl::json toJson() const {
          nl::json scope = nl::json::object();
          OBJECT_SERIALIZE_FIELD(scope, "type", type);
          OBJECT_SERIALIZE_FIELD(scope, "chat_id", chatId);
          return scope;
        }

        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "type", type, "");
          OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, -1);
        }
    };

    /// @brief Represents the scope of bot commands, covering all administrators of a specific group or supergroup chat.
    struct BotCommandScopeChatAdministrators : BotCommandScope {
        explicit BotCommandScopeChatAdministrators(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "chat_administrators";
        }

        /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
        std::int64_t chatId;

        nl::json toJson() const {
          return {};
        }
        void fromJson(const nl::json &json) {

        }

    };

    /// @brief Represents the scope of bot commands, covering a specific member of a group or supergroup chat.
    struct BotCommandScopeChatMember : BotCommandScope {
        explicit BotCommandScopeChatMember(const nl::json& json) : BotCommandScope(json) {
          BotCommandScope::type = "chat_member";
        }

        /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
        std::int64_t chatId;
        /// @brief Unique identifier of the target user
        std::int64_t userId;

        nl::json toJson() const {
          nl::json scope = nl::json::object();
          OBJECT_SERIALIZE_FIELD(scope, "type", type);
          OBJECT_SERIALIZE_FIELD(scope, "chat_id", chatId);
          OBJECT_SERIALIZE_FIELD(scope, "user_id", userId);
          return scope;
        }

        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "type", type, "");
          OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, -1);
          OBJECT_DESERIALIZE_FIELD(json, "user_id", userId, -1);
        }

    };
}