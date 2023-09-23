#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
    /// @brief Represents an invite link for a chat.
    /// @ref https://core.telegram.org/bots/api#chatinvitelink
    struct ChatInviteLink {
      explicit ChatInviteLink(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The invite link. If the link was created by another chat administrator, then the second part of the link will be replaced with “…”.
      std::string inviteLink;

      /// @brief Creator of the link
      Ptr<User> creator;

      /// @brief True, if users joining the chat via the link need to be approved by chat administrators
      bool createsJoinRequest;

      /// @brief True, if the link is primary
      bool isPrimary;

      /// @brief True, if the link is revoked
      bool isRevoked;

      /// @brief Optional. Invite link name
      std::string name;

      /// @brief Optional. Point in time (Unix timestamp) when the link will expire or has been expired
      std::time_t expireDate;

      /// @brief Optional. The maximum number of users that can be members of the chat simultaneously after joining the chat via this invite link; 1-99999
      std::int32_t memberLimit;

      /// @brief Optional. Number of pending join requests created using this link
      std::int32_t pendingJoinRequestCount;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "invite_link", inviteLink);
        OBJECT_SERIALIZE_FIELD_PTR(json, "creator", creator, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "creates_join_request", createsJoinRequest);
        OBJECT_SERIALIZE_FIELD(json, "is_primary", isPrimary);
        OBJECT_SERIALIZE_FIELD(json, "is_revoked", isRevoked);
        OBJECT_SERIALIZE_FIELD(json, "name", name);
        OBJECT_SERIALIZE_FIELD(json, "expire_date", expireDate);
        OBJECT_SERIALIZE_FIELD(json, "member_limit", memberLimit);
        OBJECT_SERIALIZE_FIELD(json, "pending_join_request_count", pendingJoinRequestCount);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json &json) {
        OBJECT_DESERIALIZE_FIELD(json, "invite_link", inviteLink, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "creator", creator, nl::json::object());
        OBJECT_DESERIALIZE_FIELD(json, "creates_join_request", createsJoinRequest, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "is_primary", isPrimary, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "is_revoked", isRevoked, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "name", name, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "expire_date", expireDate, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "member_limit", memberLimit, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "pending_join_request_count", pendingJoinRequestCount, 0, true);
      }
    };
}