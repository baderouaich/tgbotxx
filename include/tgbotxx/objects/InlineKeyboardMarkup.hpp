#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/InlineKeyboardButton.hpp>

namespace tgbotxx {
    /// @brief This object represents an inline keyboard that appears right next to the message it belongs to.
    /// @ref https://core.telegram.org/bots/api#inlinekeyboardmarkup
    struct InlineKeyboardMarkup {
        explicit InlineKeyboardMarkup(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Array of button rows, each represented by an Array of InlineKeyboardButton objects
        std::vector<Ptr<InlineKeyboardButton>> inlineKeyboard;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "inline_keyboard", inlineKeyboard);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "inline_keyboard", inlineKeyboard, false);
        }
    };
}