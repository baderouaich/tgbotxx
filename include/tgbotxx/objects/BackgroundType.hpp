#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/BackgroundFill.hpp>
#include <tgbotxx/objects/Document.hpp>

namespace tgbotxx {
  /// @brief This object describes the type of a background.
  /// It can be one of:
  /// - BackgroundTypeFill
  /// - BackgroundTypeWallpaper
  /// - BackgroundTypePattern
  /// - BackgroundTypeChatTheme
  /// @ref https://core.telegram.org/bots/api#backgroundtype
  struct BackgroundType {
    BackgroundType() = default;
    explicit BackgroundType(const nl::json& json) {
      BackgroundType::fromJson(json);
    }
    virtual ~BackgroundType() = default;

    /// @brief Type of the background, one of "fill", "wallpaper", "pattern", "chat_theme"
    std::string type;

    virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief The background is automatically filled based on the selected colors.
  /// @ref https://core.telegram.org/bots/api#backgroundtypefill
  struct BackgroundTypeFill : BackgroundType {
    BackgroundTypeFill() {
      type = "fill";
    }
    explicit BackgroundTypeFill(const nl::json& json) {
      BackgroundTypeFill::fromJson(json);
    }

    /// @brief The background fill
    Ptr<BackgroundFill> fill;

    /// @brief Dimming of the background in dark themes, as a percentage; 0-100
    std::int32_t darkThemeDimming{};

    nl::json toJson() const override {
      nl::json json = BackgroundType::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "fill", fill);
      OBJECT_SERIALIZE_FIELD(json, "dark_theme_dimming", darkThemeDimming);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "fill", fill, false);
      OBJECT_DESERIALIZE_FIELD(json, "dark_theme_dimming", darkThemeDimming, 0, false);
    }
  };

  /// @brief The background is a wallpaper in JPEG format.
  /// @ref https://core.telegram.org/bots/api#backgroundtypewallpaper
  struct BackgroundTypeWallpaper : BackgroundType {
    BackgroundTypeWallpaper() {
      type = "wallpaper";
    }
    explicit BackgroundTypeWallpaper(const nl::json& json){
      BackgroundTypeWallpaper::fromJson(json);
    }

    /// @brief Document with the wallpaper
    Ptr<Document> document;

    /// @brief Dimming of the background in dark themes, as a percentage; 0-100
    std::int32_t darkThemeDimming{};

    /// @brief Optional. True, if the wallpaper is downscaled to fit in a 450x450 square and then box-blurred with radius 12
    bool isBlurred{};

    /// @brief Optional. True, if the background moves slightly when the device is tilted
    bool isMoving{};

    nl::json toJson() const override {
      nl::json json = BackgroundType::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "document", document);
      OBJECT_SERIALIZE_FIELD(json, "dark_theme_dimming", darkThemeDimming);
      OBJECT_SERIALIZE_FIELD(json, "is_blurred", isBlurred);
      OBJECT_SERIALIZE_FIELD(json, "is_moving", isMoving);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "document", document, false);
      OBJECT_DESERIALIZE_FIELD(json, "dark_theme_dimming", darkThemeDimming, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_blurred", isBlurred, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_moving", isMoving, false, true);
    }
  };

  /// @brief The background is a PNG or TGV pattern combined with a fill.
  /// @ref https://core.telegram.org/bots/api#backgroundtypepattern
  struct BackgroundTypePattern : BackgroundType {
    BackgroundTypePattern() {
      type = "pattern";
    }
    explicit BackgroundTypePattern(const nl::json& json) {
      BackgroundTypePattern::fromJson(json);
    }

    /// @brief Document with the pattern
    Ptr<Document> document;

    /// @brief The background fill that is combined with the pattern
    Ptr<BackgroundFill> fill;

    /// @brief Intensity of the pattern when it is shown above the filled background; 0-100
    std::int32_t intensity{};

    /// @brief Optional. True, if the background fill must be applied only to the pattern itself. All other pixels are black in this case. For dark themes only
    bool isInverted{};

    /// @brief Optional. True, if the background moves slightly when the device is tilted
    bool isMoving{};

    nl::json toJson() const override {
      nl::json json = BackgroundType::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "document", document);
      OBJECT_SERIALIZE_FIELD_PTR(json, "fill", fill);
      OBJECT_SERIALIZE_FIELD(json, "intensity", intensity);
      OBJECT_SERIALIZE_FIELD(json, "is_inverted", isInverted);
      OBJECT_SERIALIZE_FIELD(json, "is_moving", isMoving);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "document", document, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "fill", fill, false);
      OBJECT_DESERIALIZE_FIELD(json, "intensity", intensity, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_inverted", isInverted, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_moving", isMoving, false, true);
    }
  };

  /// @brief The background is taken directly from a built-in chat theme.
  /// @ref https://core.telegram.org/bots/api#backgroundtypechattheme
  struct BackgroundTypeChatTheme : BackgroundType {
    BackgroundTypeChatTheme() {
      type = "chat_theme";
    }
    explicit BackgroundTypeChatTheme(const nl::json& json) {
      BackgroundTypeChatTheme::fromJson(json);
    }

    /// @brief Name of the chat theme, which is usually an emoji
    std::string themeName;

    nl::json toJson() const override {
      nl::json json = BackgroundType::toJson();
      OBJECT_SERIALIZE_FIELD(json, "theme_name", themeName);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundType::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "theme_name", themeName, "", false);
    }
  };

}
