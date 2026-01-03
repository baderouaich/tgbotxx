#pragma once
#include <tgbotxx/objects/IReplyMarkup.hpp>
#include <tgbotxx/objects/KeyboardButton.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a [custom keyboard](https://core.telegram.org/bots/features#keyboards) with reply options
  /// (see [Introduction to bots](https://core.telegram.org/bots/features#keyboards) for details and examples).
  /// @ref https://core.telegram.org/bots/api#replykeyboardmarkup
  struct ReplyKeyboardMarkup : IReplyMarkup {
      ReplyKeyboardMarkup() = default;
      explicit ReplyKeyboardMarkup(const nl::json& json) {
        ReplyKeyboardMarkup::fromJson(json);
      }

      /// @brief Array of button rows, each represented by an Array of KeyboardButton objects
      /// @type Array of Array of KeyboardButton
      std::vector<std::vector<Ptr<KeyboardButton>>> keyboard;

      /// @brief Optional. Requests clients to always show the keyboard when the regular keyboard is hidden.
      /// Defaults to false, in which case the custom keyboard can be hidden and opened with a keyboard icon.
      bool isPersistent{};

      /// @brief Optional. Requests clients to resize the keyboard vertically for optimal fit
      /// (e.g., make the keyboard smaller if there are just two rows of buttons).
      /// Defaults to false, in which case the custom keyboard is always of the same height as the app's standard keyboard.
      bool resizeKeyboard{};

      /// @brief Optional. Requests clients to hide the keyboard as soon as it's been used.
      /// The keyboard will still be available, but clients will automatically display the usual letter-keyboard in
      /// the chat - the user can press a special button in the input field to see the custom keyboard again.
      /// Defaults to false.
      bool oneTimeKeyboard{};

      /// @brief Optional. The placeholder to be shown in the input field when the keyboard is active; 1-64 characters
      std::string inputFieldPlaceholder;

      /// @brief Optional. Use this parameter if you want to show the keyboard to specific users only.
      /// Targets:
      /// - 1) users that are @mentioned in the text of the Message object;
      /// - 2) if the bot's message is a reply (has reply_to_message_id), sender of the original message.
      ///
      /// Example A user requests to change the bot's language, bot replies to the request with a keyboard to select the new language.
      /// Other users in the group don't see the keyboard.
      bool selective{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      [[nodiscard]] nl::json toJson() const override {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, "keyboard", keyboard);
        OBJECT_SERIALIZE_FIELD(json, "is_persistent", isPersistent);
        OBJECT_SERIALIZE_FIELD(json, "resize_keyboard", resizeKeyboard);
        OBJECT_SERIALIZE_FIELD(json, "one_time_keyboard", oneTimeKeyboard);
        OBJECT_SERIALIZE_FIELD(json, "input_field_placeholder", inputFieldPlaceholder);
        OBJECT_SERIALIZE_FIELD(json, "selective", selective);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) override {
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, "keyboard", keyboard, false);
        OBJECT_DESERIALIZE_FIELD(json, "is_persistent", isPersistent, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "resize_keyboard", resizeKeyboard, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "one_time_keyboard", oneTimeKeyboard, false, true);
        OBJECT_DESERIALIZE_FIELD(json, "input_field_placeholder", inputFieldPlaceholder, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "selective", selective, false, true);
      }
  };
}