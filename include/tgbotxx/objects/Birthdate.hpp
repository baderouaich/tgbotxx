#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes the birthdate of a user.
  /// @ref https://core.telegram.org/bots/api#birthdate
  struct Birthdate {
    Birthdate() = default;
    explicit Birthdate(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Day of the user's birth; 1-31
    std::int32_t day{};

    /// @brief Month of the user's birth; 1-12
    std::int32_t month{};

    /// @brief Optional. Year of the user's birth
    std::int32_t year{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "day", day);
      OBJECT_SERIALIZE_FIELD(json, "month", month);
      OBJECT_SERIALIZE_FIELD(json, "year", year);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "day", day, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "month", month, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "year", year, 0, true);
    }
  };
}