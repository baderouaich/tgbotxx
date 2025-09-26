#pragma once
#include <tgbotxx/objects/ChatLocation.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/ChatPhoto.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ReactionType.hpp>

namespace tgbotxx {
  /// @brief This object represents a chat.
  /// @ref https://core.telegram.org/bots/api#chat
  struct Chat {
    Chat() = default;
    explicit Chat(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier for this chat.
    /// @note This number may have more than 32 significant bits and some programming languages may have
    /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
    /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
    std::int64_t id{};

    /// @brief Enum of possible types of Type.
    enum class Type : std::uint8_t {
      Private = 0,
      Group,
      Supergroup,
      Channel
    };
    /// @brief Converts enum Type to a string
    static std::optional<std::string> TypeToString(const Type type) noexcept {
      if (type == Type::Private) return "private";
      if (type == Type::Group) return "group";
      if (type == Type::Supergroup) return "supergroup";
      if (type == Type::Channel) return "channel";
      return std::nullopt;
    }
    /// @brief Converts string to an enum Type
    static std::optional<Type> StringToType(const std::string& str) noexcept {
      if (str == "private") return Type::Private;
      if (str == "group") return Type::Group;
      if (str == "supergroup") return Type::Supergroup;
      if (str == "channel") return Type::Channel;
      return std::nullopt;
    }

    /// @brief Type of chat, can be either “private”, “group”, “supergroup” or “channel”
    Type type{};

    /// @brief Optional. Title, for supergroups, channels and group chats
    std::string title;

    /// @brief Optional. Username, for private chats, supergroups and channels if available
    std::string username;

    /// @brief Optional. First name of the other party in a private chat
    std::string firstName;

    /// @brief Optional. Last name of the other party in a private chat
    std::string lastName;

    /// @brief Optional. True, if the supergroup chat is a forum (has topics enabled)
    /// @link topics https://telegram.org/blog/topics-in-groups-collectible-usernames#topics-in-groups @endlink
    bool isForum{};

    /// @brief Optional. Chat photo. Returned only in getChat.
    Ptr<ChatPhoto> photo;

    /// @brief Optional. If non-empty, the list of all active chat usernames; for private chats, supergroups and channels. Returned only in getChat.
    std::vector<std::string> activeUsernames;

    /// @brief Optional. List of available reactions allowed in the chat. If omitted, then all emoji reactions are allowed. Returned only in getChat.
    std::vector<Ptr<ReactionType>> availableReactions;

    /// @brief Optional. Identifier of the accent color for the chat name and backgrounds of the chat photo, reply header, and link preview.
    /// See [accent colors](https://core.telegram.org/bots/API#accent-colors) for more details. Returned only in getChat. Always returned in getChat.
    std::int32_t accentColorId{};

    /// @brief Optional. Custom emoji identifier of emoji chosen by the chat for the reply header and link preview background. Returned only in getChat.
    std::string backgroundCustomEmojiId;

    /// @brief Optional. Identifier of the accent color for the chat's profile background. See profile accent colors for more details. Returned only in getChat.
    std::int32_t profileAccentColorId{};

    /// @brief Optional. Custom emoji identifier of the emoji chosen by the chat for its profile background. Returned only in getChat.
    std::string profileBackgroundCustomEmojiId;

    /// @brief Optional. Custom emoji identifier of emoji status of the other party in a private chat. Returned only in getChat.
    /// @link getChat https://core.telegram.org/bots/api#getchat @endlink
    std::string emojiStatusCustomEmojiId;

    /// @brief Optional. Expiration date of the emoji status of the other party in a private chat in Unix time, if any. Returned only in getChat.
    /// @link getChat https://core.telegram.org/bots/api#getchat @endlink
    std::time_t emojiStatusExpirationDate{};

    /// @brief Optional. Bio of the other party in a private chat. Returned only in getChat.
    std::string bio;

    /// @brief Optional. True, if privacy settings of the other party in the private chat allows to use tg://user?id=<user_id> links only in chats with the user. Returned only in getChat.
    bool hasPrivateForwards{};

    /// @brief Optional. True, if the privacy settings of the other party restrict sending voice and video note messages in the private chat. Returned only in getChat.
    bool hasRestrictedVoiceAndVideoMessages{};

    /// @brief Optional. True, if users need to join the supergroup before they can send messages. Returned only in getChat.
    bool joinToSendMessages{};

    /// @brief Optional. True, if all users directly joining the supergroup need to be approved by supergroup administrators. Returned only in getChat.
    bool joinByRequest{};

    /// @brief Optional. Description, for groups, supergroups and channel chats. Returned only in getChat.
    std::string description;

    /// @brief Optional. Primary invite link, for groups, supergroups and channel chats. Returned only in getChat.
    std::string inviteLink;

    /// @brief Optional. The most recent pinned message (by sending date). Returned only in getChat.
    Ptr<Message> pinnedMessage;

    /// @brief Optional. Default chat member permissions, for groups and supergroups. Returned only in getChat.
    Ptr<ChatPermissions> permissions;

    /// @brief Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unprivileged user; in seconds. Returned only in getChat.
    std::int32_t slowModeDelay{};

    /// @brief Optional. For supergroups, the minimum number of boosts that a non-administrator user needs to add in order to ignore slow mode and chat permissions. Returned only in getChat.
    std::int32_t unrestrictBoostCount{};

    /// @brief Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds. Returned only in getChat.
    std::int32_t messageAutoDeleteTime{};

    /// @brief Optional. True, if aggressive anti-spam checks are enabled in the supergroup. The field is only available to chat administrators. Returned only in getChat.
    bool hasAggressiveAntiSpamEnabled{};

    /// @brief Optional. True, if non-administrators can only get the list of bots and administrators in the chat. Returned only in getChat.
    bool hasHiddenMembers{};

    /// @brief Optional. True, if messages from the chat can't be forwarded to other chats. Returned only in getChat.
    bool hasProtectedContent{};

    /// @brief Optional. True, if new chat members will have access to old messages; available only to chat administrators. Returned only in getChat.
    bool hasVisibleHistory{};

    /// @brief Optional. For supergroups, name of group sticker set. Returned only in getChat.
    std::string stickerSetName;

    /// @brief Optional. True, if the bot can change the group sticker set. Returned only in getChat.
    bool canSetStickerSet{};

    /// @brief Optional. Unique identifier for the linked chat, i.e. the discussion group identifier for a channel and vice versa;
    /// for supergroups and channel chats. This identifier may be greater than 32 bits and some programming languages may have
    /// difficulty/silent defects in interpreting it. But it is smaller than 52 bits, so a signed 64 bit integer
    /// or double-precision float type are safe for storing this identifier. Returned only in getChat.
    std::int64_t linkedChatId{};

    /// @brief Optional. For supergroups, the location to which the supergroup is connected. Returned only in getChat.
    Ptr<ChatLocation> location;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "id", id);
      OBJECT_SERIALIZE_FIELD_ENUM(json, Type, "type", type);
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      OBJECT_SERIALIZE_FIELD(json, "username", username);
      OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
      OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
      OBJECT_SERIALIZE_FIELD(json, "is_forum", isForum);
      OBJECT_SERIALIZE_FIELD_PTR(json, "photo", photo);
      OBJECT_SERIALIZE_FIELD(json, "active_usernames", activeUsernames);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "available_reactions", availableReactions);
      OBJECT_SERIALIZE_FIELD(json, "accent_color_id", accentColorId);
      OBJECT_SERIALIZE_FIELD(json, "background_custom_emoji_id", backgroundCustomEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "profile_accent_color_id", profileAccentColorId);
      OBJECT_SERIALIZE_FIELD(json, "profile_background_custom_emoji_id", profileBackgroundCustomEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "emoji_status_custom_emoji_id", emojiStatusCustomEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "emoji_status_expiration_date", emojiStatusExpirationDate);
      OBJECT_SERIALIZE_FIELD(json, "bio", bio);
      OBJECT_SERIALIZE_FIELD(json, "has_private_forwards", hasPrivateForwards);
      OBJECT_SERIALIZE_FIELD(json, "has_restricted_voice_and_video_messages", hasRestrictedVoiceAndVideoMessages);
      OBJECT_SERIALIZE_FIELD(json, "join_to_send_messages", joinToSendMessages);
      OBJECT_SERIALIZE_FIELD(json, "join_by_request", joinByRequest);
      OBJECT_SERIALIZE_FIELD(json, "description", description);
      OBJECT_SERIALIZE_FIELD(json, "invite_link", inviteLink);
      OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage);
      OBJECT_SERIALIZE_FIELD_PTR(json, "permissions", permissions);
      OBJECT_SERIALIZE_FIELD(json, "slow_mode_delay", slowModeDelay);
      OBJECT_SERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime);
      OBJECT_SERIALIZE_FIELD(json, "has_aggressive_anti_spam_enabled", hasAggressiveAntiSpamEnabled);
      OBJECT_SERIALIZE_FIELD(json, "has_hidden_members", hasHiddenMembers);
      OBJECT_SERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent);
      OBJECT_SERIALIZE_FIELD(json, "has_visible_history", hasVisibleHistory);
      OBJECT_SERIALIZE_FIELD(json, "sticker_set_name", stickerSetName);
      OBJECT_SERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet);
      OBJECT_SERIALIZE_FIELD(json, "linked_chat_id", linkedChatId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
      OBJECT_DESERIALIZE_FIELD_ENUM(json, Type, "type", type, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "username", username, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "is_forum", isForum, false, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "photo", photo, true);
      OBJECT_DESERIALIZE_FIELD(json, "active_usernames", activeUsernames, std::vector<std::string>(), true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "available_reactions", availableReactions, true);
      OBJECT_DESERIALIZE_FIELD(json, "accent_color_id", accentColorId, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "background_custom_emoji_id", backgroundCustomEmojiId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "profile_accent_color_id", profileAccentColorId, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "profile_background_custom_emoji_id", profileBackgroundCustomEmojiId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "emoji_status_custom_emoji_id", emojiStatusCustomEmojiId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "emoji_status_expiration_date", emojiStatusExpirationDate, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "bio", bio, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "has_private_forwards", hasPrivateForwards, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_restricted_voice_and_video_messages", hasRestrictedVoiceAndVideoMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "join_to_send_messages", joinToSendMessages, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "join_by_request", joinByRequest, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "description", description, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "invite_link", inviteLink, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "permissions", permissions, true);
      OBJECT_DESERIALIZE_FIELD(json, "slow_mode_delay", slowModeDelay, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime, 0, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_aggressive_anti_spam_enabled", hasAggressiveAntiSpamEnabled, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_hidden_members", hasHiddenMembers, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "has_visible_history", hasVisibleHistory, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "sticker_set_name", stickerSetName, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "linked_chat_id", linkedChatId, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
    }
  };
}