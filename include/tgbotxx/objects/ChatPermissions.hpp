#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief Describes actions that a non-administrator user is allowed to take in a chat.
    /// @ref https://core.telegram.org/bots/api#chatpermissions
    struct ChatPermissions {
      explicit ChatPermissions(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Optional. True, if the user is allowed to send text messages, contacts, invoices, locations and venues
      bool canSendMessages;

      /// @brief Optional. True, if the user is allowed to send audios
      bool canSendAudios;

      /// @brief Optional. True, if the user is allowed to send documents
      bool canSendDocuments;

      /// @brief Optional. True, if the user is allowed to send photos
      bool canSendPhotos;

      /// @brief Optional. True, if the user is allowed to send videos
      bool canSendVideos;

      /// @brief Optional. True, if the user is allowed to send video notes
      bool canSendVideoNotes;

      /// @brief Optional. True, if the user is allowed to send voice notes
      bool canSendVoiceNotes;

      /// @brief Optional. True, if the user is allowed to send polls
      bool canSendPolls;

      /// @brief Optional. True, if the user is allowed to send animations, games, stickers and use inline bots
      bool canSendOtherMessages;

      /// @brief Optional. True, if the user is allowed to add web page previews to their messages
      bool canAddWebPagePreviews;

      /// @brief Optional. True, if the user is allowed to change the chat title, photo and other settings. Ignored in public supergroups
      bool canChangeInfo;

      /// @brief Optional. True, if the user is allowed to invite new users to the chat
      bool canInviteUsers;

      /// @brief Optional. True, if the user is allowed to pin messages. Ignored in public supergroups
      bool canPinMessages;

      /// @brief Optional. True, if the user is allowed to create forum topics. If omitted defaults to the value of canPinMessages
      bool canManageTopics;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
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
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json &json) {
        OBJECT_DESERIALIZE_FIELD(json, "can_send_messages", canSendMessages, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_audios", canSendAudios, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_documents", canSendDocuments, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_photos", canSendPhotos, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_videos", canSendVideos, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_video_notes", canSendVideoNotes, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_voice_notes", canSendVoiceNotes, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_polls", canSendPolls, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_send_other_messages", canSendOtherMessages, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_add_web_page_previews", canAddWebPagePreviews, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_change_info", canChangeInfo, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_invite_users", canInviteUsers, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_pin_messages", canPinMessages, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "can_manage_topics", canManageTopics, false, true);
      }
    };
}