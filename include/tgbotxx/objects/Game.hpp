#pragma once
#include <tgbotxx/objects/MessageEntity.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
  /// @brief This object represents a game. Use BotFather to create and edit games, their short names will act as unique identifiers.
  /// @ref https://core.telegram.org/bots/api#game
  struct Game {
      Game() = default;
      explicit Game(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Title of the game
      std::string title;

      /// @brief Description of the game
      std::string description;

      /// @brief Photo that will be displayed in the game message in chats.
      std::vector<Ptr<PhotoSize>> photo;

      /// @brief Optional. Brief description of the game or high scores included in the game message.
      /// Can be automatically edited to include current high scores for the game when the bot calls setGameScore,
      /// or manually edited using editMessageText.
      /// 0-4096 characters.
      std::string text;

      /// @brief Optional. Special entities that appear in text, such as usernames, URLs, bot commands, etc.
      std::vector<Ptr<MessageEntity>> textEntities;

      /// @brief Optional. Animation that will be displayed in the game message in chats. Upload via BotFather
      /// @link BotFather https://t.me/botfather @endlink
      Ptr<Animation> animation;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD(json, "description", description);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo);
        OBJECT_SERIALIZE_FIELD(json, "text", text);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities);
        OBJECT_SERIALIZE_FIELD_PTR(json, "animation", animation);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "description", description, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "photo", photo, false);
        OBJECT_DESERIALIZE_FIELD(json, "text", text, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "text_entities", textEntities, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "animation", animation, true);
      }
  };
}