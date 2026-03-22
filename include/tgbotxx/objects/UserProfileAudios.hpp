#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Audio.hpp>

namespace tgbotxx {
  /// @brief This object represents the audios displayed on a user's profile.
  /// @ref https://core.telegram.org/bots/api#userprofileaudios
  struct UserProfileAudios {
    UserProfileAudios() = default;
    explicit UserProfileAudios(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Total number of profile audios for the target user
    std::int32_t totalCount;

    /// @brief Requested profile audios
    std::vector<Ptr<Audio>> audios;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "total_count", totalCount);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "audios", audios);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "total_count", totalCount, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "audios", audios, false);
    }
  };
}