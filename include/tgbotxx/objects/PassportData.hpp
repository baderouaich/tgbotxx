#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/EncryptedPassportElement.hpp>
#include <tgbotxx/objects/EncryptedCredentials.hpp>

namespace tgbotxx {
    /// @brief Describes Telegram Passport data shared with the bot by the user.
    /// @ref https://core.telegram.org/bots/api#passportdata
    struct PassportData {
        explicit PassportData(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Array with information about documents and other Telegram Passport elements that was shared with the bot
        std::vector<Ptr<EncryptedPassportElement>> data;

        /// @brief Encrypted credentials required to decrypt the data
        Ptr<EncryptedCredentials> credentials;

        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "data", data);
          OBJECT_SERIALIZE_FIELD_PTR(json, "credentials", credentials, nl::json::object());
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "data", data, false);
          OBJECT_DESERIALIZE_FIELD_PTR(json, "credentials", credentials, false);
        }
    };
}