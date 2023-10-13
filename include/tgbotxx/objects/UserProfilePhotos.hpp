#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PhotoSize.hpp>

namespace tgbotxx {
  /// @brief This object represent a user's profile pictures.
  /// @ref https://core.telegram.org/bots/api#userprofilephotos
  struct UserProfilePhotos {
      UserProfilePhotos() = default;
      explicit UserProfilePhotos(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Total number of profile pictures the target user has
      std::int32_t totalCount{};

      /// @brief Requested profile pictures (in up to 4 sizes each)
      std::vector<std::vector<Ptr<PhotoSize>>> photos;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "total_count", totalCount);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, "photos", photos);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "total_count", totalCount, 0, false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY_ARRAY(json, "photos", photos, false);
      }
  };
}