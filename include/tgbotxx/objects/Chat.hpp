#pragma once
#include <tgbotxx/objects/ChatLocation.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/ChatPhoto.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Object.hpp>

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

      /// @brief Enum of possible types of a chat.
      enum class Type : std::uint8_t {
        Private = 0,
        Group,
        Supergroup,
        Channel
      };
      inline static constexpr const char *Type2Str[] = {
        "private", "group", "supergroup", "channel"};
      inline static constexpr Type Str2Type(const std::string& str) {
        std::uint8_t i = 0;
        for (const char *v: Type2Str) {
          if (str == v)
            return static_cast<Type>(i);
          ++i;
        }
        throw Exception("Could not convert Chat type string \"" + str + "\" to enum Type");
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

      /// @brief Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds. Returned only in getChat.
      std::int32_t messageAutoDeleteTime{};

      /// @brief Optional. True, if aggressive anti-spam checks are enabled in the supergroup. The field is only available to chat administrators. Returned only in getChat.
      bool hasAggressiveAntiSpamEnabled{};

      /// @brief Optional. True, if non-administrators can only get the list of bots and administrators in the chat. Returned only in getChat.
      bool hasHiddenMembers{};

      /// @brief Optional. True, if messages from the chat can't be forwarded to other chats. Returned only in getChat.
      bool hasProtectedContent{};

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
        json["type"] = Type2Str[static_cast<std::size_t>(type)];// enum
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "username", username);
        OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
        OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
        OBJECT_SERIALIZE_FIELD(json, "is_forum", isForum);
        OBJECT_SERIALIZE_FIELD_PTR(json, "photo", photo, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "active_usernames", activeUsernames);
        OBJECT_SERIALIZE_FIELD(json, "emoji_status_custom_emoji_id", emojiStatusCustomEmojiId);
        OBJECT_SERIALIZE_FIELD(json, "emoji_status_expiration_date", emojiStatusExpirationDate);
        OBJECT_SERIALIZE_FIELD(json, "bio", bio);
        OBJECT_SERIALIZE_FIELD(json, "has_private_forwards", hasPrivateForwards);
        OBJECT_SERIALIZE_FIELD(json, "has_restricted_voice_and_video_messages", hasRestrictedVoiceAndVideoMessages);
        OBJECT_SERIALIZE_FIELD(json, "join_to_send_messages", joinToSendMessages);
        OBJECT_SERIALIZE_FIELD(json, "join_by_request", joinByRequest);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD(json, "invite_link", inviteLink);
        OBJECT_SERIALIZE_FIELD_PTR(json, "pinned_message", pinnedMessage, nl::json::object());
        OBJECT_SERIALIZE_FIELD_PTR(json, "permissions", permissions, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "slow_mode_delay", slowModeDelay);
        OBJECT_SERIALIZE_FIELD(json, "message_auto_delete_time", messageAutoDeleteTime);
        OBJECT_SERIALIZE_FIELD(json, "has_aggressive_anti_spam_enabled", hasAggressiveAntiSpamEnabled);
        OBJECT_SERIALIZE_FIELD(json, "has_hidden_members", hasHiddenMembers);
        OBJECT_SERIALIZE_FIELD(json, "has_protected_content", hasProtectedContent);
        OBJECT_SERIALIZE_FIELD(json, "sticker_set_name", stickerSetName);
        OBJECT_SERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet);
        OBJECT_SERIALIZE_FIELD(json, "linked_chat_id", linkedChatId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "location", location, nl::json::object());
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "id", id, 0, false);
        type = Str2Type(json["type"]);// enum
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "username", username, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "is_forum", isForum, false, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "photo", photo, true);
        OBJECT_DESERIALIZE_FIELD(json, "active_usernames", activeUsernames, std::vector<std::string>(), true);
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
        OBJECT_DESERIALIZE_FIELD(json, "sticker_set_name", stickerSetName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "can_set_sticker_set", canSetStickerSet, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "linked_chat_id", linkedChatId, 0, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
      }
  };
}