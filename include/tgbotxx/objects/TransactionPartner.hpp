#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/objects/Chat.hpp>
#include <tgbotxx/objects/Gift.hpp>
#include <tgbotxx/objects/AffiliateInfo.hpp>
#include <tgbotxx/objects/PaidMedia.hpp>
#include <tgbotxx/objects/RevenueWithdrawalState.hpp>
#include <vector>

namespace tgbotxx {

  /// @brief Base class for all transaction partners
  /// @ref https://core.telegram.org/bots/api#transactionpartner
  struct TransactionPartner {
    TransactionPartner() = default;
    explicit TransactionPartner(const nl::json& json) {
      TransactionPartner::fromJson(json);
    }
    virtual ~TransactionPartner() = default;

    /// @brief Type of the transaction partner
    std::string type;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] virtual nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "type", type);
      return json;
    }

    /// @brief Deserializes this object from JSON
    virtual void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "type", type, "", false);
    }
  };

  /// @brief Describes a transaction with a user.
  struct TransactionPartnerUser : TransactionPartner {
    TransactionPartnerUser() = default;
    explicit TransactionPartnerUser(const nl::json& json) {
      TransactionPartnerUser::fromJson(json);
      // TransactionPartner::type = "user";
    }

    /// @brief Type of the transaction, e.g., "invoice_payment", "paid_media_payment", etc.
    std::string transactionType;

    /// @brief Information about the user
    Ptr<User> user;

    /// @brief Optional. Affiliate that received a commission via this transaction
    Ptr<AffiliateInfo> affiliate;

    /// @brief Optional. Bot-specified invoice payload
    std::string invoicePayload;

    /// @brief Optional. Duration of paid subscription
    std::int32_t subscriptionPeriod{};

    /// @brief Optional. Information about the paid media bought by the user
    std::vector<Ptr<PaidMedia>> paidMedia;

    /// @brief Optional. Bot-specified paid media payload
    std::string paidMediaPayload;

    /// @brief Optional. Gift sent to the user by the bot
    Ptr<Gift> gift;

    /// @brief Optional. Number of months for gifted Telegram Premium subscription
    std::int32_t premiumSubscriptionDuration{};

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      OBJECT_SERIALIZE_FIELD(json, "transaction_type", transactionType);
      OBJECT_SERIALIZE_FIELD_PTR(json, "user", user);
      OBJECT_SERIALIZE_FIELD_PTR(json, "affiliate", affiliate);
      OBJECT_SERIALIZE_FIELD(json, "invoice_payload", invoicePayload);
      OBJECT_SERIALIZE_FIELD(json, "subscription_period", subscriptionPeriod);
      OBJECT_SERIALIZE_FIELD_PTR_ARRAY(json, "paid_media", paidMedia);
      OBJECT_SERIALIZE_FIELD(json, "paid_media_payload", paidMediaPayload);
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      OBJECT_SERIALIZE_FIELD(json, "premium_subscription_duration", premiumSubscriptionDuration);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "transaction_type", transactionType, "", false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "user", user, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "affiliate", affiliate, true);
      OBJECT_DESERIALIZE_FIELD(json, "invoice_payload", invoicePayload, "", true);
      OBJECT_DESERIALIZE_FIELD(json, "subscription_period", subscriptionPeriod, 0, true);
      OBJECT_DESERIALIZE_FIELD_PTR_ARRAY(json, "paid_media", paidMedia, true);
      OBJECT_DESERIALIZE_FIELD(json, "paid_media_payload", paidMediaPayload, "", true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, true);
      OBJECT_DESERIALIZE_FIELD(json, "premium_subscription_duration", premiumSubscriptionDuration, 0, true);
    }
  };

  /// @brief Describes a transaction with a chat.
  struct TransactionPartnerChat : TransactionPartner {
    TransactionPartnerChat() = default;
    explicit TransactionPartnerChat(const nl::json& json) {
      TransactionPartnerChat::fromJson(json);
      // TransactionPartner::type = "chat";
    }

    /// @brief Information about the chat
    Ptr<Chat> chat;

    /// @brief Optional. Gift sent to the chat by the bot
    Ptr<Gift> gift;

    /// @brief Serializes this object to JSON
    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "chat", chat);
      OBJECT_SERIALIZE_FIELD_PTR(json, "gift", gift);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "chat", chat, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "gift", gift, true);
    }
  };

  /// @brief Describes a transaction with an affiliate program.
  struct TransactionPartnerAffiliateProgram : TransactionPartner {
    TransactionPartnerAffiliateProgram() = default;
    explicit TransactionPartnerAffiliateProgram(const nl::json& json) {
      TransactionPartnerAffiliateProgram::fromJson(json);
      //TransactionPartner::type = "affiliate_program";
    }

    /// @brief Optional. Information about the bot sponsoring the affiliate program
    Ptr<User> sponsorUser;

    /// @brief Number of Telegram Stars received per 1000 Stars of referred users
    std::int32_t commissionPerMille{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "sponsor_user", sponsorUser);
      OBJECT_SERIALIZE_FIELD(json, "commission_per_mille", commissionPerMille);
      return json;
    }

    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "sponsor_user", sponsorUser, true);
      OBJECT_DESERIALIZE_FIELD(json, "commission_per_mille", commissionPerMille, 0, false);
    }
  };

  /// @brief Describes a withdrawal transaction with Fragment.
  struct TransactionPartnerFragment : TransactionPartner {
    TransactionPartnerFragment() = default;
    explicit TransactionPartnerFragment(const nl::json& json) {
      TransactionPartnerFragment::fromJson(json);
      // TransactionPartner::type = "fragment";
    }

    /// @brief Optional. State of the withdrawal if transaction is outgoing
    Ptr<RevenueWithdrawalState> withdrawalState;

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      OBJECT_SERIALIZE_FIELD_PTR(json, "withdrawal_state", withdrawalState);
      return json;
    }

    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "withdrawal_state", withdrawalState, true);
    }
  };

  /// @brief Describes a withdrawal transaction to Telegram Ads platform.
  struct TransactionPartnerTelegramAds : TransactionPartner {
    TransactionPartnerTelegramAds() = default;
    explicit TransactionPartnerTelegramAds(const nl::json& json) {
      TransactionPartnerTelegramAds::fromJson(json);
      // TransactionPartner::type = "telegram_ads";
    }

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      return json;
    }

    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
    }
  };

  /// @brief Describes a transaction for paid broadcasting (Telegram API).
  struct TransactionPartnerTelegramApi : TransactionPartner {
    TransactionPartnerTelegramApi() = default;
    explicit TransactionPartnerTelegramApi(const nl::json& json) {
      TransactionPartnerTelegramApi::fromJson(json);
      // TransactionPartner::type = "telegram_api";
    }

    /// @brief Number of successful requests exceeding regular limits that were billed
    std::int32_t requestCount{};

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      OBJECT_SERIALIZE_FIELD(json, "request_count", requestCount);
      return json;
    }

    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
      OBJECT_DESERIALIZE_FIELD(json, "request_count", requestCount, 0, false);
    }
  };

  /// @brief Describes a transaction with an unknown source or recipient.
  struct TransactionPartnerOther : TransactionPartner {
    TransactionPartnerOther() = default;
    explicit TransactionPartnerOther(const nl::json& json) {
      TransactionPartnerOther::fromJson(json);
      // TransactionPartner::type = "other";
    }

    [[nodiscard]] nl::json toJson() const override {
      nl::json json = TransactionPartner::toJson();
      return json;
    }

    void fromJson(const nl::json& json) override {
      TransactionPartner::fromJson(json);
    }
  };

}
