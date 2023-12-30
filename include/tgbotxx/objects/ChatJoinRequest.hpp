#pragma once
#include <tgbotxx/objects/ChatInviteLink.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
// TODO: circular include ? Chat ~ this
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief Represents a join request sent to a chat.
  /// @ref https://core.telegram.org/bots/api#chatjoinrequest
  struct ChatJoinRequest {
      ChatJoinRequest() = default;
      explicit ChatJoinRequest(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Chat to which the request was sent
      Ptr<Chat> chat;

      /// @brief User that sent the join request
      Ptr<User> from;

      /// @brief Identifier of a private chat with the user who sent the join request. This number may have more
      /// than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
      /// But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
      /// The bot can use this identifier for 24 hours to send messages until the join request is processed, assuming no other administrator contacted the user.
      std::int64_t userChatId{};

      /// @brief Date the request was sent in Unix time
      std::time_t date{};

      /// @brief Optional. Bio of the user.
      std::string bio;

      /// @brief Optional. Chat invite link that was used by the user to send the join request
      Ptr<ChatInviteLink> inviteLink;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
        OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
        OBJECT_SERIALIZE_FIELD(json, "user_chat_id", userChatId);
        OBJECT_SERIALIZE_FIELD(json, "date", date);
        OBJECT_SERIALIZE_FIELD(json, "bio", bio);
        OBJECT_SERIALIZE_FIELD_PTR(json, "invite_link", inviteLink);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
        OBJECT_DESERIALIZE_FIELD(json, "user_chat_id", userChatId, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "bio", bio, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "invite_link", inviteLink, true);
      }
  };
}