#pragma once
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents an answer of a user in a non-anonymous poll.
  /// @ref https://core.telegram.org/bots/api#pollanswer
  struct PollAnswer {
      PollAnswer() = default;
      explicit PollAnswer(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique poll identifier
      std::string pollId;

      /// @brief Optional. The chat that changed the answer to the poll, if the voter is anonymous
      Ptr<Chat> voterChat;

      /// @brief Optional. The user that changed the answer to the poll, if the voter isn't anonymous
      Ptr<User> user;

      /// @brief 0-based identifiers of chosen answer options. May be empty if the vote was retracted.
      std::vector<std::int32_t> optionIds;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "poll_id", pollId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "voter_chat", voterChat);
        OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
        OBJECT_SERIALIZE_FIELD(json, "option_ids", optionIds);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "poll_id", pollId, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "voter_chat", voterChat, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
        OBJECT_DESERIALIZE_FIELD(json, "option_ids", optionIds, std::vector<std::int32_t>(), false);
      }
  };
}