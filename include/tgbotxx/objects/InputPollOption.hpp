#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>

namespace tgbotxx {
  /// @brief This object contains information about one answer option in a poll to be sent.
  /// @ref https://core.telegram.org/bots/api#inputpolloption
  struct InputPollOption {
    InputPollOption() = default;
    explicit InputPollOption(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Option text, 1-100 characters
    std::string text;

    /// @brief Optional. Mode for parsing entities in the text. Currently, only custom emoji entities are allowed
    std::string textParseMode;

    /// @brief Optional. A JSON-serialized list of special entities that appear in the poll option text.
    /// It can be specified instead of text_parse_mode
    std::vector<Ptr<MessageEntity>> textEntities;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD(json, "text_parse_mode", textParseMode);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "text_parse_mode", textParseMode, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities, true);
    }
  };
}