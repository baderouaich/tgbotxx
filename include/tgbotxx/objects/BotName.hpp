#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents the bot's name.
  /// @ref https://core.telegram.org/bots/api#botname
  struct BotName {
      BotName() = default;
      explicit BotName(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The bot's name
      std::string name;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "name", name);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
      }
  };
}