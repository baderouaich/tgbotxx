#pragma once
#include <tgbotxx/objects/Object.hpp>
// TODO: circular include ? Chat and here
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/User.hpp>
//
#include <tgbotxx/objects/ChatInviteLink.hpp>
#include <tgbotxx/objects/ChatMember.hpp>

namespace tgbotxx {
  /// @brief This object represents changes in the status of a chat member.
  /// @ref https://core.telegram.org/bots/api#chatmemberupdated
  struct ChatMemberUpdated {
      ChatMemberUpdated() = default;
      explicit ChatMemberUpdated(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Chat the user belongs to
      Ptr<Chat> chat;

      /// @brief Performer of the action, which resulted in the change
      Ptr<User> from;

      /// @brief Date the change was done in Unix time
      std::time_t date{};

      /// @brief Previous information about the chat member
      Ptr<ChatMember> oldChatMember;

      /// @brief New information about the chat member
      Ptr<ChatMember> newChatMember;

      /// @brief Optional. Chat invite link, which was used by the user to join the chat; for joining by invite link events only.
      Ptr<ChatInviteLink> inviteLink;

      /// @brief Optional. True, if the user joined the chat via a chat folder invite link
      bool viaChatFolderInviteLink{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat, nl::json::object());
        OBJECT_SERIALIZE_FIELD_PTR(json, "from", from, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "date", date);
        OBJECT_SERIALIZE_FIELD_PTR(json, "old_chat_member", oldChatMember, nl::json::object());
        OBJECT_SERIALIZE_FIELD_PTR(json, "new_chat_member", newChatMember, nl::json::object());
        OBJECT_SERIALIZE_FIELD_PTR(json, "invite_link", inviteLink, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "via_chat_folder_invite_link", viaChatFolderInviteLink);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
        OBJECT_DESERIALIZE_FIELD(json, "date", date, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "old_chat_member", oldChatMember, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "new_chat_member", newChatMember, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "invite_link", inviteLink, true);
        OBJECT_DESERIALIZE_FIELD(json, "via_chat_folder_invite_link", viaChatFolderInviteLink, false, true);
      }
  };
}
