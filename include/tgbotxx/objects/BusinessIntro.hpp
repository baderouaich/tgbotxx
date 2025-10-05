#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Sticker.hpp>

namespace tgbotxx {
  /// @brief Contains information about the start page settings of a Telegram Business account.
  /// @ref https://core.telegram.org/bots/api#businessintro
  struct BusinessIntro {
    BusinessIntro() = default;
    explicit BusinessIntro(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Title text of the business intro
    std::string title;

    /// @brief Optional. Message text of the business intro
    std::string message;

    /// @brief Optional. Sticker of the business intro
    Ptr<Sticker> sticker;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "title", title);
      OBJECT_SERIALIZE_FIELD(json, "message", message);
      OBJECT_SERIALIZE_FIELD_PTR(json, "sticker", sticker);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "title", title, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "message", message, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sticker", sticker, true);
    }
  };
}