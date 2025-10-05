#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>

namespace tgbotxx {
  /// @brief This object contains information about the quoted part of a message that is replied to by the given message.
  /// @ref https://core.telegram.org/bots/api#textquote
  struct TextQuote {
    TextQuote() = default;
    explicit TextQuote(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Text of the quoted part of a message that is replied to by the given message
    std::string text;

    /// @brief Optional. Special entities that appear in the quote.
    /// Currently, only bold, italic, underline, strikethrough, spoiler, and custom_emoji entities are kept in quotes.
    std::vector<Ptr<MessageEntity>> entities;

    /// @brief Approximate quote position in the original message in UTF-16 code units as specified by the sender
    std::int32_t position{};

    /// @brief Optional. True, if the quote was chosen manually by the message sender. Otherwise, the quote was added automatically by the server.
    bool isManual{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities);
      OBJECT_SERIALIZE_FIELD(json, "position", position);
      OBJECT_SERIALIZE_FIELD(json, "is_manual", isManual);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "entities", entities, true);
      OBJECT_DESERIALIZE_FIELD(json, "position", position, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_manual", isManual, false, true);
    }
  };
}