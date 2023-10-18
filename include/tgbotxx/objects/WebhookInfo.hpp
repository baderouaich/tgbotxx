#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief Describes the current status of a webhook.
  /// @ref https://core.telegram.org/bots/api#webhookinfo
  struct WebhookInfo {
      WebhookInfo() = default;
      explicit WebhookInfo(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Webhook URL, may be empty if webhook is not set up
      std::string url;

      /// @brief True, if a custom certificate was provided for webhook certificate checks
      bool hasCustomCertificate{};

      /// @brief Number of updates awaiting delivery
      std::int32_t pendingUpdateCount{};

      /// @brief Optional. Currently used webhook IP address
      std::string ipAddress;

      /// @brief Optional. Unix time for the most recent error that happened when trying to deliver an update via webhook
      std::time_t lastErrorDate{};

      /// @brief Optional. Error message in human-readable format for the most recent error that happened when trying to deliver an update via webhook
      std::string lastErrorMessage;

      /// @brief Optional. Unix time of the most recent error that happened when trying to synchronize available updates with Telegram datacenters
      std::time_t lastSynchronizationErrorDate{};

      /// @brief Optional. The maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery
      std::int32_t maxConnections{};

      /// @brief Optional. A list of update types the bot is subscribed to. Defaults to all update types except chat_member
      std::vector<std::string> allowedUpdates;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "url", url);
        OBJECT_SERIALIZE_FIELD(json, "has_custom_certificate", hasCustomCertificate);
        OBJECT_SERIALIZE_FIELD(json, "pending_update_count", pendingUpdateCount);
        OBJECT_SERIALIZE_FIELD(json, "ip_address", ipAddress);
        OBJECT_SERIALIZE_FIELD(json, "last_error_date", lastErrorDate);
        OBJECT_SERIALIZE_FIELD(json, "last_error_message", lastErrorMessage);
        OBJECT_SERIALIZE_FIELD(json, "last_synchronization_error_date", lastSynchronizationErrorDate);
        OBJECT_SERIALIZE_FIELD(json, "max_connections", maxConnections);
        OBJECT_SERIALIZE_FIELD(json, "allowed_updates", allowedUpdates);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "url", url, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "has_custom_certificate", hasCustomCertificate, false, false);
        OBJECT_DESERIALIZE_FIELD(json, "pending_update_count", pendingUpdateCount, 0, false);
        OBJECT_DESERIALIZE_FIELD(json, "ip_address", ipAddress, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "last_error_date", lastErrorDate, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "last_error_message", lastErrorMessage, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "last_synchronization_error_date", lastSynchronizationErrorDate, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "max_connections", maxConnections, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "allowed_updates", allowedUpdates, std::vector<std::string>(), true);
      }
  };
}