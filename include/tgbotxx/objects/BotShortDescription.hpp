#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents the bot's short description.
  /// @ref https://core.telegram.org/bots/api#botshortdescription
  struct BotShortDescription {
      BotShortDescription() = default;
      explicit BotShortDescription(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The bot's short description
      std::string shortDescription;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "short_description", shortDescription);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "short_description", shortDescription, "", false);
      }
  };
}