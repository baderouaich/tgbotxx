#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief This object describes the origin of a message. It can be one of:
  /// - MessageOriginUser
  /// - MessageOriginHiddenUser
  /// - MessageOriginChat
  /// - MessageOriginChannel
  /// @ref https://core.telegram.org/bots/api#messageorigin
  struct MessageOrigin {
    MessageOrigin() = default;
    explicit MessageOrigin(const nl::json& json) {
      _fromJson(json);
    }
    virtual ~MessageOrigin() = default;

    /// @brief Type of the message origin, one of "user", "hidden_user", "chat" or "channel"
    std::string type;

    /// @brief Date the message was sent originally in Unix time
    std::time_t date{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      OBJECT_SERIALIZE_FIELD(json, "date", date);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
    }

  private:
    void _fromJson(const nl::json& json) {
      fromJson(json);
    }
  };

  /// @brief The message was originally sent by a known user.
  /// @ref https://core.telegram.org/bots/api#messageoriginuser
  struct MessageOriginUser : MessageOrigin {
    MessageOriginUser() {
      MessageOrigin::type = "user";
    }
    explicit MessageOriginUser(const nl::json& json) : MessageOrigin(json) {
      MessageOrigin::type = "user";
    }

    /// @brief User that sent the message originally
    Ptr<User> senderUser;

    nl::json toJson() const override {
      nl::json json = MessageOrigin::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "sender_user", senderUser);
      return json;
    }

    void fromJson(const nl::json& json) override {
      MessageOrigin::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_user", senderUser, false);
    }
  };


  /// @brief The message was originally sent by an unknown user.
  /// @ref https://core.telegram.org/bots/api#messageoriginhiddenuser
  struct MessageOriginHiddenUser : MessageOrigin {
    MessageOriginHiddenUser() {
      MessageOrigin::type = "hidden_user";
    }
    explicit MessageOriginHiddenUser(const nl::json& json) : MessageOrigin(json) {
      MessageOrigin::type = "hidden_user";
    }

    /// @brief Name of the user that sent the message originally
    std::string senderUserName;

    nl::json toJson() const override {
      nl::json json = MessageOrigin::toJson();
      OBJECT_SERIALIZE_FIELD(json, "sender_user_name", senderUserName);
      return json;
    }

    void fromJson(const nl::json& json) override {
      MessageOrigin::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "sender_user_name", senderUserName, "", false);
    }
  };


  /// @brief The message was originally sent on behalf of a chat to a group chat.
  /// @ref https://core.telegram.org/bots/api#messageoriginchat
  struct MessageOriginChat : MessageOrigin {
    MessageOriginChat() {
      MessageOrigin::type = "chat";
    }
    explicit MessageOriginChat(const nl::json& json) : MessageOrigin(json) {
      MessageOrigin::type = "chat";
    }

    /// @brief Chat that sent the message originally
    Ptr<Chat> senderChat;

    /// @brief Optional. For messages originally sent by an anonymous chat administrator, original message author signature
    std::string authorSignature;

    nl::json toJson() const override {
      nl::json json = MessageOrigin::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "sender_chat", senderChat);
      OBJECT_SERIALIZE_FIELD(json, "author_signature", authorSignature);
      return json;
    }

    void fromJson(const nl::json& json) override {
      MessageOrigin::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sender_chat", senderChat, false);
      OBJECT_DESERIALIZE_FIELD(json, "author_signature", authorSignature, "", true);
    }
  };

  /// @brief The message was originally sent to a channel chat.
  /// @ref https://core.telegram.org/bots/api#messageoriginchannel
  struct MessageOriginChannel : MessageOrigin {
    MessageOriginChannel() {
      MessageOrigin::type = "channel";
    }
    explicit MessageOriginChannel(const nl::json& json) : MessageOrigin(json) {
      MessageOrigin::type = "channel";
    }

    /// @brief Channel chat to which the message was originally sent
    Ptr<Chat> chat;

    /// @brief Unique message identifier inside the chat
    std::int32_t messageId{};

    /// @brief Optional. Signature of the original post author
    std::string authorSignature;

    nl::json toJson() const override {
      nl::json json = MessageOrigin::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
      OBJECT_SERIALIZE_FIELD(json, "author_signature", authorSignature);
      return json;
    }

    void fromJson(const nl::json& json) override {
      MessageOrigin::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "author_signature", authorSignature, "", true);
    }
  };
}