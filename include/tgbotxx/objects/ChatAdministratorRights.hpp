#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Represents the rights of an administrator in a chat.
  /// @ref https://core.telegram.org/bots/api#chatadministratorrights
  struct ChatAdministratorRights {
    ChatAdministratorRights() = default;
    explicit ChatAdministratorRights(const nl::json& json) {
      fromJson(json);
    }

    /// @brief True, if the user's presence in the chat is hidden
    bool isAnonymous{};

    /// @brief True, if the administrator can access the chat event log, boost list in channels, see channel members,
    /// report spam messages, see anonymous administrators in supergroups and ignore slow mode.
    /// Implied by any other administrator privilege
    bool canManageChat{};

    /// @brief True, if the administrator can delete messages of other users
    bool canDeleteMessages{};

    /// @brief True, if the administrator can manage video chats
    bool canManageVideoChats{};

    /// @brief True, if the administrator can restrict, ban or unban chat members, or access supergroup statistics
    bool canRestrictMembers{};

    /// @brief True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted,
    /// directly or indirectly (promoted by administrators that were appointed by the user)
    bool canPromoteMembers{};

    /// @brief True, if the user is allowed to change the chat title, photo and other settings
    bool canChangeInfo{};

    /// @brief True, if the user is allowed to invite new users to the chat
    bool canInviteUsers{};

    /// @brief Optional. True, if the administrator can post messages in the channel, or access channel statistics; channels only
    bool canPostMessages{};

    /// @brief Optional. True, if the administrator can edit messages of other users and can pin messages; channels only
    bool canEditMessages{};

    /// @brief Optional. True, if the user is allowed to pin messages; groups and supergroups only
    bool canPinMessages{};

    /// @brief Optional. True, if the administrator can post stories in the channel; channels only
    bool canPostStories{};

    /// @brief Optional. True, if the administrator can edit stories posted by other users; channels only
    bool canEditStories{};

    /// @brief Optional. True, if the administrator can delete stories posted by other users; channels only
    bool canDeleteStories{};

    /// @brief Optional. True, if the user is allowed to create, rename, close, and reopen forum topics; supergroups only
    bool canManageTopics{};

    /// @brief Optional. True, if the administrator can manage direct messages of the channel and decline suggested posts; for channels only
    bool canManageDirectMessages{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "is_anonymous", isAnonymous);
      OBJECT_SERIALIZE_FIELD(json, "can_manage_chat", canManageChat);
      OBJECT_SERIALIZE_FIELD(json, "can_delete_messages", canDeleteMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_manage_video_chats", canManageVideoChats);
      OBJECT_SERIALIZE_FIELD(json, "can_restrict_members", canRestrictMembers);
      OBJECT_SERIALIZE_FIELD(json, "can_promote_members", canPromoteMembers);
      OBJECT_SERIALIZE_FIELD(json, "can_change_info", canChangeInfo);
      OBJECT_SERIALIZE_FIELD(json, "can_invite_users", canInviteUsers);
      OBJECT_SERIALIZE_FIELD(json, "can_post_messages", canPostMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_messages", canEditMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_pin_messages", canPinMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_post_stories", canPostStories);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_stories", canEditStories);
      OBJECT_SERIALIZE_FIELD(json, "can_delete_stories", canDeleteStories);
      OBJECT_SERIALIZE_FIELD(json, "can_manage_topics", canManageTopics);
      OBJECT_SERIALIZE_FIELD(json, "can_manage_direct_messages", canManageDirectMessages);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "is_anonymous", isAnonymous, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_manage_chat", canManageChat, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_delete_messages", canDeleteMessages, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_manage_video_chats", canManageVideoChats, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_restrict_members", canRestrictMembers, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_promote_members", canPromoteMembers, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_change_info", canChangeInfo, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_invite_users", canInviteUsers, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "can_post_messages", canPostMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_messages", canEditMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_pin_messages", canPinMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_post_stories", canPostStories, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_stories", canEditStories, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_delete_stories", canDeleteStories, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_manage_topics", canManageTopics, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_manage_direct_messages", canManageDirectMessages, false, true);
    }
  };
}