#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a Telegram user or bot.
  /// @ref https://core.telegram.org/bots/api#user
  struct User {
    User() = default;
    explicit User(const nl::json& json);

    /// @brief Unique identifier for this user or bot. This number may have more than 32 significant bits
    /// and some programming languages may have difficulty/silent defects in interpreting it.
    /// But it has at most 52 significant bits, so a 64-bit integer or double-precision float type
    /// are safe for storing this identifier.
    std::int64_t id{};

    /// @brief True, if this user is a bot
    bool isBot{};

    /// @brief User's or bot's first name
    std::string firstName;

    /// @brief Optional. User's or bot's last name
    std::string lastName;

    /// @brief Optional. User's or bot's username
    std::string username;

    /// @brief Optional. IETF language tag of the user's language
    /// @link https://en.wikipedia.org/wiki/IETF_language_tag @endlink
    std::string languageCode;

    /// @brief Optional. True, if this user is a Telegram Premium user
    bool isPremium{};

    /// @brief Optional. True, if this user added the bot to the attachment menu
    bool addedToAttachmentMenu{};

    /// @brief Optional. True, if the bot can be invited to groups. Returned only in getMe.
    bool canJoinGroups{};

    /// @brief Optional. True, if privacy mode is disabled for the bot. Returned only in getMe.
    bool canReadAllGroupMessages{};

    /// @brief Optional. True, if the bot supports inline queries. Returned only in getMe.
    bool supportsInlineQueries{};

    /// @brief Optional. True, if the bot can be connected to a Telegram Business account to receive its messages. Returned only in getMe.
    bool canConnectToBusiness{};

    /// @brief Optional. True, if the bot has a main Web App. Returned only in getMe.
    bool hasMainWebApp{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const;

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json);
  };
}