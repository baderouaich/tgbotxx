#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestUser.hpp>
#include <tgbotxx/objects/KeyboardButtonRequestChat.hpp>
#include <tgbotxx/objects/KeyboardButtonPollType.hpp>
#include <tgbotxx/objects/WebAppInfo.hpp>

namespace tgbotxx {
    /// @brief This object represents one button of the reply keyboard. For simple text buttons,
    /// String can be used instead of this object to specify the button text.
    /// The optional fields web_app, request_user, request_chat, request_contact, request_location, and request_poll are mutually exclusive.
    /// @ref https://core.telegram.org/bots/api#keyboardbutton
    struct KeyboardButton {
        explicit KeyboardButton(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Text of the button. If none of the optional fields are used, it will be sent as a message when the button is pressed
        std::string text;

        /// @brief Optional. If specified, pressing the button will open a list of suitable users.
        /// Tapping on any user will send their identifier to the bot in a “user_shared” service message.
        /// @note Available in private chats only.
        Ptr<KeyboardButtonRequestUser> requestUser;

        /// @brief Optional. If specified, pressing the button will open a list of suitable chats.
        /// Tapping on a chat will send its identifier to the bot in a “chat_shared” service message.
        /// @note Available in private chats only.
        Ptr<KeyboardButtonRequestChat> requestChat;

        /// @brief Optional. If True, the user's phone number will be sent as a contact when the button is pressed.
        /// @note Available in private chats only.
        bool requestContact;

        /// @brief Optional. If True, the user's current location will be sent when the button is pressed.
        /// @note Available in private chats only.
        bool requestLocation;

        /// @brief Optional. If specified, the user will be asked to create a poll and send it to the bot when the button is pressed.
        /// @note Available in private chats only.
        Ptr<KeyboardButtonPollType> requestPoll;

        /// @brief Optional. If specified, the described Web App will be launched when the button is pressed.
        /// The Web App will be able to send a “web_app_data” service message.
        /// @note Available in private chats only.
        Ptr<WebAppInfo> webApp;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "text", text);
          OBJECT_SERIALIZE_FIELD_PTR(json, "request_user", requestUser, nl::json::object());
          OBJECT_SERIALIZE_FIELD_PTR(json, "request_chat", requestChat, nl::json::object());
          OBJECT_SERIALIZE_FIELD(json, "request_contact", requestContact);
          OBJECT_SERIALIZE_FIELD(json, "request_location", requestLocation);
          OBJECT_SERIALIZE_FIELD_PTR(json, "request_poll", requestPoll, nl::json::object());
          OBJECT_SERIALIZE_FIELD_PTR(json, "web_app", webApp, nl::json::object());
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
            OBJECT_DESERIALIZE_FIELD(json, "text", text, "", false);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "request_user", requestUser, true);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "request_chat", requestChat, true);
            OBJECT_DESERIALIZE_FIELD(json, "request_contact", requestContact, false, true);
            OBJECT_DESERIALIZE_FIELD(json, "request_location", requestLocation, false, true);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "request_poll", requestPoll, true);
            OBJECT_DESERIALIZE_FIELD_PTR(json, "web_app", webApp, true);
        }
    };
}