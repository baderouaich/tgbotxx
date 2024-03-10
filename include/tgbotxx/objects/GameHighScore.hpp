#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object represents one row of the high scores table for a game.
  /// @ref https://core.telegram.org/bots/api#gamehighscore
  struct GameHighScore {
      GameHighScore() = default;
      explicit GameHighScore(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Position in high score table for the game
      std::int32_t position{};

      /// @brief User
      Ptr<User> user;

      /// @brief Score
      std::int32_t score{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "position", position);
        OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
        OBJECT_SERIALIZE_FIELD(json, "score", score);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "position", position, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
        OBJECT_DESERIALIZE_FIELD(json, "score", score, 0, false);
      }
  };
}