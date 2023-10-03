#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a parameter of the inline keyboard button used to automatically authorize a user.
  /// Serves as a great replacement for the Telegram Login Widget when the user is coming from Telegram.
  /// All the user needs to do is tap/click a button and confirm that they want to log in:
  /// @image https://core.telegram.org/file/811140015/1734/8VZFkwWXalM.97872/6127fa62d8a0bf2b3c
  /// @note Telegram apps support these buttons as of version 5.7.
  /// @ref https://core.telegram.org/bots/api#loginurl
  struct LoginUrl {
      LoginUrl() = default;
      explicit LoginUrl(const nl::json& json) {
        fromJson(json);
      }

      /// @brief An HTTPS URL to be opened with user authorization data added to the query string when the button is pressed.
      /// If the user refuses to provide authorization data, the original URL without information about the user will be opened.
      /// The data added is the same as described in Receiving authorization data.
      ///
      /// @note You must always check the hash of the received data to verify the authentication and the integrity of the data as
      /// described in Checking authorization.
      std::string url;

      /// @brief Optional. New text of the button in forwarded messages.
      std::string forwardText;

      /// @brief Optional. Username of a bot, which will be used for user authorization. See Setting up a bot for more details.
      /// If not specified, the current bot's username will be assumed. The url's domain must be the same as the domain linked
      /// with the bot. See Linking your domain to the bot for more details.
      std::string botUsername;

      /// @brief Optional. Pass True to request the permission for your bot to send messages to the user.
      bool requestWriteAccess{};

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "url", url);
        OBJECT_SERIALIZE_FIELD(json, "forward_text", forwardText);
        OBJECT_SERIALIZE_FIELD(json, "bot_username", botUsername);
        OBJECT_SERIALIZE_FIELD(json, "request_write_access", requestWriteAccess);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "url", url, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "forward_text", forwardText, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "bot_username", botUsername, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "request_write_access", requestWriteAccess, false, true);
      }
  };
}