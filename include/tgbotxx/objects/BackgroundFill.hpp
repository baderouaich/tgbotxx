#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object describes the way a background is filled based on the selected colors.
  /// It can be one of:
  /// - BackgroundFillSolid
  /// - BackgroundFillGradient
  /// - BackgroundFillFreeformGradient
  /// @ref https://core.telegram.org/bots/api#backgroundfill
  struct BackgroundFill {
    BackgroundFill() = default;
    explicit BackgroundFill(const nl::json& json) {
      BackgroundFill::fromJson(json);
    }
    virtual ~BackgroundFill() = default;

    /// @brief Type of the background fill, one of "solid", "gradient", "freeform_gradient"
    std::string type;

    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief The background is filled using the selected solid color.
  /// @ref https://core.telegram.org/bots/api#backgroundfillsolid
  struct BackgroundFillSolid : BackgroundFill {
    BackgroundFillSolid() = default;
    explicit BackgroundFillSolid(const nl::json& json) {
      BackgroundFillSolid::fromJson(json);
      // BackgroundFill::type = "solid";
    }

    /// @brief The color of the background fill in the RGB24 format
    std::int32_t color{};

    nl::json toJson() const override {
      nl::json json = BackgroundFill::toJson();
      OBJECT_SERIALIZE_FIELD(json, "color", color);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundFill::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "color", color, 0, false);
    }
  };

  /// @brief The background is a gradient fill.
  /// @ref https://core.telegram.org/bots/api#backgroundfillgradient
  struct BackgroundFillGradient : BackgroundFill {
    BackgroundFillGradient() = default;
    explicit BackgroundFillGradient(const nl::json& json) {
      BackgroundFillGradient::fromJson(json);
      // BackgroundFill::type = "gradient";
    }

    /// @brief Top color of the gradient in the RGB24 format
    std::int32_t topColor{};

    /// @brief Bottom color of the gradient in the RGB24 format
    std::int32_t bottomColor{};

    /// @brief Clockwise rotation angle of the background fill in degrees; 0-359
    std::int32_t rotationAngle{};

    nl::json toJson() const override {
      nl::json json = BackgroundFill::toJson();
      OBJECT_SERIALIZE_FIELD(json, "top_color", topColor);
      OBJECT_SERIALIZE_FIELD(json, "bottom_color", bottomColor);
      OBJECT_SERIALIZE_FIELD(json, "rotation_angle", rotationAngle);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundFill::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "top_color", topColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "bottom_color", bottomColor, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "rotation_angle", rotationAngle, 0, false);
    }
  };

  /// @brief The background is a freeform gradient that rotates after every message in the chat.
  /// @ref https://core.telegram.org/bots/api#backgroundfillfreeformgradient
  struct BackgroundFillFreeformGradient : BackgroundFill {
    BackgroundFillFreeformGradient() = default;
    explicit BackgroundFillFreeformGradient(const nl::json& json) {
      BackgroundFillFreeformGradient::fromJson(json);
      // BackgroundFill::type = "freeform_gradient";
    }

    /// @brief A list of 3 or 4 base colors that are used to generate the freeform gradient in the RGB24 format
    std::vector<std::int32_t> colors;

    nl::json toJson() const override {
      nl::json json = BackgroundFill::toJson();
      OBJECT_SERIALIZE_FIELD(json, "colors", colors);
      return json;
    }

    void fromJson(const nl::json& json) override {
      BackgroundFill::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "colors", colors, {}, false);
    }
  };

}
