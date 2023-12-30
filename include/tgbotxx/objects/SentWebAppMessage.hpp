#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes an inline message sent by a [Web App](https://core.telegram.org/bots/webapps) on behalf of a user.
  /// @ref https://core.telegram.org/bots/api#story
  struct SentWebAppMessage {
      SentWebAppMessage() = default;
      explicit SentWebAppMessage(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Optional. Identifier of the sent inline message.
      /// Available only if there is an inline keyboard attached to the message.
      std::string inlineMessageId;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "inline_message_id", inlineMessageId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson([[maybe_unused]] const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "inline_message_id", inlineMessageId, "", false);
      }
  };
}