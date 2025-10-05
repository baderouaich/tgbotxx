#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/SuggestedPostPrice.hpp>

namespace tgbotxx {

  /// @brief Describes a service message about the approval of a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostapproved
  struct SuggestedPostApproved {
    SuggestedPostApproved() = default;
    explicit SuggestedPostApproved(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the suggested post
    Ptr<Message> suggestedPostMessage;

    /// @brief Optional. Amount paid for the post
    Ptr<SuggestedPostPrice> price;

    /// @brief Date when the post will be published
    std::time_t sendDate{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage);
      OBJECT_SERIALIZE_FIELD_PTR(json, "price", price);
      OBJECT_SERIALIZE_FIELD(json, "send_date", sendDate);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "price", price, true);
      OBJECT_DESERIALIZE_FIELD(json, "send_date", sendDate, 0, false);
    }
  };

}
