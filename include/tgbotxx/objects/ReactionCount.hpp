#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ReactionType.hpp>

namespace tgbotxx {
  /// @brief Represents a reaction added to a message along with the number of times it was added.
  /// @ref https://core.telegram.org/bots/api#reactioncount
  struct ReactionCount {
      ReactionCount() = default;
      explicit ReactionCount(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Type of the reaction
      Ptr<ReactionType> type;

      /// @brief Number of times the reaction was added
      std::int32_t totalCount{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR(json, "type", type);
        OBJECT_SERIALIZE_FIELD(json, "total_count", totalCount);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD_PTR(json, "type", type, false);
        OBJECT_DESERIALIZE_FIELD(json, "total_count", totalCount, 0, false);
      }
  };
}