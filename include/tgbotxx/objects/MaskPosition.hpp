#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object describes the position on faces where a mask should be placed by default.
  /// @ref https://core.telegram.org/bots/api#maskposition
  struct MaskPosition {
      MaskPosition() = default;
      explicit MaskPosition(const nl::json& json) {
        fromJson(json);
      }

      /// @brief The part of the face relative to which the mask should be placed.
      /// One of “forehead”, “eyes”, “mouth”, or “chin”.
      std::string point;

      /// @brief Shift by X-axis measured in widths of the mask scaled to the face size, from left to right.
      /// For example, choosing -1.0 will place mask just to the left of the default mask position.
      float xShift{};

      /// @brief Shift by Y-axis measured in heights of the mask scaled to the face size, from top to bottom.
      /// For example, 1.0 will place the mask just below the default mask position.
      float yShift{};

      /// @brief Mask scaling coefficient. For example, 2.0 means double size.
      float scale{};


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "point", point);
        OBJECT_SERIALIZE_FIELD(json, "x_shift", xShift);
        OBJECT_SERIALIZE_FIELD(json, "y_shift", yShift);
        OBJECT_SERIALIZE_FIELD(json, "scale", scale);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "point", point, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "x_shift", xShift, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "y_shift", yShift, 0.0f, false);
        OBJECT_DESERIALIZE_FIELD(json, "scale", scale, 0.0f, false);
      }
  };
}