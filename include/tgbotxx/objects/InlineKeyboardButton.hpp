#pragma once
#include <tgbotxx/objects/CallbackGame.hpp>
#include <tgbotxx/objects/LoginUrl.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/SwitchInlineQueryChosenChat.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>

namespace tgbotxx {
  /// @brief This object represents one button of an inline keyboard. You must use exactly one of the optional fields.
  /// @ref https://core.telegram.org/bots/api#inlinekeyboardbutton
  struct InlineKeyboardButton {
      InlineKeyboardButton() = default;
      explicit InlineKeyboardButton(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Label text on the button
      std::string text;

      /// @brief Optional. HTTP or tg:// URL to be opened when the button is pressed.
      /// Links tg://user?id=<user_id> can be used to mention a user by their ID without using a username,
      /// if this is allowed by their privacy settings.
      std::string url;

      /// @brief Optional. Data to be sent in a callback query to the bot when button is pressed, 1-64 bytes
      std::string callbackData;

      /// @brief Optional. Description of the Web App that will be launched when the user presses the button.
      /// The Web App will be able to send an arbitrary message on behalf of the user using the method answerWebAppQuery.
      /// Available only in private chats between a user and the bot.
      Ptr<WebAppInfo> webApp;

      /// @brief Optional. An HTTPS URL used to automatically authorize the user.
      /// Can be used as a replacement for the Telegram Login Widget.
      Ptr<LoginUrl> loginUrl;

      /// @brief Optional. If set, pressing the button will prompt the user to select one of their chats,
      /// open that chat and insert the bot's username and the specified inline query in the input field.
      /// May be empty, in which case just the bot's username will be inserted.
      std::string switchInlineQuery;

      /// @brief Optional. If set, pressing the button will insert the bot's username and the specified inline query
      /// in the current chat's input field. May be empty, in which case only the bot's username will be inserted.
      ///
      /// This offers a quick way for the user to open your bot in inline mode in the same chat - good for selecting something from multiple options.
      std::string switchInlineQueryCurrentChat;

      /// @brief Optional. If set, pressing the button will prompt the user to select one of their chats of the specified type,
      /// open that chat and insert the bot's username and the specified inline query in the input field
      Ptr<SwitchInlineQueryChosenChat> switchInlineQueryChosenChat;

      /// @brief Optional. Description of the game that will be launched when the user presses the button.
      ///
      /// @note This type of button must always be the first button in the first row.
      Ptr<CallbackGame> callbackGame;

      /// @brief Optional. Specify True, to send a Pay button.
      ///
      /// @note This type of button must always be the first button in the first row and can only be used in invoice messages.
      bool pay{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "text", text);
        OBJECT_SERIALIZE_FIELD(json, "url", url);
        OBJECT_SERIALIZE_FIELD(json, "callback_data", callbackData);
        OBJECT_SERIALIZE_FIELD_PTR(json, "web_app", webApp);
        OBJECT_SERIALIZE_FIELD_PTR(json, "login_url", loginUrl);
        OBJECT_SERIALIZE_FIELD(json, "switch_inline_query", switchInlineQuery);
        OBJECT_SERIALIZE_FIELD(json, "switch_inline_query_current_chat", switchInlineQueryCurrentChat);
        OBJECT_SERIALIZE_FIELD_PTR(json, "switch_inline_query_chosen_chat", switchInlineQueryChosenChat);
        OBJECT_SERIALIZE_FIELD_PTR(json, "callback_game", callbackGame);
        OBJECT_SERIALIZE_FIELD(json, "pay", pay);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "url", url, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "callback_data", callbackData, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app", webApp, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "login_url", loginUrl, true);
        OBJECT_DESERIALIZE_FIELD(json, "switch_inline_query", switchInlineQuery, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "switch_inline_query_current_chat", switchInlineQueryCurrentChat, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "switch_inline_query_chosen_chat", switchInlineQueryChosenChat, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "callback_game", callbackGame, true);
        OBJECT_DESERIALIZE_FIELD(json, "pay", pay, false, true);
      }
  };
}
