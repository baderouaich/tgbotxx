#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc.
  /// @ref https://core.telegram.org/bots/api#messageentity
  struct MessageEntity {
    MessageEntity() = default;
    explicit MessageEntity(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Enum of possible types of MessageEntity.
    enum class Type : std::uint8_t {
      /// @brief “mention” (@username),
      Mention = 0,
      /// @brief “hashtag” (#hashtag or #hashtag@chatusername),
      Hashtag,
      /// @brief “cashtag” ($USD or $USD@chatusername),
      Cashtag,
      /// @brief “bot_command” (/start@jobs_bot),
      BotCommand,
      /// @brief “url” (https://telegram.org),
      Url,
      /// @brief “email” (do-not-reply@telegram.org),
      Email,
      /// @brief “phone_number” (+1-212-555-0123),
      PhoneNumber,
      /// @brief “bold” (bold text),
      Bold,
      /// @brief “italic” (italic text),
      Italic,
      /// @brief “underline” (underlined text),
      Underline,
      /// @brief “strikethrough” (strikethrough text),
      Strikethrough,
      /// @brief “spoiler” (spoiler message),
      Spoiler,
      /// @brief “blockquote” (block quotation),
      Blockquote,
      /// @brief “expandable_blockquote” (collapsed-by-default block quotation),
      ExpandableBlockquote,
      /// @brief “code” (monowidth string),
      Code,
      /// @brief “pre” (monowidth block),
      Pre,
      /// @brief “text_link” (for clickable text URLs),
      TextLink,
      /// @brief “text_mention” (for users without usernames),
      TextMention,
      /// @brief “custom_emoji” (for inline custom emoji stickers)
      CustomEmoji
    };
    /// @brief Converts enum Type to a string
    static std::optional<std::string> TypeToString(const Type type) noexcept {
      if (type == Type::Mention) return "mention";
      if (type == Type::Hashtag) return "hashtag";
      if (type == Type::Cashtag) return "cashtag";
      if (type == Type::BotCommand) return "bot_command";
      if (type == Type::Url) return "url";
      if (type == Type::Email) return "email";
      if (type == Type::PhoneNumber) return "phone_number";
      if (type == Type::Bold) return "bold";
      if (type == Type::Italic) return "italic";
      if (type == Type::Underline) return "underline";
      if (type == Type::Strikethrough) return "strikethrough";
      if (type == Type::Spoiler) return "spoiler";
      if (type == Type::Blockquote) return "blockquote";
      if (type == Type::ExpandableBlockquote) return "expandable_blockquote";
      if (type == Type::Code) return "code";
      if (type == Type::Pre) return "pre";
      if (type == Type::TextLink) return "text_link";
      if (type == Type::TextMention) return "text_mention";
      if (type == Type::CustomEmoji) return "custom_emoji";
      return std::nullopt;
    }
    /// @brief Converts string to an enum Type
    static std::optional<Type> StringToType(const std::string& str) noexcept {
      if (str == "mention") return Type::Mention;
      if (str == "hashtag") return Type::Hashtag;
      if (str == "cashtag") return Type::Cashtag;
      if (str == "bot_command") return Type::BotCommand;
      if (str == "url") return Type::Url;
      if (str == "email") return Type::Email;
      if (str == "phone_number") return Type::PhoneNumber;
      if (str == "bold") return Type::Bold;
      if (str == "italic") return Type::Italic;
      if (str == "underline") return Type::Underline;
      if (str == "strikethrough") return Type::Strikethrough;
      if (str == "spoiler") return Type::Spoiler;
      if (str == "blockquote") return Type::Blockquote;
      if (str == "expandable_blockquote") return Type::ExpandableBlockquote;
      if (str == "code") return Type::Code;
      if (str == "pre") return Type::Pre;
      if (str == "text_link") return Type::TextLink;
      if (str == "text_mention") return Type::TextMention;
      if (str == "custom_emoji") return Type::CustomEmoji;
      return std::nullopt;
    }

    /// @brief Type of the entity.
    /// Type of the entity. Currently, can be:
    /// “mention” (@username),
    /// “hashtag” (#hashtag or #hashtag@chatusername),
    /// “cashtag” ($USD or $USD@chatusername),
    /// “bot_command” (/start@jobs_bot),
    /// “url” (https://telegram.org),
    /// “email” (do-not-reply@telegram.org),
    /// “phone_number” (+1-212-555-0123),
    /// “bold” (bold text),
    /// “italic” (italic text),
    /// “underline” (underlined text),
    /// “strikethrough” (strikethrough text),
    /// “spoiler” (spoiler message),
    /// “blockquote” (block quotation),
    /// “expandable_blockquote” (collapsed-by-default block quotation),
    /// “code” (monowidth string),
    /// “pre” (monowidth block),
    /// “text_link” (for clickable text URLs),
    /// “text_mention” (for users without usernames),
    /// “custom_emoji” (for inline custom emoji stickers)
    Type type{};

    /// @brief Offset in UTF-16 code units to the start of the entity
    std::int32_t offset{};

    /// @brief Length of the entity in UTF-16 code units
    std::int32_t length{};

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
      OBJECT_SERIALIZE_FIELD_ENUM(json, Type, "type", type);
      OBJECT_SERIALIZE_FIELD(json, "offset", offset);
      OBJECT_SERIALIZE_FIELD(json, "length", length);
      OBJECT_SERIALIZE_FIELD(json, "url", url);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      OBJECT_SERIALIZE_FIELD(json, "language", language);
      OBJECT_SERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_ENUM(json, Type, "type", type, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "offset", offset, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "length", length, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "url", url, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
      OBJECT_DESERIALIZE_FIELD(json, "language", language, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId, "", true);
    }
  };
}