#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief Describes a topic of a direct messages chat.
  /// @ref https://core.telegram.org/bots/api#directmessagestopic
  struct DirectMessagesTopic {
    DirectMessagesTopic() = default;
    explicit DirectMessagesTopic(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Unique identifier of the topic.
    /// This number may have more than 32 significant bits and some programming languages may have difficulty/silent defects in interpreting it.
    /// But it has at most 52 significant bits, so a 64-bit integer or double-precision float type are safe for storing this identifier.
    std::int64_t topicId{};

    /// @brief Optional. Information about the user that created the topic. Currently, it is always present
    Ptr<User> user;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "topic_id", topicId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "topic_id", topicId, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
    }
  };
}