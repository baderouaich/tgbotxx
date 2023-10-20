#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>

namespace tgbotxx {
  /// @brief This object describes the bot's menu button in a private chat. It should be one of:
  /// - MenuButtonCommands
  /// - MenuButtonWebApp
  /// - MenuButtonDefault
  /// If a menu button other than MenuButtonDefault is set for a private chat, then it is applied in the chat.
  /// Otherwise the default menu button is applied.
  /// By default, the menu button opens the list of bot commands.
  /// @ref https://core.telegram.org/bots/api#menubuttondefault
  struct MenuButton {
      MenuButton() = default;
      explicit MenuButton(const nl::json& json) {
        _fromJson(json);
      }
      virtual ~MenuButton() = default;

      /// @brief Type of the button
      std::string type;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      virtual nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        return json;
      }

      /// @brief Deserializes this object from JSON
      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      }

    private:
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };

  /// @brief Describes that no specific value for the menu button was set.
  /// @ref https://core.telegram.org/bots/api#menubuttondefault
  struct MenuButtonDefault : MenuButton {
      MenuButtonDefault() {
        MenuButton::type = "default";
      }
      explicit MenuButtonDefault(const nl::json& json) : MenuButton(json) {
        MenuButton::type = "default";
      }
  };

  /// @brief Represents a menu button, which launches a Web App. https://core.telegram.org/bots/webapps
  /// @ref https://core.telegram.org/bots/api#menubuttonwebapp
  struct MenuButtonWebApp : MenuButton {
      MenuButtonWebApp() {
        MenuButton::type = "web_app";
      }
      explicit MenuButtonWebApp(const nl::json& json) : MenuButton(json) {
        MenuButton::type = "web_app";
      }

      /// @brief Text on the button
      std::string text;

      /// @brief Description of the Web App that will be launched when the user presses the button.
      /// The Web App will be able to send an arbitrary message on behalf of the user using the method answerWebAppQuery. https://core.telegram.org/bots/api#answerwebappquery
      Ptr<WebAppInfo> webApp;

      nl::json toJson() const override {
        nl::json json = MenuButton::toJson();
        OBJECT_SERIALIZE_FIELD(json, "text", text);
        OBJECT_SERIALIZE_FIELD_PTR(json, "web_app", webApp, nl::json::object());
        return json;
      }

      void fromJson(const nl::json& json) override {
        MenuButton::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app", webApp, false);
      }
  };

  /// @brief Represents a menu button, which opens the bot's list of commands.
  /// @ref https://core.telegram.org/bots/api#menubuttoncommands
  struct MenuButtonCommands : MenuButton {
      MenuButtonCommands() {
        MenuButton::type = "commands";
      }
      explicit MenuButtonCommands(const nl::json& json) : MenuButton(json) {
        MenuButton::type = "commands";
      }
  };

}