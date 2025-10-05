#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/SuggestedPostPrice.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about the failed approval of a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostapprovalfailed
  struct SuggestedPostApprovalFailed {
    SuggestedPostApprovalFailed() = default;
    explicit SuggestedPostApprovalFailed(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the suggested post whose approval has failed
    Ptr<Message> suggestedPostMessage;

    /// @brief Expected price of the post
    Ptr<SuggestedPostPrice> price;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage);
      OBJECT_SERIALIZE_FIELD_PTR(json, "price", price);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "price", price, false);
    }
  };

}
