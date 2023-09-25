#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
    /// @brief This object represents an inline button that switches the current user to inline mode in a chosen chat,
    /// with an optional default inline query.
    /// @ref https://core.telegram.org/bots/api#switchinlinequerychosenchat
    struct SwitchInlineQueryChosenChat {
        explicit SwitchInlineQueryChosenChat(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Optional. The default inline query to be inserted in the input field. If left empty, only the bot's username will be inserted
        std::string query;

        /// @brief Optional. True, if private chats with users can be chosen
        bool allowUserChats;

        /// @brief Optional. True, if private chats with bots can be chosen
        bool allowBotChats;

        /// @brief Optional. True, if group and supergroup chats can be chosen
        bool allowGroupChats;

        /// @brief Optional. True, if channel chats can be chosen
        bool allowChannelChats;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "query", query);
          OBJECT_SERIALIZE_FIELD(json, "allow_user_chats", allowUserChats);
          OBJECT_SERIALIZE_FIELD(json, "allow_bot_chats", allowBotChats);
          OBJECT_SERIALIZE_FIELD(json, "allow_group_chats", allowGroupChats);
          OBJECT_SERIALIZE_FIELD(json, "allow_channel_chats", allowChannelChats);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "query", query, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "allow_user_chats", allowUserChats, false, true);
          OBJECT_DESERIALIZE_FIELD(json, "allow_bot_chats", allowBotChats, false, true);
          OBJECT_DESERIALIZE_FIELD(json, "allow_group_chats", allowGroupChats, false, true);
          OBJECT_DESERIALIZE_FIELD(json, "allow_channel_chats", allowChannelChats, false, true);
        }
    };
}