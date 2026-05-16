#pragma once

/// @brief Webhook settings
struct WebhookSettings {
  /// @param url HTTPS URL to send updates to.
  std::string url;
  /// @param certificateFile Optional. Upload your public key certificate so that the root certificate in use can be checked. See our self-signed guide for details.
  cpr::File certificateFile{""};
  /// @param privateKeyFile Optional. Set your webhook private key certificate. See our self-signed guide for details.
  cpr::File privateKeyFile{""};
  /// @brief Webhook local server (listener) port
  int port{8080};
  /// @param ipAddress Optional. The fixed IP address which will be used to send webhook requests instead of the IP address resolved through DNS
  std::string ipAddress{};
  /// @param maxConnections Optional. The maximum allowed number of simultaneous HTTPS connections to the webhook for update delivery, 1-100. Defaults to 40.
  /// Use lower values to limit the load on your bot's server, and higher values to increase your bot's throughput.
  std::int32_t maxConnections = 40;
  /// @param allowedUpdates Optional. A JSON-serialized list of the update types you want your bot to receive.
  /// For example, specify [“message”, “edited_channel_post”, “callback_query”] to only receive updates of these types.
  /// See Update for a complete list of available update types. Specify an empty list to receive all update types except chat_member (default).
  /// If not specified, the previous setting will be used.
  /// Please note that this parameter doesn't affect updates created before the call to the setWebhook, so unwanted updates may be received for a short period of time.
  std::vector<std::string> allowedUpdates{};
  /// @param dropPendingUpdates Optional. Pass True to drop all pending updates.
  bool dropPendingUpdates{false};
  /// @param secretToken Optional. A secret token to be sent in a header “X-Telegram-Bot-Api-Secret-Token” in every webhook request, 1-256 characters. Only characters A-Z, a-z, 0-9, _ and - are allowed.
  std::string secretToken;
};