#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief Describes data required for decrypting and authenticating EncryptedPassportElement.
    /// See the Telegram Passport Documentation for a complete description of the data decryption and authentication processes.
    /// @ref https://core.telegram.org/bots/api#encryptedcredentials
    struct EncryptedCredentials {
        explicit EncryptedCredentials(const nl::json& json) {
          fromJson(json);
        }

        /// @brief Base64-encoded encrypted JSON-serialized data with unique user's payload,
        /// data hashes and secrets required for EncryptedPassportElement decryption and authentication
        std::string data;

        /// @brief Base64-encoded data hash for data authentication
        std::string hash;

        /// @brief Base64-encoded secret, encrypted with the bot's public RSA key, required for data decryption
        std::string secret;


        /// @brief Serializes this object to JSON
        /// @returns JSON representation of this object
        nl::json toJson() const {
          nl::json json = nl::json::object();
          OBJECT_SERIALIZE_FIELD(json, "data", data);
          OBJECT_SERIALIZE_FIELD(json, "hash", hash);
          OBJECT_SERIALIZE_FIELD(json, "secret", secret);
          return json;
        }

        /// @brief Deserializes this object from JSON
        void fromJson(const nl::json &json) {
          OBJECT_DESERIALIZE_FIELD(json, "data", data, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "hash", hash, "", false);
          OBJECT_DESERIALIZE_FIELD(json, "secret", secret, "", false);
        }
    };
}