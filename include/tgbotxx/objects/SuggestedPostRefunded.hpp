#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about a payment refund for a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostrefunded
  struct SuggestedPostRefunded {
    SuggestedPostRefunded() = default;
    explicit SuggestedPostRefunded(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the suggested post.
    /// Note that the Message object in this field will not contain the reply_to_message field even if it itself is a reply.
    Ptr<Message> suggestedPostMessage;

    /// @brief Reason for the refund.
    /// Currently, one of “post_deleted” if the post was deleted within 24 hours of being posted or removed from scheduled messages without being posted,
    /// or “payment_refunded” if the payer refunded their payment.
    std::string reason;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage);
      OBJECT_SERIALIZE_FIELD(json, "reason", reason);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage, true);
      OBJECT_DESERIALIZE_FIELD(json, "reason", reason, "", false);
    }
  };

}
