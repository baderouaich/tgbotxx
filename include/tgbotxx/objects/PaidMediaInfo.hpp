#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PaidMedia.hpp>

namespace tgbotxx {
  /// @brief Describes the paid media added to a message.
  /// @ref https://core.telegram.org/bots/api#paidmediainfo
  struct PaidMediaInfo {
    PaidMediaInfo() = default;
    explicit PaidMediaInfo(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The number of Telegram Stars that must be paid to buy access to the media
    std::int64_t starCount{};

    /// @brief Information about the paid media
    std::vector<Ptr<PaidMedia>> paidMedia;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "star_count", starCount);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "paid_media", paidMedia);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "star_count", starCount, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "paid_media", paidMedia, false);
    }
  };
}