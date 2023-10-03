#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
  /// @brief This object represents a phone contact.
  /// @ref https://core.telegram.org/bots/api#contact
  struct Contact {
      Contact() = default;
      explicit Contact(const nl::json& json) {
        fromJson(json);
      }

      /// @brief Contact's phone number
      std::string phoneNumber;

      /// @brief Contact's first name
      std::string firstName;

      /// @brief Optional. Contact's last name
      std::string lastName;

      /// @brief Optional. Contact's user identifier in Telegram.
      /// This number may have more than 32 significant bits and some programming languages
      /// may have difficulty/silent defects in interpreting it. But it has at most 52 significant bits,
      /// so a 64-bit integer or double-precision float type are safe for storing this identifier.
      std::int64_t userId{};

      /// @brief Optional. Additional data about the contact in the form of a vCard
      /// @link vCard https://en.wikipedia.org/wiki/VCard @endlink
      std::string vcard;


      /// @brief Serializes this object to JSON
      /// @returns JSON representation of this object
      nl::json toJson() const {
        nl::json json = nl::json::object();
        OBJECT_SERIALIZE_FIELD(json, "phone_number", phoneNumber);
        OBJECT_SERIALIZE_FIELD(json, "first_name", firstName);
        OBJECT_SERIALIZE_FIELD(json, "last_name", lastName);
        OBJECT_SERIALIZE_FIELD(json, "user_id", userId);
        OBJECT_SERIALIZE_FIELD(json, "vcard", vcard);
        return json;
      }

      /// @brief Deserializes this object from JSON
      void fromJson(const nl::json& json) {
        OBJECT_DESERIALIZE_FIELD(json, "phone_number", phoneNumber, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "first_name", firstName, "", false);
        OBJECT_DESERIALIZE_FIELD(json, "last_name", lastName, "", true);
        OBJECT_DESERIALIZE_FIELD(json, "user_id", userId, 0, true);
        OBJECT_DESERIALIZE_FIELD(json, "vcard", vcard, "", true);
      }
  };
}