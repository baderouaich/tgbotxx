#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/OwnedGift.hpp>

namespace tgbotxx {

  /// @brief Contains the list of gifts received and owned by a user or a chat.
  /// @ref https://core.telegram.org/bots/api#ownedgifts
  struct OwnedGifts {
    OwnedGifts() = default;
    explicit OwnedGifts(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The total number of gifts owned by the user or the chat
    std::int32_t totalCount{};

    /// @brief The list of gifts
    std::vector<Ptr<OwnedGift>> gifts;

    /// @brief Optional. Offset for the next request. If empty, then there are no more results
    std::string nextOffset;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "total_count", totalCount);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "gifts", gifts);
      OBJECT_SERIALIZE_FIELD(json, "next_offset", nextOffset);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "total_count", totalCount, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "gifts", gifts, false);
      OBJECT_DESERIALIZE_FIELD(json, "next_offset", nextOffset, "", true);
    }
  };

}
