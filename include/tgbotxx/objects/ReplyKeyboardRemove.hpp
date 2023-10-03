#pragma once
#include <tgbotxx/objects/IReplyMarkup.hpp>

namespace tgbotxx {
  /// @brief Upon receiving a message with this object, Telegram clients will remove the current custom keyboard and
  /// display the default letter-keyboard. By default, custom keyboards are displayed until a new keyboard is sent by a bot.
  /// An exception is made for one-time keyboards that are hidden immediately after the user presses a button (see ReplyKeyboardMarkup).
  /// @ref https://core.telegram.org/bots/api#replykeyboardremove
  struct ReplyKeyboardRemove : IReplyMarkup {
      ReplyKeyboardRemove() = default;
      explicit ReplyKeyboardRemove(const nl::json& json) {
        _fromJson(json);
      }

      /// @brief Requests clients to remove the custom keyboard (user will not be able to summon this keyboard;
      /// if you want to hide the keyboard from sight but keep it accessible, use oneTimeKeyboard in ReplyKeyboardMarkup)
      bool removeKeyboard{};

      /// @brief Optional. Use this parameter if you want to remove the keyboard for specific users only.
      /// Targets:
      /// - 1) users that are @mentioned in the text of the Message object;
      /// - 2) if the bot's message is a reply (has reply_to_message_id), sender of the original message.
      ///
      /// @example A user votes in a poll, bot returns confirmation message in reply to the vote and removes the keyboard for that user,
      /// while still showing the keyboard with poll options to users who haven't voted yet.
      bool selective{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const override {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "remove_keyboard", removeKeyboard);
        OBJECT_SERIALIZE_FIELD(json, "selective", selective);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) override {
        OBJECT_DESERIALIZE_FIELD(json, "remove_keyboard", removeKeyboard, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "selective", selective, false, true);
      }

    private:
      /// @brief Just so we don't invoke virtual method fromJson() from constructor
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };
}