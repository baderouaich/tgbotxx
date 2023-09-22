#pragma once
#include <string>
#include <iostream>
#include "utils/Ptr.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
namespace nl = nlohmann;

namespace tgbotxx {
    class Update;

    class Api {
        inline static const std::string BASE_URL = "https://api.telegram.org";
        inline static const cpr::Timeout TIMEOUT = 25 * 1000; // 25s
        inline static const cpr::ConnectTimeout CONNECT_TIMEOUT = 20 * 1000; // 20s
        std::string m_token;

    public:
        /// @brief Constructs Api object.
        /// @param token: Bot Token from FatherBot.
        Api(const std::string& token);

    public: /// @defgroup Api Methods
        /// @brief Use this method to remove webhook integration if you decide to switch back to getUpdates.
        /// Returns True on success.
        /// @param dropPendingUpdates: Pass True to drop all pending updates.
        /// @note when Bot is not running, updates will remain 24 hours in Telegram server before they get deleted or retrieved by BOT
        /// @note In order for Api::getUpdates() to work, there should be no outgoing webhook set up.
        /// see https://core.telegram.org/bots/api#getupdates
        /// @link ref https://core.telegram.org/bots/api#deletewebhook @endlink
        bool deleteWebhook(bool dropPendingUpdates = false) const;

        /// @brief Use this method to receive incoming updates using long polling.
        /// @returns an Array of Update objects.
        /// @note This method will not work if an outgoing webhook is set up.
        /// @note In order to avoid getting duplicate updates, recalculate offset after each server response.
        /// @link ref https://core.telegram.org/bots/api#getupdates @endlink
        std::vector<Ptr<Update>> getUpdates() const;

        // Todo: ...

    private:
        nl::json sendRequest(const std::string& endpoint, const cpr::Multipart& data = cpr::Multipart({})) const;
    };
}