#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/PassportFile.hpp>

namespace tgbotxx {
  /// @brief Describes documents or other Telegram Passport elements shared with the bot by the user.
  /// @ref https://core.telegram.org/bots/api#encryptedpassportelement
  struct EncryptedPassportElement {
      EncryptedPassportElement() = default;
      explicit EncryptedPassportElement(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Element type.
      /// One of “personal_details”, “passport”, “driver_license”, “identity_card”, “internal_passport”, “address”,
      /// “utility_bill”, “bank_statement”, “rental_agreement”, “passport_registration”, “temporary_registration”,
      /// “phone_number”, “email”.
      std::string type;

      /// @brief Optional. Base64-encoded encrypted Telegram Passport element data provided by the user,
      /// available for “personal_details”, “passport”, “driver_license”, “identity_card”, “internal_passport” and “address” types.
      /// Can be decrypted and verified using the accompanying EncryptedCredentials.
      std::string data;

      /// @brief Optional. User's verified phone number, available only for “phone_number” type
      std::string phoneNumber;

      /// @brief Optional. User's verified email address, available only for “email” type
      std::string email;

      /// @brief Optional. Array of encrypted files with documents provided by the user, available for “utility_bill”,
      /// “bank_statement”, “rental_agreement”, “passport_registration” and “temporary_registration” types.
      /// Files can be decrypted and verified using the accompanying EncryptedCredentials.
      std::vector<Ptr<PassportFile>> files;

      /// @brief Optional. Encrypted file with the front side of the document, provided by the user.
      /// Available for “passport”, “driver_license”, “identity_card” and “internal_passport”.
      /// The file can be decrypted and verified using the accompanying EncryptedCredentials.
      Ptr<PassportFile> frontSide;

      /// @brief Optional. Encrypted file with the reverse side of the document, provided by the user. Available for “driver_license” and “identity_card”.
      /// The file can be decrypted and verified using the accompanying EncryptedCredentials.
      Ptr<PassportFile> reverseSide;

      /// @brief Optional. Encrypted file with the selfie of the user holding a document, provided by the user; available for “passport”, “driver_license”, “identity_card” and “internal_passport”.
      /// The file can be decrypted and verified using the accompanying EncryptedCredentials.
      Ptr<PassportFile> selfie;

      /// @brief Optional. Array of encrypted files with translated versions of documents provided by the user.
      /// Available if requested for “passport”, “driver_license”, “identity_card”, “internal_passport”, “utility_bill”,
      /// “bank_statement”, “rental_agreement”, “passport_registration” and “temporary_registration” types.
      /// Files can be decrypted and verified using the accompanying EncryptedCredentials.
      std::vector<Ptr<PassportFile>> translation;

      /// @brief Base64-encoded element hash for using in PassportElementErrorUnspecified
      std::string hash;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        OBJECT_SERIALIZE_FIELD(json, "data", data);
        OBJECT_SERIALIZE_FIELD(json, "phone_number", phoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "email", email);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "files", files);
        OBJECT_SERIALIZE_FIELD_PTR(json, "front_side", frontSide);
        OBJECT_SERIALIZE_FIELD_PTR(json, "reverse_side", reverseSide);
        OBJECT_SERIALIZE_FIELD_PTR(json, "selfie", selfie);
        OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "translation", translation);
        OBJECT_SERIALIZE_FIELD(json, "hash", hash);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "data", data, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "phone_number", phoneNumber, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "email", email, "", true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "files", files, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "front_side", frontSide, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "reverse_side", reverseSide, true);
        OBJECT_DESERIALIZE_FIELD_PTR(json, "selfie", selfie, true);
        OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "translation", translation, true);
        OBJECT_DESERIALIZE_FIELD(json, "hash", hash, "", false);
      }
  };
}