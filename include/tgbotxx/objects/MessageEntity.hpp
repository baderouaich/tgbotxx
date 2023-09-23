#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
    /// @brief This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc.
    /// @ref https://core.telegram.org/bots/api#messageentity
    struct MessageEntity {
        explicit MessageEntity(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Enum of possible types of MessageEntity.
        enum class Type : std::uint8_t {
            /// @brief “mention” (@username)
            Mention = 0,
            /// @brief “hashtag” (#hashtag)
            Hashtag,
            /// @brief “cashtag” ($USD)
            Cashtag,
            /// @brief “bot_command” (/start@jobs_bot)
            BotCommand,
            /// @brief “url” (https://telegram.org)
            Url,
            /// @brief “email” (do-not-reply@telegram.org)
            Email,
            /// @brief “phone_number” (+1-212-555-0123)
            PhoneNumber,
            /// @brief “bold” (bold text)
            Bold,
            /// @brief “italic” (italic text)
            Italic,
            /// @brief “underline” (underlined text)
            Underline,
            /// @brief “strikethrough” (strikethrough text)
            Strikethrough,
            /// @brief “spoiler” (spoiler message)
            Spoiler,
            /// @brief “code” (monowidth string)
            Code,
            /// @brief “pre” (monowidth block)
            Pre,
            /// @brief “text_link” (for clickable text URLs)
            TextLink,
            /// @brief “text_mention” (for users without usernames)
            TextMention,
            /// @brief “custom_emoji” (for inline custom emoji stickers)
            CustomEmoji
        };
        inline static constexpr const char* Type2Str[] = {
                "mention",
                "hashtag",
                "cashtag",
                "bot_command",
                "url",
                "email",
                "phone_number",
                "bold",
                "italic",
                "underline",
                "strikethrough",
                "spoiler",
                "code",
                "pre",
                "text_link",
                "text_mention",
                "custom_emoji"
        };

        inline static constexpr Type Str2Type(const std::string& str){
          std::uint8_t i = 0;
          for(const char* v : Type2Str) {
            if(str == v)
              return static_cast<Type>(i);
            ++i;
          }
          throw Exception("Could not convert MessageEntity type string \""+str+"\" to enum Type");
        }

        /// @brief Type of the entity.
        /// Currently, can be “mention” (@username), “hashtag” (#hashtag), “cashtag” ($USD),
        /// “bot_command” (/start@jobs_bot), “url” (https://telegram.org), “email” (do-not-reply@telegram.org),
        /// “phone_number” (+1-212-555-0123), “bold” (bold text), “italic” (italic text), “underline” (underlined text),
        /// “strikethrough” (strikethrough text), “spoiler” (spoiler message), “code” (monowidth string),
        /// “pre” (monowidth block), “text_link” (for clickable text URLs), “text_mention” (for users without usernames),
        /// “custom_emoji” (for inline custom emoji stickers)
        Type type;

        /// @brief Offset in UTF-16 code units to the start of the entity
        std::int32_t offset;

        /// @brief Length of the entity in UTF-16 code units
        std::int32_t length;

        /// @brief Optional. For “text_link” only, URL that will be opened after user taps on the text
        std::string url;

        /// @brief Optional. For “text_mention” only, the mentioned user
        Ptr<User> user;

        /// @brief Optional. For “pre” only, the programming language of the entity text
        std::string language;

        /// @brief Optional. For “custom_emoji” only, unique identifier of the custom emoji.
        /// Use Api::getCustomEmojiStickers to get full information about the sticker
        std::string customEmojiId;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          json["type"] = Type2Str[static_cast<std::size_t>(type)]; // enum
          OBJECT_SERIALIZE_FIELD(json, "offset", offset);
          OBJECT_SERIALIZE_FIELD(json, "length", length);
          OBJECT_SERIALIZE_FIELD(json, "url", url);
          OBJECT_SERIALIZE_FIELD_PTR(json, "user", user, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "language", language);
          OBJECT_SERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          type = Str2Type(json["type"]); // enum
          OBJECT_DESERIALIZE_FIELD(json, "offset", offset, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "length", length, 0, false);
          OBJECT_DESERIALIZE_FIELD(json, "url", url, "", true);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
          OBJECT_DESERIALIZE_FIELD(json, "language", language, "", true);
          OBJECT_DESERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId, "", true);
        }
    };
}