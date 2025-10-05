#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ChatAdministratorRights.hpp>

namespace tgbotxx {
  /// @brief This object defines the criteria used to request a suitable chat.
  /// Information about the selected chat will be shared with the bot when the corresponding button is pressed.
  /// The bot will be granted requested rights in the chat if appropriate.
  /// @ref https://core.telegram.org/bots/api#keyboardbuttonrequestchat
  struct KeyboardButtonRequestChat {
    KeyboardButtonRequestChat() = default;
    explicit KeyboardButtonRequestChat(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Signed 32-bit identifier of the request, which will be received back in the ChatShared object.
    /// Must be unique within the message
    std::int32_t requestId{};

    /// @brief Pass True to request a channel chat, pass False to request a group or a supergroup chat.
    bool chatIsChannel{};

    /// @brief Optional. Pass True to request a forum supergroup, pass False to request a non-forum chat.
    bool chatIsForum{};

    /// @brief Optional. Pass True to request a supergroup or a channel with a username, pass False to request a chat without a username.
    bool chatHasUsername{};

    /// @brief Optional. Pass True to request a chat owned by the user.
    bool chatIsCreated{};

    /// @brief Optional. A JSON-serialized object listing the required administrator rights of the user in the chat.
    Ptr<ChatAdministratorRights> userAdministratorRights;

    /// @brief Optional. A JSON-serialized object listing the required administrator rights of the bot in the chat.
    Ptr<ChatAdministratorRights> botAdministratorRights;

    /// @brief Optional. Pass True to request a chat with the bot as a member.
    bool botIsMember{};

    /// @brief Optional. Pass True to request the chat's title.
    bool requestTitle{};

    /// @brief Optional. Pass True to request the chat's username.
    bool requestUsername{};

    /// @brief Optional. Pass True to request the chat's photo.
    bool requestPhoto{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "request_id", requestId);
      OBJECT_SERIALIZE_FIELD(json, "chat_is_channel", chatIsChannel);
      OBJECT_SERIALIZE_FIELD(json, "chat_is_forum", chatIsForum);
      OBJECT_SERIALIZE_FIELD(json, "chat_has_username", chatHasUsername);
      OBJECT_SERIALIZE_FIELD(json, "chat_is_created", chatIsCreated);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user_administrator_rights", userAdministratorRights);
      OBJECT_SERIALIZE_FIELD_PTR(json, "bot_administrator_rights", botAdministratorRights);
      OBJECT_SERIALIZE_FIELD(json, "bot_is_member", botIsMember);
      OBJECT_SERIALIZE_FIELD(json, "request_title", requestTitle);
      OBJECT_SERIALIZE_FIELD(json, "request_username", requestUsername);
      OBJECT_SERIALIZE_FIELD(json, "request_photo", requestPhoto);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "request_id", requestId, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "chat_is_channel", chatIsChannel, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "chat_is_forum", chatIsForum, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "chat_has_username", chatHasUsername, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "chat_is_created", chatIsCreated, false, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user_administrator_rights", userAdministratorRights, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "bot_administrator_rights", botAdministratorRights, true);
      OBJECT_DESERIALIZE_FIELD(json, "bot_is_member", botIsMember, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_title", requestTitle, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_username", requestUsername, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "request_photo", requestPhoto, false, true);
    }
  };
}