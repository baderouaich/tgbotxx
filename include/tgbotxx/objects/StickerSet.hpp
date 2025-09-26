#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>
#include <tgbotxx/objects/Sticker.hpp>

namespace tgbotxx {
  /// @brief This object represents a sticker set.
  /// @ref https://core.telegram.org/bots/api#stickerset
  struct StickerSet {
    StickerSet() = default;
    explicit StickerSet(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Sticker set name
    std::string name;

    /// @brief Sticker set title
    std::string title;

    /// @brief Type of stickers in the set, currently one of “regular”, “mask”, “custom_emoji”
    Sticker::Type stickerType{};

    /// @brief List of all set stickers
    std::vector<Ptr<Sticker>> stickers;

    /// @brief Optional. Sticker set thumbnail in the .WEBP, .TGS, or .WEBM format
    Ptr<PhotoSize> thumbnail;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "name", name);
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      OBJECT_SERIALIZE_FIELD_ENUM(json, Sticker::Type, "sticker_type", stickerType);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "stickers", stickers);
      OBJECT_SERIALIZE_FIELD_PTR(json, "thumbnail", thumbnail);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
      stickerType = Sticker::StringToType(json["sticker_type"]).value(); // enum
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "stickers", stickers, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "thumbnail", thumbnail, true);
    }
  };
}