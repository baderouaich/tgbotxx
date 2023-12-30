#pragma once
#include <tgbotxx/objects/Location.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Represents a result of an inline query that was chosen by the user and sent to their chat partner.
  /// @ref https://core.telegram.org/bots/api#choseninlineresult
  /// @note It is necessary to enable [inline feedback](https://core.telegram.org/bots/inline#collecting-feedback) via @BotFather in order to receive these objects in updates.
  struct ChosenInlineResult {
      ChosenInlineResult() = default;
      explicit ChosenInlineResult(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The unique identifier for the result that was chosen
      std::string resultId;

      /// @brief The user that chose the result
      Ptr<User> from;

      /// @brief Optional. Sender location, only for bots that require user location
      Ptr<Location> location;

      /// @brief Optional. Identifier of the sent inline message. Available only if there is an inline keyboard
      /// attached to the message. Will be also received in callback queries and can be used to edit the message.
      std::string inlineMessageId;

      /// @brief The query that was used to obtain the result
      std::string query;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "result_id", resultId);
        OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
        OBJECT_SERIALIZE_FIELD_PTR(json, "location", location);
        OBJECT_SERIALIZE_FIELD(json, "inline_message_id", inlineMessageId);
        OBJECT_SERIALIZE_FIELD(json, "query", query);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "result_id", resultId, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "location", location, true);
        OBJECT_DESERIALIZE_FIELD(json, "inline_message_id", inlineMessageId, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "query", query, "", false);
      }
  };
}
