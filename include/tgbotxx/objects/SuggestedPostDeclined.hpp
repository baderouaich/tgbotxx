#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/Message.hpp>

namespace tgbotxx {
  /// @brief Describes a service message about the rejection of a suggested post.
  /// @ref https://core.telegram.org/bots/api#suggestedpostdeclined
  struct SuggestedPostDeclined {
    SuggestedPostDeclined() = default;
    explicit SuggestedPostDeclined(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Optional. Message containing the suggested post
    Ptr<Message> suggestedPostMessage;

    /// @brief Optional. Comment with which the post was declined
    std::string comment;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage);
      OBJECT_SERIALIZE_FIELD(json, "comment", comment);
      return json;
    }
    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD_PTR(json, "suggested_post_message", suggestedPostMessage, true);
      OBJECT_DESERIALIZE_FIELD(json, "comment", comment, "", true);
    }
  };

}
