#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents the bot's description.
  /// @ref https://core.telegram.org/bots/api#botdescription
  struct BotDescription {
      BotDescription() = default;
      explicit BotDescription(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The bot's description
      std::string description;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", false);
      }
  };
}