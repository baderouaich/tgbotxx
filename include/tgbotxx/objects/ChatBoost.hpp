#pragma once
#include <tgbotxx/objects/ChatBoostSource.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object contains information about a chat boost.
  /// @ref https://core.telegram.org/bots/api#chatboost
  struct ChatBoost {
      ChatBoost() = default;
      explicit ChatBoost(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique identifier of the boost
      std::string boostId;

      /// @brief Point in time (Unix timestamp) when the chat was boosted
      std::time_t addDate{};

      /// @brief Point in time (Unix timestamp) when the boost will automatically expire, unless the booster's Telegram Premium subscription is prolonged
      std::time_t expirationDate{};

      /// @brief Source of the added boost
      Ptr<ChatBoostSource> source;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "boost_id", boostId);
        OBJECT_SERIALIZE_FIELD(json, "add_date", addDate);
        OBJECT_SERIALIZE_FIELD(json, "expiration_date", expirationDate);
        OBJECT_SERIALIZE_FIELD_PTR(json, "source", source);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "boost_id", boostId, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "add_date", addDate, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "expiration_date", expirationDate, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "source", source, false);
      }
  };
}
