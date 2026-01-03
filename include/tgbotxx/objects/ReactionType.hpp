#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object describes the type of a reaction. Currently, it can be one of:
  /// - ReactionTypeEmoji
  /// - ReactionTypeCustomEmoji
  /// @ref https://core.telegram.org/bots/api#reactiontype
  struct ReactionType {
    ReactionType() = default;
    explicit ReactionType(const nl::json& json) {
      ReactionType::fromJson(json);
    }
    virtual ~ReactionType() = default;

    /// @brief Type of the reaction, one of “emoji”, "custom_emoji”
    std::string type;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief The reaction is based on an emoji.
  /// @ref https://core.telegram.org/bots/api#reactiontypeemoji
  struct ReactionTypeEmoji : ReactionType {
    ReactionTypeEmoji() {
      type = "emoji";
    }
    explicit ReactionTypeEmoji(const nl::json& json) {
      ReactionTypeEmoji::fromJson(json);
    }

    /// @brief Reaction emoji. Currently,it can be one of "👍", "👎", "❤", "🔥", "🥰", "👏", "😁", "🤔", "🤯",
    /// "😱", "🤬", "😢", "🎉", "🤩", "🤮", "💩", "🙏", "👌", "🕊", "🤡", "🥱", "🥴", "😍", "🐳", "❤‍🔥", "🌚",
    /// "🌭", "💯", "🤣", "⚡", "🍌", "🏆", "💔", "🤨", "😐", "🍓", "🍾", "💋", "🖕", "😈", "😴", "😭", "🤓",
    /// "👻", "👨‍💻", "👀", "🎃", "🙈", "😇", "😨", "🤝", "✍", "🤗", "🫡", "🎅", "🎄", "☃", "💅", "🤪", "🗿",
    /// "🆒", "💘", "🙉", "🦄", "😘", "💊", "🙊", "😎", "👾", "🤷‍♂", "🤷", "🤷‍♀", "😡"
    std::string emoji;


    [[nodiscard]] nl::json toJson() const override {
      nl::json json = ReactionType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "emoji", emoji);
      return json;
    }
    void fromJson(const nl::json& json) override {
      ReactionType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "emoji", emoji, "", false);
    }
  };

  /// @brief The reaction is based on a custom emoji.
  /// @ref https://core.telegram.org/bots/api#reactiontypecustomemoji
  struct ReactionTypeCustomEmoji : ReactionType {
    ReactionTypeCustomEmoji() {
      type = "custom_emoji";
    }
    explicit ReactionTypeCustomEmoji(const nl::json& json) {
      ReactionTypeCustomEmoji::fromJson(json);
    }

    /// @brief Custom emoji identifier
    std::string customEmojiId;


    [[nodiscard]] nl::json toJson() const override {
      nl::json json = ReactionType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId);
      return json;
    }
    void fromJson(const nl::json& json) override {
      ReactionType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId, "", false);
    }
  };
}