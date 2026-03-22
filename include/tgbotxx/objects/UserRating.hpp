#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object describes the rating of a user based on their Telegram Star spendings.
  /// @ref https://core.telegram.org/bots/api#userrating
  struct UserRating {
    UserRating() = default;
    explicit UserRating(const nl::json& json);

    /// @brief Current level of the user, indicating their reliability when purchasing digital goods and services.
    /// A higher level suggests a more trustworthy customer; a negative level is likely reason for concern.
    std::int32_t level{};

    /// @brief Numerical value of the user's rating; the higher the rating, the better
    std::int32_t rating{};

    /// @brief The rating value required to get the current level
    std::int32_t currentLevelRating{};

    /// @brief Optional. The rating value required to get to the next level; omitted if the maximum level was reached
    std::int32_t nextLevelRating{};


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "level", level);
      OBJECT_SERIALIZE_FIELD(json, "rating", rating);
      OBJECT_SERIALIZE_FIELD(json, "current_level_rating", currentLevelRating);
      OBJECT_SERIALIZE_FIELD(json, "next_level_rating", nextLevelRating);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "level", level, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "rating", rating, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "current_level_rating", currentLevelRating, 0, false);
      OBJECT_DESERIALIZE_FIELD(json, "next_level_rating", nextLevelRating, 0, true);
    }
  };
}