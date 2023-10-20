#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>

namespace tgbotxx {
  /// @brief This object represents a button to be shown above inline query results.
  /// You must use exactly one of the optional fields.
  /// @ref https://core.telegram.org/bots/api#inlinequeryresultsbutton
  struct InlineQueryResultsButton {
      InlineQueryResultsButton() = default;
      explicit InlineQueryResultsButton(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Label text on the button
      std::string text;

      /// @brief Optional. Description of the [Web App](https://core.telegram.org/bots/webapps) that will be launched when the user presses the button.
      /// The Web App will be able to switch back to the inline mode using the method [switchInlineQuery](https://core.telegram.org/bots/webapps#initializing-mini-apps) inside the Web App.
      Ptr<WebAppInfo> webApp;

      /// @brief Optional. [Deep-linking](https://core.telegram.org/bots/features#deep-linking) parameter for the /start message sent to the bot when a user presses the button.
      /// 1-64 characters, only A-Z, a-z, 0-9, _ and - are allowed.
      /// Example: An inline bot that sends YouTube videos can ask the user to connect the bot to their YouTube account to adapt search results accordingly.
      /// To do this, it displays a 'Connect your YouTube account' button above the results, or even before showing any.
      /// The user presses the button, switches to a private chat with the bot and, in doing so, passes a start parameter that instructs the bot to return an OAuth link.
      /// Once done, the bot can offer a [switch_inline](https://core.telegram.org/bots/api#inlinekeyboardmarkup) button so that the user can easily return to the chat where they wanted to use the bot's inline capabilities.
      std::string startParameter;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "text", text);
        OBJECT_SERIALIZE_FIELD_PTR(json, "web_app", webApp, nl::json::object());
        OBJECT_SERIALIZE_FIELD(json, "start_parameter", startParameter);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app", webApp, true);
        OBJECT_DESERIALIZE_FIELD(json, "start_parameter", startParameter, "", true);
      }
  };
}