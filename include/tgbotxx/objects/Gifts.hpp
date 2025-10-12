#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Gift.hpp>

namespace tgbotxx {

  /// @brief This object represents a list of gifts.
  /// @ref https://core.telegram.org/bots/api#gifts
  struct Gifts {
    Gifts() = default;
    explicit Gifts(const nl::json& json) {
      fromJson(json);
    }

    /// @brief The list of gifts
    std::vector<Ptr<Gift>> gifts;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "gifts", gifts);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "gifts", gifts, false);
    }
  };

}
