#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a unique message identifier.
  /// @ref https://core.telegram.org/bots/api#messageid
  struct MessageId {
      MessageId() = default;
      explicit MessageId(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique message identifier. In specific instances (e.g., message containing a video sent to a big chat),
      /// the server might automatically schedule a message instead of sending it immediately. In such cases,
      /// this field will be 0 and the relevant message will be unusable until it is actually sent
      std::int32_t messageId{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "message_id", messageId);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "message_id", messageId, 0, false);
      }
  };
}