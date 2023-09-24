#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief This object represents an animated emoji that displays a random value.
    /// @ref https://core.telegram.org/bots/api#dice
    struct Dice {
        explicit Dice(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Emoji on which the dice throw animation is based
        std::string emoji;

        /// @brief Value of the dice, 1-6 for “🎲”, “🎯” and “🎳” base emoji, 1-5 for “🏀” and “⚽” base emoji, 1-64 for “🎰” base emoji
        std::int32_t value;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "emoji", emoji);
          OBJECT_SERIALIZE_FIELD(json, "value", value);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "emoji", emoji, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "value", value, 0, false);
        }
    };
}