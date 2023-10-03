#pragma once
#include <string>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a bot command.
  /// @ref https://core.telegram.org/bots/api#botcommand
  struct BotCommand {
      BotCommand() = default;
      explicit BotCommand(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Text of the command; 1-32 characters. Can contain only lowercase English letters, digits and underscores.
      std::string command;

      /// @brief Description of the command; 1-256 characters.
      std::string description;

      nl::json toJson() const {
        nl::json cmd = nl::json::object();
        OBJECT_SERIALIZE_FIELD(cmd, "command", command);
        OBJECT_SERIALIZE_FIELD(cmd, "description", description);
        return cmd;
      }

      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "command", command, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", false);
      }
  };
}