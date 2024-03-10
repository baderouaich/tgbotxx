#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents an error in the Telegram Passport element which was submitted that should be resolved by the user.
  /// It should be one of:
  /// - PassportElementErrorDataField
  /// - PassportElementErrorFrontSide
  /// - PassportElementErrorReverseSide
  /// - PassportElementErrorSelfie
  /// - PassportElementErrorFile
  /// - PassportElementErrorFiles
  /// - PassportElementErrorTranslationFile
  /// - PassportElementErrorTranslationFiles
  /// - PassportElementErrorUnspecified
  /// @ref https://core.telegram.org/bots/api#passportelementerror
  struct PassportElementError {
      PassportElementError() = default;
      explicit PassportElementError(const nl::json& json) {
        _fromJson(json);
      }

      /// @brief Error source
      std::string source;

      /// @brief The section of the user's Telegram Passport which has the issue,
      /// one of “passport”, “driver_license”, “identity_card”, “internal_passport”
      std::string type;

      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      virtual nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "source", source);
        OBJECT_SERIALIZE_FIELD(json, "type", type);
        return json;
      }

      /// @brief Deserializes this object from JSON
      virtual void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "source", source, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
      }

    private:
      void _fromJson(const nl::json& json) {
        fromJson(json);
      }
  };

  /// @brief Represents an issue in one of the data fields that was provided by the user.
  /// The error is considered resolved when the field's value changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrordatafield
  struct PassportElementErrorDataField : PassportElementError {
      PassportElementErrorDataField() {
        PassportElementError::source = "data";
      }
      explicit PassportElementErrorDataField(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "data";
      }

      /// @brief Name of the data field which has the error
      std::string fieldName;

      /// @brief Base64-encoded data hash
      std::string dataHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "field_name", fieldName);
        OBJECT_SERIALIZE_FIELD(json, "data_hash", dataHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "field_name", fieldName, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "data_hash", dataHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with the front side of a document.
  /// The error is considered resolved when the file with the front side of the document changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorfrontside
  struct PassportElementErrorFrontSide : PassportElementError {
      PassportElementErrorFrontSide() {
        PassportElementError::source = "front_side";
      }
      explicit PassportElementErrorFrontSide(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "front_side";
      }

      /// @brief Base64-encoded hash of the file with the front side of the document
      std::string fileHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hash", fileHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hash", fileHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with the reverse side of a document.
  /// The error is considered resolved when the file with reverse side of the document changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorreverseside
  struct PassportElementErrorReverseSide : PassportElementError {
      PassportElementErrorReverseSide() {
        PassportElementError::source = "reverse_side";
      }
      explicit PassportElementErrorReverseSide(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "reverse_side";
      }

      /// @brief Base64-encoded hash of the file with the front side of the document
      std::string fileHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hash", fileHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hash", fileHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with the selfie with a document.
  /// The error is considered resolved when the file with the selfie changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorselfie
  struct PassportElementErrorSelfie : PassportElementError {
      PassportElementErrorSelfie() {
        PassportElementError::source = "selfie";
      }
      explicit PassportElementErrorSelfie(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "selfie";
      }

      /// @brief Base64-encoded hash of the file with the selfie
      std::string fileHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hash", fileHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hash", fileHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with a document scan.
  /// The error is considered resolved when the file with the document scan changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorfile
  struct PassportElementErrorFile : PassportElementError {
      PassportElementErrorFile() {
        PassportElementError::source = "file";
      }
      explicit PassportElementErrorFile(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "file";
      }

      /// @brief Base64-encoded file hash
      std::string fileHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hash", fileHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hash", fileHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };


  /// @brief Represents an issue with a list of scans.
  /// The error is considered resolved when the list of files containing the scans changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorfiles
  struct PassportElementErrorFiles : PassportElementError {
      PassportElementErrorFiles() {
        PassportElementError::source = "files";
      }
      explicit PassportElementErrorFiles(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "files";
      }

      /// @brief List of base64-encoded file hashes
      std::vector<std::string> fileHashes;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hashes", fileHashes);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hashes", fileHashes, {}, false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with one of the files that constitute the translation of a document.
  /// The error is considered resolved when the file changes.
  /// @ref https://core.telegram.org/bots/api#passportelementerrortranslationfile
  struct PassportElementErrorTranslationFile : PassportElementError {
      PassportElementErrorTranslationFile() {
        PassportElementError::source = "translation_file";
      }
      explicit PassportElementErrorTranslationFile(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "translation_file";
      }

      /// @brief Base64-encoded file hash
      std::string fileHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hash", fileHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hash", fileHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue with the translated version of a document.
  /// The error is considered resolved when a file with the document translation change.
  /// @ref https://core.telegram.org/bots/api#passportelementerrortranslationfiles
  struct PassportElementErrorTranslationFiles : PassportElementError {
      PassportElementErrorTranslationFiles() {
        PassportElementError::source = "translation_files";
      }
      explicit PassportElementErrorTranslationFiles(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "translation_files";
      }

      /// @brief List of base64-encoded file hashes
      std::vector<std::string> fileHashes;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "file_hashes", fileHashes);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "file_hashes", fileHashes, {}, false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

  /// @brief Represents an issue in an unspecified place.
  /// The error is considered resolved when new data is added.
  /// @ref https://core.telegram.org/bots/api#passportelementerrorunspecified
  struct PassportElementErrorUnspecified : PassportElementError {
      PassportElementErrorUnspecified() {
        PassportElementError::source = "unspecified";
      }
      explicit PassportElementErrorUnspecified(const nl::json& json) {
        PassportElementError::fromJson(json);
        PassportElementError::source = "unspecified";
      }

      /// @brief Base64-encoded element hash
      std::string elementHash;

      /// @brief Error message
      std::string message;

      nl::json toJson() const override {
        nl::json json = PassportElementError::toJson();
        OBJECT_SERIALIZE_FIELD(json, "element_hash", elementHash);
        OBJECT_SERIALIZE_FIELD(json, "message", message);
        return json;
      }
      void fromJson(const nl::json& json) override {
        PassportElementError::fromJson(json);
        OBJECT_DESERIALIZE_FIELD(json, "element_hash", elementHash, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "message", message, "", false);
      }
  };

}