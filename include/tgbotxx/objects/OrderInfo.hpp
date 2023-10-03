#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ShippingAddress.hpp>

namespace tgbotxx {
  /// @brief This object represents information about an order.
  /// @ref https://core.telegram.org/bots/api#orderinfo
  struct OrderInfo {
      OrderInfo() = default;
      explicit OrderInfo(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Optional. User name
      std::string name;

      /// @brief Optional. User's phone number
      std::string phoneNumber;

      /// @brief Optional. User email
      std::string email;

      /// @brief Optional. User shipping address
      Ptr<ShippingAddress> shippingAddress;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "name", name);
        OBJECT_SERIALIZE_FIELD(json, "phone_number", phoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "email", email);
        OBJECT_SERIALIZE_FIELD_PTR(json, "shipping_address", shippingAddress, nl::json::object());
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "name", name, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "phone_number", phoneNumber, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "email", email, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "shipping_address", shippingAddress, true);
      }
  };
}
