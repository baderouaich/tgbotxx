#pragma once
#include <tgbotxx/objects/File.hpp>
#include <tgbotxx/objects/MaskPosition.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
  /// @brief This object represents a sticker.
  /// @ref https://core.telegram.org/bots/api#sticker
  struct Sticker {
    Sticker() = default;
    explicit Sticker(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Identifier for this file, which can be used to download or reuse the file
    std::string fileId;

    /// @brief Unique identifier for this file, which is supposed to be the same over time and for different bots.
    /// Can't be used to download or reuse the file.
    std::string fileUniqueId;

    /// @brief Enum of possible types of Type.
    enum class Type : std::uint8_t {
      Regular = 0,
      Mask,
      CustomEmoji
    };
    /// @brief Converts enum Type to a string
    static std::optional<std::string> TypeToString(const Type type) noexcept {
      if (type == Type::Regular) return "regular";
      if (type == Type::Mask) return "mask";
      if (type == Type::CustomEmoji) return "custom_emoji";
      return std::nullopt;
    }
    /// @brief Converts string to an enum Type
    static std::optional<Type> StringToType(const std::string& str) noexcept {
      if (str == "regular") return Type::Regular;
      if (str == "mask") return Type::Mask;
      if (str == "custom_emoji") return Type::CustomEmoji;
      return std::nullopt;
    }
    /// @brief Type of the sticker, currently one of “regular”, “mask”, “custom_emoji”.
    /// The type of the sticker is independent from its format, which is determined by the fields is_animated and is_video.
    Type type{};

    /// @brief Sticker width
    std::int32_t width{};

    /// @brief Sticker height
    std::int32_t height{};

    /// @brief True, if the sticker is animated
    bool isAnimated{};

    /// @brief True, if the sticker is a video sticker
    bool isVideo{};

    /// @brief Optional. Sticker thumbnail in the .WEBP or .JPG format
    Ptr<PhotoSize> thumbnail;

    /// @brief Optional. Emoji associated with the sticker
    std::string emoji;

    /// @brief Optional. Name of the sticker set to which the sticker belongs
    std::string setName;

    /// @brief Optional. For premium regular stickers, premium animation for the sticker
    Ptr<File> premiumAnimation;

    /// @brief Optional. For mask stickers, the position where the mask should be placed
    Ptr<MaskPosition> maskPosition;

    /// @brief Optional. For custom emoji stickers, unique identifier of the custom emoji
    std::string customEmojiId;

    /// @brief Optional. True, if the sticker must be repainted to a text color in messages,
    /// the color of the Telegram Premium badge in emoji status, white color on chat photos,
    /// or another appropriate color in other places
    bool needsRepainting{};

    /// @brief Optional. File size in bytes.
    std::int64_t fileSize{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "file_id", fileId);
      OBJECT_SERIALIZE_FIELD(json, "file_unique_id", fileUniqueId);
      OBJECT_SERIALIZE_FIELD_ENUM(json, Type, "type", type);
      OBJECT_SERIALIZE_FIELD(json, "width", width);
      OBJECT_SERIALIZE_FIELD(json, "height", height);
      OBJECT_SERIALIZE_FIELD(json, "is_animated", isAnimated);
      OBJECT_SERIALIZE_FIELD(json, "is_video", isVideo);
      OBJECT_SERIALIZE_FIELD_PTR(json, "thumbnail", thumbnail);
      OBJECT_SERIALIZE_FIELD(json, "emoji", emoji);
      OBJECT_SERIALIZE_FIELD(json, "set_name", setName);
      OBJECT_SERIALIZE_FIELD_PTR(json, "premium_animation", premiumAnimation);
      OBJECT_SERIALIZE_FIELD_PTR(json, "mask_position", maskPosition);
      OBJECT_SERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId);
      OBJECT_SERIALIZE_FIELD(json, "needs_repainting", needsRepainting);
      OBJECT_SERIALIZE_FIELD(json, "file_size", fileSize);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "file_id", fileId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "file_unique_id", fileUniqueId, "", false);
      OBJECT_DESERIALIZE_FIELD_ENUM(json, Type, "type", type, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "width", width, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "height", height, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_animated", isAnimated, false, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_video", isVideo, false, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "thumbnail", thumbnail, true);
      OBJECT_DESERIALIZE_FIELD(json, "emoji", emoji, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "set_name", setName, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "premium_animation", premiumAnimation, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "mask_position", maskPosition, true);
      OBJECT_DESERIALIZE_FIELD(json, "custom_emoji_id", customEmojiId, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "needs_repainting", needsRepainting, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "file_size", fileSize, 0, true);
    }
  };
}