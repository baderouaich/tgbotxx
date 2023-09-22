#pragma once

#include "Object.hpp"
#include <cstdint>
#include <string>

namespace tgbotxx {
    /// @brief This object represents a Telegram user or bot.
    /// @ref https://core.telegram.org/bots/api#user
    struct User {
        /// @brief Unique identifier for this user or bot. This number may have more than 32 significant bits
        /// and some programming languages may have difficulty/silent defects in interpreting it.
        /// But it has at most 52 significant bits, so a 64-bit integer or double-precision float type
        /// are safe for storing this identifier.
        std::int64_t id;

        /// @brief True, if this user is a bot
        bool isBot;

        /// @brief User's or bot's first name
        std::string firstName;

        /// @brief Optional. User's or bot's last name
        std::string lastName;

        /// @brief Optional. User's or bot's username
        std::string username;

        /// @brief Optional. IETF language tag of the user's language
        std::string languageCode;

        /// @brief Optional. True, if this user is a Telegram Premium user
        bool isPremium;

        /// @brief Optional. True, if this user added the bot to the attachment menu
        bool addedToAttachmentMenu;

        /// @brief Optional. True, if the bot can be invited to groups. Returned only in getMe.
        bool canJoinGroups;

        /// @brief Optional. True, if privacy mode is disabled for the bot. Returned only in getMe.
        bool canReadAllGroupMessages;

        /// @brief Optional. True, if the bot supports inline queries. Returned only in getMe.
        bool supportsInlineQueries;


        nl::json toJson() const {
          nl::json user = nl::json::object();
          OBJECT_SERIALIZE_FIELD(user, "id", id);
          OBJECT_SERIALIZE_FIELD(user, "is_bot", isBot);
          OBJECT_SERIALIZE_FIELD(user, "first_name", firstName);
          OBJECT_SERIALIZE_FIELD(user, "last_name", lastName);
          OBJECT_SERIALIZE_FIELD(user, "username", username);
          OBJECT_SERIALIZE_FIELD(user, "language_code", languageCode);
          OBJECT_SERIALIZE_FIELD(user, "is_premium", isPremium);
          OBJECT_SERIALIZE_FIELD(user, "added_to_attachment_menu", addedToAttachmentMenu);
          OBJECT_SERIALIZE_FIELD(user, "can_join_groups", canJoinGroups);
          OBJECT_SERIALIZE_FIELD(user, "can_read_all_group_messages", canReadAllGroupMessages);
          OBJECT_SERIALIZE_FIELD(user, "supports_inline_queries", supportsInlineQueries);
          return user;
        }

        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "id", id, -1);
          OBJECT_DESERIALIZE_FIELD(json, "is_bot", isBot, false);
          OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "");
          OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "");
          OBJECT_DESERIALIZE_FIELD(json, "username", username, "");
          OBJECT_DESERIALIZE_FIELD(json, "language_code", languageCode, "");
          OBJECT_DESERIALIZE_FIELD(json, "is_premium", isPremium, false);
          OBJECT_DESERIALIZE_FIELD(json, "added_to_attachment_menu", addedToAttachmentMenu, false);
          OBJECT_DESERIALIZE_FIELD(json, "can_join_groups", canJoinGroups, false);
          OBJECT_DESERIALIZE_FIELD(json, "can_read_all_group_messages", canReadAllGroupMessages, false);
          OBJECT_DESERIALIZE_FIELD(json, "supports_inline_queries", supportsInlineQueries, false);
        }
    };
}