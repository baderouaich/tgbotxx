#pragma once
#include <tgbotxx/objects/LabeledPrice.hpp>
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents one shipping option.
  /// @ref https://core.telegram.org/bots/api#shippingoption
  struct ShippingOption {
      ShippingOption() = default;
      explicit ShippingOption(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Shipping option identifier
      std::string id;

      /// @brief Option title
      std::string title;

      /// @brief List of price portions
      std::vector<Ptr<LabeledPrice>> prices;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "id", id);
        OBJECT_SERIALIZE_FIELD(json, "title", title);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "prices", prices);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "title", title, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "prices", prices, false);
      }
  };
}