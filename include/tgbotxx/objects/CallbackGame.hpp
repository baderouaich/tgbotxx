#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
    /// @brief A placeholder, currently holds no information.
    /// @note Use BotFather to set up your game.
    /// @ref https://core.telegram.org/bots/api#callbackgame
    struct CallbackGame {
        explicit CallbackGame(const nl::json& json) {
          fromJson(json);
        }


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
        }
    };
}