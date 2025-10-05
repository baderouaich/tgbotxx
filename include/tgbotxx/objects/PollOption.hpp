#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MessageEntity.hpp>

namespace tgbotxx {
  /// @brief This object contains information about one answer option in a poll.
  /// @ref https://core.telegram.org/bots/api#polloption
  struct PollOption {
    PollOption() = default;
    explicit PollOption(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Option text, 1-100 characters
    std::string text;

    /// @brief Optional. Special entities that appear in the option text. Currently, only custom emoji entities are allowed in poll option texts
    std::vector<Ptr<MessageEntity>> textEntities;

    /// @brief Number of users that voted for this option
    std::int32_t voterCount{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "text", text);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities);
      OBJECT_SERIALIZE_FIELD(json, "voter_count", voterCount);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities, true);
      OBJECT_DESERIALIZE_FIELD(json, "voter_count", voterCount, 0, false);
    }
  };
}