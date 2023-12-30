#pragma once

#include <nlohmann/json.hpp>
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/ShippingAddress.hpp>
#include <tgbotxx/objects/User.hpp>

namespace nl = nlohmann;

namespace tgbotxx {
  /// @brief This object contains information about an incoming shipping query.
  /// @ref https://core.telegram.org/bots/api#shippingquery
  struct ShippingQuery {
      ShippingQuery() = default;
      explicit ShippingQuery(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Unique query identifier
      std::string id;

      /// @brief User who sent the query
      Ptr<User> from;

      /// @brief Bot specified invoice payload
      std::string invoicePayload;

      /// @brief User specified shipping address
      Ptr<ShippingAddress> shippingAddress;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "id", id);
        OBJECT_SERIALIZE_FIELD_PTR(json, "from", from);
        OBJECT_SERIALIZE_FIELD(json, "invoice_payload", invoicePayload);
        OBJECT_SERIALIZE_FIELD_PTR(json, "shipping_address", shippingAddress);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "id", id, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "from", from, false);
        OBJECT_DESERIALIZE_FIELD(json, "invoice_payload", invoicePayload, "", false);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "shipping_address", shippingAddress, false);
      }
  };
}
