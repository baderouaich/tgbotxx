#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes a Web App.
  /// @ref https://core.telegram.org/bots/api#webappinfo
  struct WebAppInfo {
      WebAppInfo() = default;
      explicit WebAppInfo(const nl::json& json) {
        fromJson(json);
      }

      /// @brief An HTTPS URL of a Web App to be opened with additional data as specified in Initializing Web Apps
      /// @link Initializing Web Apps https://core.telegram.org/bots/webapps#initializing-mini-apps @endlink
      std::string url;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "url", url);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "url", url, "", false);
      }
  };
}