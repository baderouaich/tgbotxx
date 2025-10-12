#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {

  /// @brief Represents the rights of a business bot.
  /// @ref https://core.telegram.org/bots/api#businessbotrights
  struct BusinessBotRights {
    BusinessBotRights() = default;
    explicit BusinessBotRights(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. True, if the bot can send and edit messages in private chats that had incoming messages in the last 24 hours
    bool canReply{};

    /// @brief Optional. True, if the bot can mark incoming private messages as read
    bool canReadMessages{};

    /// @brief Optional. True, if the bot can delete messages sent by the bot
    bool canDeleteSentMessages{};

    /// @brief Optional. True, if the bot can delete all private messages in managed chats
    bool canDeleteAllMessages{};

    /// @brief Optional. True, if the bot can edit the first and last name of the business account
    bool canEditName{};

    /// @brief Optional. True, if the bot can edit the bio of the business account
    bool canEditBio{};

    /// @brief Optional. True, if the bot can edit the profile photo of the business account
    bool canEditProfilePhoto{};

    /// @brief Optional. True, if the bot can edit the username of the business account
    bool canEditUsername{};

    /// @brief Optional. True, if the bot can change the privacy settings pertaining to gifts for the business account
    bool canChangeGiftSettings{};

    /// @brief Optional. True, if the bot can view gifts and the amount of Telegram Stars owned by the business account
    bool canViewGiftsAndStars{};

    /// @brief Optional. True, if the bot can convert regular gifts owned by the business account to Telegram Stars
    bool canConvertGiftsToStars{};

    /// @brief Optional. True, if the bot can transfer and upgrade gifts owned by the business account
    bool canTransferAndUpgradeGifts{};

    /// @brief Optional. True, if the bot can transfer Telegram Stars received by the business account to its own account, or use them to upgrade and transfer gifts
    bool canTransferStars{};

    /// @brief Optional. True, if the bot can post, edit, and delete stories on behalf of the business account
    bool canManageStories{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "can_reply", canReply);
      OBJECT_SERIALIZE_FIELD(json, "can_read_messages", canReadMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_delete_sent_messages", canDeleteSentMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_delete_all_messages", canDeleteAllMessages);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_name", canEditName);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_bio", canEditBio);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_profile_photo", canEditProfilePhoto);
      OBJECT_SERIALIZE_FIELD(json, "can_edit_username", canEditUsername);
      OBJECT_SERIALIZE_FIELD(json, "can_change_gift_settings", canChangeGiftSettings);
      OBJECT_SERIALIZE_FIELD(json, "can_view_gifts_and_stars", canViewGiftsAndStars);
      OBJECT_SERIALIZE_FIELD(json, "can_convert_gifts_to_stars", canConvertGiftsToStars);
      OBJECT_SERIALIZE_FIELD(json, "can_transfer_and_upgrade_gifts", canTransferAndUpgradeGifts);
      OBJECT_SERIALIZE_FIELD(json, "can_transfer_stars", canTransferStars);
      OBJECT_SERIALIZE_FIELD(json, "can_manage_stories", canManageStories);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "can_reply", canReply, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_read_messages", canReadMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_delete_sent_messages", canDeleteSentMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_delete_all_messages", canDeleteAllMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_name", canEditName, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_bio", canEditBio, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_profile_photo", canEditProfilePhoto, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_edit_username", canEditUsername, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_change_gift_settings", canChangeGiftSettings, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_view_gifts_and_stars", canViewGiftsAndStars, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_convert_gifts_to_stars", canConvertGiftsToStars, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_transfer_and_upgrade_gifts", canTransferAndUpgradeGifts, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_transfer_stars", canTransferStars, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "can_manage_stories", canManageStories, false, true);
    }
  };

}
