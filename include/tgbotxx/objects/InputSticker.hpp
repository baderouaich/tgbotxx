#pragma once
#include <cpr/file.h>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <variant>

namespace tgbotxx {
  /// @brief This object describes a sticker to be added to a sticker set.
  /// @ref https://core.telegram.org/bots/api#inputsticker
  struct InputSticker {
      InputSticker() = default;
      explicit InputSticker(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The added sticker.
      /// - Pass a file_id std::string to send a file that exists on the Telegram servers (recommended),
      /// - Pass an HTTP URL as an std::string for Telegram to get a .WEBP sticker from the Internet, or
      /// - Pass a cpr::File to upload a new .WEBP or .TGS sticker
      /// Animated and video stickers can't be uploaded via HTTP URL. [More information on Sending Files »](https://core.telegram.org/bots/api#sending-files)
      std::variant<std::monostate, cpr::File, std::string> sticker{};

      /// @brief Format of the added sticker, must be one of “static” for a .WEBP or .PNG image, “animated” for a .TGS animation, “video” for a .WEBM video
      std::string format;

      /// @brief List of 1-20 emoji associated with the sticker
      std::vector<std::string> emojiList;

      /// @brief Optional. Position where the mask should be placed on faces. For “mask” stickers only.
      Ptr<MaskPosition> maskPosition;

      /// @brief Optional. List of 0-20 search keywords for the sticker with total length of up to 64 characters.
      /// For “regular” and “custom_emoji” stickers only.
      std::vector<std::string> keywords;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        if (not std::holds_alternative<std::monostate>(sticker)) {
          // sticker variant
          if (std::holds_alternative<cpr::File>(sticker))
            json["sticker"] = std::get<cpr::File>(sticker).filepath;
          else
            json["sticker"] = std::get<std::string>(sticker);
        }
        OBJECT_SERIALIZE_FIELD(json, "format", format);
        OBJECT_SERIALIZE_FIELD(json, "emoji_list", emojiList);
        OBJECT_SERIALIZE_FIELD_PTR(json, "mask_position", maskPosition);
        OBJECT_SERIALIZE_FIELD(json, "keywords", keywords);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        // sticker variant, we can't get a local file from remote, so it's always a URL or file id std::string.
        OBJECT_DESERIALIZE_FIELD(json, "sticker", std::get<std::string>(sticker), "", false);
        OBJECT_DESERIALIZE_FIELD(json, "format", format, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "emoji_list", emojiList, std::vector<std::string>(), false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "mask_position", maskPosition, true);
        OBJECT_DESERIALIZE_FIELD(json, "keywords", keywords, std::vector<std::string>(), true);
      }
  };
}