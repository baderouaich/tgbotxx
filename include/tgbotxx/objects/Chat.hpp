#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a chat.
  /// @ref https://core.telegram.org/bots/api#chat
  struct Chat {
    Chat() = default;
    explicit Chat(const nl::json& json);
    virtual ~Chat() = default;

    /// @brief Unique identifier for this chat.
    /// @note This number may have more than 32 significant bits and some programming languages may have
    /// difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
    /// so a signed 64-bit integer or double-precision float type are safe for storing this identifier.
    std::int64_t id{};

    /// @brief Enum of possible types of Type.
    enum class Type : std::uint8_t {
      Private = 0,
      Group,
      Supergroup,
      Channel
    };
    /// @brief Converts enum Type to a string
    static std::optional<std::string> TypeToString(const Type type) noexcept;
    /// @brief Converts string to an enum Type
    static std::optional<Type> StringToType(const std::string& str) noexcept;

    /// @brief Type of chat, can be either “private”, “group”, “supergroup” or “channel”
    Type type{};

    /// @brief Optional. Title, for supergroups, channels and group chats
    std::string title;

    /// @brief Optional. Username, for private chats, supergroups and channels if available
    std::string username;

    /// @brief Optional. First name of the other party in a private chat
    std::string firstName;

    /// @brief Optional. Last name of the other party in a private chat
    std::string lastName;

    /// @brief Optional. True, if the supergroup chat is a forum (has topics enabled)
    /// @link topics https://telegram.org/blog/topics-in-groups-collectible-usernames#topics-in-groups @endlink
    bool isForum{};

    /// @brief Optional. True, if the supergroup chat is a forum (has topics enabled)
    /// @link topics https://telegram.org/blog/topics-in-groups-collectible-usernames#topics-in-groups @endlink
    bool isDirectMessages{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] virtual nl::json toJson() const;

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json);

  private:
    void _fromJson(const nl::json& json);
  };
}