#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {

  /// @brief This object contains information about a paid media purchase.
  /// @ref https://core.telegram.org/bots/api#paidmediapurchased
  struct PaidMediaPurchased {
    PaidMediaPurchased() = default;
    explicit PaidMediaPurchased(const nl::json& json) {
      fromJson(json);
    }

    /// @brief User who purchased the media
    Ptr<User> from;

    /// @brief Bot-specified paid media payload
    std::string paidMediaPayload;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
      OBJECT_SERIALIZE_FIELD(json, "paid_media_payload", paidMediaPayload);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
      OBJECT_DESERIALIZE_FIELD(json, "paid_media_payload", paidMediaPayload, "", false);
    }
  };

}
