#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>

namespace tgbotxx {
  /// @brief This object describes the source of a chat boost. It can be one of:
  /// - ChatBoostSourcePremium
  /// - ChatBoostSourceGiftCode
  /// - ChatBoostSourceGiveaway
  /// @ref https://core.telegram.org/bots/api#chatboostsource
  struct ChatBoostSource {
    ChatBoostSource() = default;
    explicit ChatBoostSource(const nl::json& json) {
      ChatBoostSource::fromJson(json);
    }
    virtual ~ChatBoostSource() = default;

    /// @brief Source of the boost
    std::string source;


    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "source", source);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "source", source, "", false);
    }
  };

  /// @brief The boost was obtained by subscribing to Telegram Premium or by gifting a Telegram Premium subscription to another user.
  /// @ref https://core.telegram.org/bots/api#chatboostsourcepremium
  struct ChatBoostSourcePremium : ChatBoostSource {
    ChatBoostSourcePremium() = default;
    explicit ChatBoostSourcePremium(const nl::json& json) {
      ChatBoostSourcePremium::fromJson(json);
      // ChatBoostSource::source = "premium";
    }

    /// @brief User that boosted the chat
    Ptr<User> user;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = ChatBoostSource::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      return json;
    }
    void fromJson(const nl::json& json) override {
      ChatBoostSource::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
    }
  };

  /// @brief The boost was obtained by subscribing to Telegram Premium or by gifting a Telegram Premium subscription to another user.
  /// @ref https://core.telegram.org/bots/api#chatboostsourcegiftcode
  struct ChatBoostSourceGiftCode : ChatBoostSource {
    ChatBoostSourceGiftCode() = default;
    explicit ChatBoostSourceGiftCode(const nl::json& json) {
      ChatBoostSourceGiftCode::fromJson(json);
      // ChatBoostSourceGiftCode::source = "gift_code";
    }

    /// @brief User for which the gift code was created
    Ptr<User> user;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = ChatBoostSource::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      return json;
    }
    void fromJson(const nl::json& json) override {
      ChatBoostSource::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
    }
  };

  /// @brief The boost was obtained by the creation of a Telegram Premium giveaway.
  /// This boosts the chat 4 times for the duration of the corresponding Telegram Premium subscription.
  /// @ref https://core.telegram.org/bots/api#chatboostsourcegiveaway
  struct ChatBoostSourceGiveaway : ChatBoostSource {
    ChatBoostSourceGiveaway() = default;
    explicit ChatBoostSourceGiveaway(const nl::json& json) {
      ChatBoostSourceGiveaway::fromJson(json);
      // ChatBoostSourceGiveaway::source = "giveaway";
    }

    /// @brief Identifier of a message in the chat with the giveaway; the message could have been deleted already.
    /// May be 0 if the message isn't sent yet.
    std::int32_t giveawayMessageId{};

    /// @brief Optional. User that won the prize in the giveaway if any
    Ptr<User> user;

    /// @brief Optional. True, if the giveaway was completed, but there was no user to win the prize
    bool isUnclaimed{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = ChatBoostSource::toJson();
      OBJECT_SERIALIZE_FIELD(json, "giveaway_message_id", giveawayMessageId);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      OBJECT_SERIALIZE_FIELD(json, "is_unclaimed", isUnclaimed);
      return json;
    }
    void fromJson(const nl::json& json) override {
      ChatBoostSource::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "giveaway_message_id", giveawayMessageId, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_unclaimed", isUnclaimed, 0, true);
    }
  };


}