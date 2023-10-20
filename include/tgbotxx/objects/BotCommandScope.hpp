#pragma once
#include <tgbotxx/objects/Object.hpp>

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
      BotCommandScope() = default;
      explicit BotCommandScope(const nl::json& json) {
        _fromJson(json);
      }
      virtual ~BotCommandScope() = default;

      /// @brief Scope type.
      std::string type;

      virtual nl::json toJson() const {
        nl::json scope = nl::json::object();
        OBJECT_SERIALIZE_FIELD(scope, "type", type);
        return scope;
      }

      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      }

    private:
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };

  /// @brief Represents the default scope of bot commands. Default commands are used if no commands with a narrower
  /// scope are specified for the user.
  struct BotCommandScopeDefault : BotCommandScope {
      BotCommandScopeDefault() {
        BotCommandScope::type = "default";
      }
      explicit BotCommandScopeDefault(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "default";
      }
  };

  /// @brief Represents the scope of bot commands, covering all private chats.
  struct BotCommandScopeAllPrivateChats : BotCommandScope {
      BotCommandScopeAllPrivateChats() {
        BotCommandScope::type = "all_private_chats";
      }
      explicit BotCommandScopeAllPrivateChats(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "all_private_chats";
      }
  };

  /// @brief Represents the scope of bot commands, covering all group and supergroup chats.
  struct BotCommandScopeAllGroupChats : BotCommandScope {
      BotCommandScopeAllGroupChats() {
        BotCommandScope::type = "all_group_chats";
      }
      explicit BotCommandScopeAllGroupChats(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "all_group_chats";
      }
  };

  /// @brief Represents the scope of bot commands, covering all group and supergroup chat administrators.
  struct BotCommandScopeAllChatAdministrators : BotCommandScope {
      BotCommandScopeAllChatAdministrators() {
        BotCommandScope::type = "all_chat_administrators";
      }
      explicit BotCommandScopeAllChatAdministrators(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "all_chat_administrators";
      }
  };

  /// @brief Represents the scope of bot commands, covering a specific chat.
  struct BotCommandScopeChat : BotCommandScope {
      BotCommandScopeChat() {
        BotCommandScope::type = "chat";
      }
      explicit BotCommandScopeChat(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "chat";
      }

      /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
      std::int64_t chatId{};

      nl::json toJson() const override {
        nl::json scope = BotCommandScope::toJson();
        OBJECT_SERIALIZE_FIELD(scope, "chat_id", chatId);
        return scope;
      }

      void fromJson(const nl::json& json) override {
        BotCommandScope::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, -1, false);
      }
  };

  /// @brief Represents the scope of bot commands, covering all administrators of a specific group or supergroup chat.
  struct BotCommandScopeChatAdministrators : BotCommandScope {
      BotCommandScopeChatAdministrators() {
        BotCommandScope::type = "chat_administrators";
      }
      explicit BotCommandScopeChatAdministrators(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "chat_administrators";
      }

      /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
      std::int64_t chatId{};

      nl::json toJson() const override {
        nl::json scope = BotCommandScope::toJson();
        OBJECT_SERIALIZE_FIELD(scope, "chat_id", chatId);
        return scope;
      }

      void fromJson(const nl::json& json) override {
        BotCommandScope::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, -1, false);
      }
  };

  /// @brief Represents the scope of bot commands, covering a specific member of a group or supergroup chat.
  struct BotCommandScopeChatMember : BotCommandScope {
      BotCommandScopeChatMember() {
        BotCommandScope::type = "chat_member";
      }
      explicit BotCommandScopeChatMember(const nl::json& json) : BotCommandScope(json) {
        BotCommandScope::type = "chat_member";
      }

      /// @brief Unique identifier for the target chat or username of the target supergroup (in the format @supergroupusername)
      std::int64_t chatId{};
      /// @brief Unique identifier of the target user
      std::int64_t userId{};

      nl::json toJson() const override {
        nl::json scope = BotCommandScope::toJson();
        OBJECT_SERIALIZE_FIELD(scope, "chat_id", chatId);
        OBJECT_SERIALIZE_FIELD(scope, "user_id", userId);
        return scope;
      }

      void fromJson(const nl::json& json) override {
        BotCommandScope::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, -1, false);
        OBJECT_DESERIALIZE_FIELD(json, "user_id", userId, -1, false);
      }
  };
}