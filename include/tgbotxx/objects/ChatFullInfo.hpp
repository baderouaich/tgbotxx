#pragma once
#include <tgbotxx/objects/ChatLocation.hpp>
#include <tgbotxx/objects/ChatPermissions.hpp>
#include <tgbotxx/objects/ChatPhoto.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ReactionType.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Birthdate.hpp>
#include <tgbotxx/objects/BusinessIntro.hpp>
#include <tgbotxx/objects/BusinessLocation.hpp>
#include <tgbotxx/objects/BusinessOpeningHours.hpp>

namespace tgbotxx {
  /// @brief This object represents a chat.
  /// @ref https://core.telegram.org/bots/api#chatfullinfo
  struct ChatFullInfo : Chat {
    ChatFullInfo() = default;
    explicit ChatFullInfo(const nl::json& json);

    /// @brief Optional. Identifier of the accent color for the chat name and backgrounds of the chat photo, reply header, and link preview.
    /// See [accent colors](https://core.telegram.org/bots/API#accent-colors) for more details. Always returned in getChat.
    std::int32_t accentColorId{};

    /// @brief The maximum number of reactions that can be set on a message in the chat
    std::int64_t maxReactionCount{};

    /// @brief Optional. Chat photo.
    Ptr<ChatPhoto> photo;

    /// @brief Optional. If non-empty, the list of all active chat usernames; for private chats, supergroups and channels
    std::vector<std::string> activeUsernames;

    /// @brief Optional. For private chats, the date of birth of the user
    Ptr<Birthdate> birthdate;

    /// @brief Optional. For private chats with business accounts, the intro of the business
    Ptr<BusinessIntro> businessIntro;

    /// @brief Optional. For private chats with business accounts, the location of the business
    Ptr<BusinessLocation> businessLocation;

    /// @brief Optional. For private chats with business accounts, the opening hours of the business
    Ptr<BusinessOpeningHours> businessOpeningHours;

    /// @brief Optional. For private chats, the personal channel of the user
    Ptr<Chat> personalChat;

    /// @brief Optional. Information about the corresponding channel chat; for direct messages chats only
    Ptr<Chat> parentChat;

    /// @brief Optional. List of available reactions allowed in the chat. If omitted, then all emoji reactions are allowed.
    std::vector<Ptr<ReactionType>> availableReactions;

    /// @brief Optional. Custom emoji identifier of emoji chosen by the chat for the reply header and link preview background.
    std::string backgroundCustomEmojiId;

    /// @brief Optional. Identifier of the accent color for the chat's profile background. See profile accent colors for more details.
    std::int32_t profileAccentColorId{};

    /// @brief Optional. Custom emoji identifier of the emoji chosen by the chat for its profile background.
    std::string profileBackgroundCustomEmojiId;

    /// @brief Optional. Custom emoji identifier of emoji status of the other party in a private chat.
    /// @link getChat https://core.telegram.org/bots/api#getchat @endlink
    std::string emojiStatusCustomEmojiId;

    /// @brief Optional. Expiration date of the emoji status of the other party in a private chat in Unix time, if any.
    /// @link getChat https://core.telegram.org/bots/api#getchat @endlink
    std::time_t emojiStatusExpirationDate{};

    /// @brief Optional. Bio of the other party in a private chat.
    std::string bio;

    /// @brief Optional. True, if privacy settings of the other party in the private chat allows to use tg://user?id=<user_id> links only in chats with the user.
    bool hasPrivateForwards{};

    /// @brief Optional. True, if the privacy settings of the other party restrict sending voice and video note messages in the private chat.
    bool hasRestrictedVoiceAndVideoMessages{};

    /// @brief Optional. True, if users need to join the supergroup before they can send messages.
    bool joinToSendMessages{};

    /// @brief Optional. True, if all users directly joining the supergroup need to be approved by supergroup administrators.
    bool joinByRequest{};

    /// @brief Optional. Description, for groups, supergroups and channel chats.
    std::string description;

    /// @brief Optional. Primary invite link, for groups, supergroups and channel chats.
    std::string inviteLink;

    /// @brief Optional. The most recent pinned message (by sending date).
    Ptr<Message> pinnedMessage;

    /// @brief Optional. Default chat member permissions, for groups and supergroups.
    Ptr<ChatPermissions> permissions;

    /// @brief Optional. For supergroups, the minimum allowed delay between consecutive messages sent by each unprivileged user; in seconds.
    std::int32_t slowModeDelay{};

    /// @brief Optional. For supergroups, the minimum number of boosts that a non-administrator user needs to add in order to ignore slow mode and chat permissions
    std::int32_t unrestrictBoostCount{};

    /// @brief Optional. The time after which all messages sent to the chat will be automatically deleted; in seconds.
    std::int32_t messageAutoDeleteTime{};

    /// @brief Optional. True, if aggressive anti-spam checks are enabled in the supergroup. The field is only available to chat administrators.
    bool hasAggressiveAntiSpamEnabled{};

    /// @brief Optional. True, if non-administrators can only get the list of bots and administrators in the chat.
    bool hasHiddenMembers{};

    /// @brief Optional. True, if messages from the chat can't be forwarded to other chats.
    bool hasProtectedContent{};

    /// @brief Optional. True, if new chat members will have access to old messages; available only to chat administrators.
    bool hasVisibleHistory{};

    /// @brief Optional. For supergroups, name of group sticker set.
    std::string stickerSetName;

    /// @brief Optional. True, if the bot can change the group sticker set.
    bool canSetStickerSet{};

    /// @brief Optional. For supergroups, the name of the group's custom emoji sticker set. Custom emoji from this set can be used by all users and bots in the group.
    std::string customEmojiStickerSetName;

    /// @brief Optional. Unique identifier for the linked chat, i.e. the discussion group identifier for a channel and vice versa;
    /// for supergroups and channel chats. This identifier may be greater than 32 bits and some programming languages may have
    /// difficulty/silent defects in interpreting it. But it is smaller than 52 bits, so a signed 64 bit integer
    /// or double-precision float type are safe for storing this identifier.
    std::int64_t linkedChatId{};

    /// @brief Optional. For supergroups, the location to which the supergroup is connected.
    Ptr<ChatLocation> location;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const override;
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override;
  };
}