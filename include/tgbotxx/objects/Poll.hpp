#pragma once
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PollOption.hpp>

namespace tgbotxx {
  /// @brief This object contains information about a poll.
  /// @ref https://core.telegram.org/bots/api#poll
  struct Poll {
      Poll() = default;
      explicit Poll(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique poll identifier
      std::string id;

      /// @brief Poll question, 1-300 characters
      std::string question;

      /// @brief List of poll options
      std::vector<Ptr<PollOption>> options;

      /// @brief Total number of users that voted in the poll
      std::int32_t totalVoterCount{};

      /// @brief True, if the poll is closed
      bool isClosed{};

      /// @brief True, if the poll is anonymous
      bool isAnonymous{};

      /// @brief Poll type, currently can be “regular” or “quiz”
      std::string type;

      /// @brief True, if the poll allows multiple answers
      bool allowsMultipleAnswers{};

      /// @brief Optional. 0-based identifier of the correct answer option. Available only for polls in the quiz mode,
      /// which are closed, or was sent (not forwarded) by the bot or to the private chat with the bot.
      std::int32_t correctOptionId{};

      /// @brief Optional. Text that is shown when a user chooses an incorrect answer or taps on the lamp icon in a quiz-style poll, 0-200 characters
      std::string explanation;

      /// @brief Optional. Special entities like usernames, URLs, bot commands, etc. that appear in the explanation
      std::vector<Ptr<MessageEntity>> explanationEntities;

      /// @brief Optional. Amount of time in seconds the poll will be active after creation
      std::int32_t openPeriod{};

      /// @brief Optional. Point in time (Unix timestamp) when the poll will be automatically closed
      std::time_t closeDate{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "id", id);
        OBJECT_SERIALIZE_FIELD(json, "question", question);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "options", options);
        OBJECT_SERIALIZE_FIELD(json, "total_voter_count", totalVoterCount);
        OBJECT_SERIALIZE_FIELD(json, "is_closed", isClosed);
        OBJECT_SERIALIZE_FIELD(json, "is_anonymous", isAnonymous);
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        OBJECT_SERIALIZE_FIELD(json, "allows_multiple_answers", allowsMultipleAnswers);
        OBJECT_SERIALIZE_FIELD(json, "correct_option_id", correctOptionId);
        OBJECT_SERIALIZE_FIELD(json, "explanation", explanation);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "explanation_entities", explanationEntities);
        OBJECT_SERIALIZE_FIELD(json, "open_period", openPeriod);
        OBJECT_SERIALIZE_FIELD(json, "close_date", closeDate);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "question", question, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "options", options, false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "options", options, false);
        OBJECT_DESERIALIZE_FIELD(json, "total_voter_count", totalVoterCount, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "is_closed", isClosed, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "is_anonymous", isAnonymous, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "allows_multiple_answers", allowsMultipleAnswers, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "correct_option_id", correctOptionId, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "explanation", explanation, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "explanation_entities", explanationEntities, true);
        OBJECT_DESERIALIZE_FIELD(json, "open_period", openPeriod, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "close_date", closeDate, 0, true);
      }
  };
}