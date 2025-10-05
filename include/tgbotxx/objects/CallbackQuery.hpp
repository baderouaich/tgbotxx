#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/MaybeInaccessibleMessage.hpp>
#include <tgbotxx/objects/User.hpp>

namespace nl = nlohmann;

namespace tgbotxx {
  /// Forward declarations
  struct Message;

  /// @brief This object represents an incoming callback query from a callback button in an inline keyboard.
  /// If the button that originated the query was attached to a message sent by the bot, the field message will be present.
  /// If the button was attached to a message sent via the bot (in inline mode), the field inline_message_id will be present.
  /// Exactly one of the fields data or game_short_name will be present.
  ///
  /// @note NOTE: After the user presses a callback button, Telegram clients will display a progress bar until you call answerCallbackQuery.
  /// It is, therefore, necessary to react by calling answerCallbackQuery even if no notification to the user is needed
  /// (e.g., without specifying any of the optional parameters).
  ///
  /// @ref https://core.telegram.org/bots/api#callbackquery
  struct CallbackQuery {
    CallbackQuery() = default;
    explicit CallbackQuery(const nl::json& json);

    /// @brief Unique identifier for this query
    std::string id;

    /// @brief Sender
    Ptr<User> from;

    /// @brief Optional. Message sent by the bot with the callback button that originated the query
    MaybeInaccessibleMessage message;

    /// @brief Optional. Identifier of the message sent via the bot in inline mode, that originated the query.
    std::string inlineMessageId;

    /// @brief Global identifier, uniquely corresponding to the chat to which the message with the callback button was sent.
    /// Useful for high scores in games.
    std::string chatInstance;

    /// @brief Optional. Data associated with the callback button.
    /// @note Be aware that the message originated the query can contain no callback buttons with this data.
    std::string data;

    /// @brief Optional. Short name of a Game to be returned, serves as the unique identifier for the game
    std::string gameShortName;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const;

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json);
  };
}
