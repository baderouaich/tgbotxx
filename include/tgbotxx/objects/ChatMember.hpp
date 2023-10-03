#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief The base class of all chat members objects.
  /// This object contains information about one member of a chat. Currently, the following 6 types of chat members are supported:
  /// ChatMemberOwner
  /// ChatMemberAdministrator
  /// ChatMemberMember
  /// ChatMemberRestricted
  /// ChatMemberLeft
  /// ChatMemberBanned
  /// @ref https://core.telegram.org/bots/api#chatmember
  struct ChatMember {
      ChatMember() = default;
      explicit ChatMember(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The member's status in the chat
      std::string status;

      /// @brief Information about the user
      Ptr<User> user;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "status", status);
        OBJECT_SERIALIZE_FIELD_PTR(json, "user", user, nl::json::object());
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "status", status, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
      }
  };

  /// @brief Represents a chat member that owns the chat and has all administrator privileges.
  /// @ref https://core.telegram.org/bots/api#chatmemberowner
  struct ChatMemberOwner : ChatMember {
      ChatMemberOwner() = default;
      explicit ChatMemberOwner(const nl::json& json) : ChatMember(json) {
        fromJson(json);
        ChatMember::status = "creator";
      }

      /// @brief True, if the user's presence in the chat is hidden
      bool isAnonymous{};

      /// @brief Optional. Custom title for this user
      std::string customTitle;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = ChatMember::toJson();
        OBJECT_SERIALIZE_FIELD(json, "is_anonymous", isAnonymous);
        OBJECT_SERIALIZE_FIELD(json, "custom_title", customTitle);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        ChatMember::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "is_anonymous", isAnonymous, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "custom_title", customTitle, "", true);
      }
  };


  /// @brief Represents a chat member that has some additional privileges.
  /// @ref https://core.telegram.org/bots/api#chatmemberadministrator
  struct ChatMemberAdministrator : ChatMember {
      ChatMemberAdministrator() = default;
      explicit ChatMemberAdministrator(const nl::json& json) : ChatMember(json) {
        fromJson(json);
        ChatMember::status = "administrator";
      }

      /// @brief True, if the bot is allowed to edit administrator privileges of that user
      bool canBeEdited{};

      /// @brief True, if the user's presence in the chat is hidden
      bool isAnonymous{};

      /// @brief True, if the administrator can access the chat event log, chat statistics, boost list in channels,
      /// message statistics in channels, see channel members, see anonymous administrators in supergroups and ignore slow mode.
      /// Implied by any other administrator privilege
      bool canManageChat{};

      /// @brief True, if the administrator can delete messages of other users
      bool canDeleteMessages{};

      /// @brief True, if the administrator can manage video chats
      bool canManageVideoChats{};

      /// @brief True, if the administrator can restrict, ban or unban chat members
      bool canRestrictMembers{};

      /// @brief True, if the administrator can add new administrators with a subset of their own privileges or demote administrators that they have promoted,
      /// directly or indirectly (promoted by administrators that were appointed by the user)
      bool canPromoteMembers{};

      /// @brief True, if the user is allowed to change the chat title, photo and other settings
      bool canChangeInfo{};

      /// @brief True, if the user is allowed to invite new users to the chat
      bool canInviteUsers{};

      /// @brief Optional. True, if the administrator can post messages in the channel; channels only
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

      /// @brief Optional. Custom title for this user
      std::string customTitle;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = ChatMember::toJson();
        OBJECT_SERIALIZE_FIELD(json, "can_be_edited", canBeEdited);
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
        OBJECT_SERIALIZE_FIELD(json, "custom_title", customTitle);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        ChatMember::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "can_be_edited", canBeEdited, false, false);
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
        OBJECT_DESERIALIZE_FIELD(json, "custom_title", customTitle, "", true);
      }
  };


  /// @brief Represents a chat member that has no additional privileges or restrictions.
  /// @ref https://core.telegram.org/bots/api#chatmembermember
  struct ChatMemberMember : ChatMember {
      ChatMemberMember() = default;
      explicit ChatMemberMember(const nl::json& json) : ChatMember(json) {
        ChatMember::status = "member";
      }
  };


  /// @brief Represents a chat member that is under certain restrictions in the chat. Supergroups only.
  /// @ref https://core.telegram.org/bots/api#chatmemberrestricted
  struct ChatMemberRestricted : ChatMember {
      ChatMemberRestricted() = default;
      explicit ChatMemberRestricted(const nl::json& json) : ChatMember(json) {
        fromJson(json);
        ChatMember::status = "restricted";
      }

      /// @brief True, if the user is a member of the chat at the moment of the request
      bool isMember{};

      /// @brief True, if the user is allowed to send text messages, contacts, invoices, locations and venues
      bool canSendMessages{};

      /// @brief True, if the user is allowed to send audios
      bool canSendAudios{};

      /// @brief True, if the user is allowed to send documents
      bool canSendDocuments{};

      /// @brief True, if the user is allowed to send photos
      bool canSendPhotos{};

      /// @brief True, if the user is allowed to send videos
      bool canSendVideos{};

      /// @brief True, if the user is allowed to send video notes
      bool canSendVideoNotes{};

      /// @brief True, if the user is allowed to send voice notes
      bool canSendVoiceNotes{};

      /// @brief True, if the user is allowed to send polls
      bool canSendPolls{};

      /// @brief True, if the user is allowed to send animations, games, stickers and use inline bots
      bool canSendOtherMessages{};

      /// @brief True, if the user is allowed to add web page previews to their messages
      bool canAddWebPagePreviews{};

      /// @brief True, if the user is allowed to change the chat title, photo and other settings
      bool canChangeInfo{};

      /// @brief True, if the user is allowed to invite new users to the chat
      bool canInviteUsers{};

      /// @brief True, if the user is allowed to pin messages
      bool canPinMessages{};

      /// @brief True, if the user is allowed to create forum topics
      bool canManageTopics{};

      /// @brief Date when restrictions will be lifted for this user; Unix time. If 0, then the user is restricted forever
      std::time_t untilDate{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = ChatMember::toJson();
        OBJECT_SERIALIZE_FIELD(json, "is_member", isMember);
        OBJECT_SERIALIZE_FIELD(json, "can_send_messages", canSendMessages);
        OBJECT_SERIALIZE_FIELD(json, "can_send_audios", canSendAudios);
        OBJECT_SERIALIZE_FIELD(json, "can_send_documents", canSendDocuments);
        OBJECT_SERIALIZE_FIELD(json, "can_send_photos", canSendPhotos);
        OBJECT_SERIALIZE_FIELD(json, "can_send_videos", canSendVideos);
        OBJECT_SERIALIZE_FIELD(json, "can_send_video_notes", canSendVideoNotes);
        OBJECT_SERIALIZE_FIELD(json, "can_send_voice_notes", canSendVoiceNotes);
        OBJECT_SERIALIZE_FIELD(json, "can_send_polls", canSendPolls);
        OBJECT_SERIALIZE_FIELD(json, "can_send_other_messages", canSendOtherMessages);
        OBJECT_SERIALIZE_FIELD(json, "can_add_web_page_previews", canAddWebPagePreviews);
        OBJECT_SERIALIZE_FIELD(json, "can_change_info", canChangeInfo);
        OBJECT_SERIALIZE_FIELD(json, "can_invite_users", canInviteUsers);
        OBJECT_SERIALIZE_FIELD(json, "can_pin_messages", canPinMessages);
        OBJECT_SERIALIZE_FIELD(json, "can_manage_topics", canManageTopics);
        OBJECT_SERIALIZE_FIELD(json, "until_date", untilDate);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        ChatMember::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "is_member", isMember, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_messages", canSendMessages, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_audios", canSendAudios, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_documents", canSendDocuments, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_photos", canSendPhotos, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_videos", canSendVideos, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_video_notes", canSendVideoNotes, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_voice_notes", canSendVoiceNotes, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_polls", canSendPolls, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_other_messages", canSendOtherMessages, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_add_web_page_previews", canAddWebPagePreviews, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_change_info", canChangeInfo, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_invite_users", canInviteUsers, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_pin_messages", canPinMessages, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "can_manage_topics", canManageTopics, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "until_date", untilDate, 0, false);
      }
  };


  /// @brief Represents a chat member that isn't currently a member of the chat, but may join it themselves.
  /// @ref https://core.telegram.org/bots/api#chatmemberleft
  struct ChatMemberLeft : ChatMember {
      ChatMemberLeft() = default;
      explicit ChatMemberLeft(const nl::json& json) : ChatMember(json) {
        ChatMember::status = "left";
      }
  };


  /// @brief Represents a chat member that was banned in the chat and can't return to the chat or view chat messages.
  /// @ref https://core.telegram.org/bots/api#chatmemberbanned
  struct ChatMemberBanned : ChatMember {
      ChatMemberBanned() = default;
      explicit ChatMemberBanned(const nl::json& json) : ChatMember(json) {
        ChatMember::status = "left";
      }

      /// @brief Date when restrictions will be lifted for this user; Unix time. If 0, then the user is banned forever
      std::time_t untilDate{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = ChatMember::toJson();
        OBJECT_SERIALIZE_FIELD(json, "until_date", untilDate);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        ChatMember::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "until_date", untilDate, 0, false);
      }
  };

}