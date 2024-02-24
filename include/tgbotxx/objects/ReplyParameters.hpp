#pragma once
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes reply parameters for the message that is being sent.
  /// @ref https://core.telegram.org/bots/api#replyparameters
  struct ReplyParameters {
      ReplyParameters() = default;
      explicit ReplyParameters(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Identifier of the message that will be replied to in the current chat, or in the chat chat_id if it is specified
      std::int32_t messageId{};

      /// @brief Optional. If the message to be replied to is from a different chat,
      /// unique identifier for the chat or username of the channel (in the format @channelusername)
      std::int64_t chatId{};

      /// @brief Optional. Pass True if the message should be sent even if the specified message to be replied to is not found;
      /// can be used only for replies in the same chat and forum topic.
      bool allowSendingWithoutReply{};

      /// @brief Optional. Quoted part of the message to be replied to; 0-1024 characters after entities parsing.
      /// The quote must be an exact substring of the message to be replied to, including bold, italic, underline, strikethrough, spoiler, and custom_emoji entities.
      /// The message will fail to send if the quote isn't found in the original message.
      std::string quote;

      /// @brief Optional. Mode for parsing entities in the quote.
      /// See [formatting options](https://core.telegram.org/bots/api#formatting-options) for more details.
      std::string quoteParseMode;

      /// @brief Optional. A JSON-serialized list of special entities that appear in the quote. It can be specified instead of quote_parse_mode.
      std::vector<Ptr<MessageEntity>> quoteEntities;

      /// @brief Optional. Position of the quote in the original message in UTF-16 code units
      std::int32_t quotePosition{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
        OBJECT_SERIALIZE_FIELD(json, "chat_id", chatId);
        OBJECT_SERIALIZE_FIELD(json, "allow_sending_without_reply", allowSendingWithoutReply);
        OBJECT_SERIALIZE_FIELD(json, "quote", quote);
        OBJECT_SERIALIZE_FIELD(json, "quote_parse_mode", quoteParseMode);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "quote_entities", quoteEntities);
        OBJECT_SERIALIZE_FIELD(json, "quote_position", quotePosition);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "chat_id", chatId, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "allow_sending_without_reply", allowSendingWithoutReply, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "quote", quote, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "quote_parse_mode", quoteParseMode, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "quote_entities", quoteEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "quote_position", quotePosition, 0, true);
      }
  };
}