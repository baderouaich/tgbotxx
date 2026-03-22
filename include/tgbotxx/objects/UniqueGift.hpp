#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/UniqueGiftModel.hpp>
#include <tgbotxx/objects/UniqueGiftSymbol.hpp>
#include <tgbotxx/objects/UniqueGiftBackdrop.hpp>
#include <tgbotxx/objects/UniqueGiftColors.hpp>
#include <tgbotxx/objects/Chat.hpp>

namespace tgbotxx {
  /// @brief This object describes a unique gift that was upgraded from a regular gift.
  /// @ref https://core.telegram.org/bots/api#uniquegift
  struct UniqueGift {
    UniqueGift() = default;
    explicit UniqueGift(const nl::json& json) {
      fromJson(json);
    }

    /// @brief Identifier of the regular gift from which the gift was upgraded
    std::string giftId;

    /// @brief Human-readable name of the regular gift from which this unique gift was upgraded
    std::string baseName;

    /// @brief Unique name of the gift. This name can be used in https://t.me/nft/... links and story areas
    std::string name;

    /// @brief Unique number of the upgraded gift among gifts upgraded from the same regular gift
    std::int32_t number{};

    /// @brief Model of the gift
    Ptr<UniqueGiftModel> model;

    /// @brief Symbol of the gift
    Ptr<UniqueGiftSymbol> symbol;

    /// @brief Backdrop of the gift
    Ptr<UniqueGiftBackdrop> backdrop;

    /// @brief Optional. True, if the original regular gift was exclusively purchaseable by Telegram Premium subscribers
    bool isPremium{};

    /// @brief Optional. True, if the gift was used to craft another gift and isn't available anymore
    bool isBurned{};

    /// @brief Optional. True, if the gift is assigned from the TON blockchain and can't be resold or transferred in Telegram
    bool isFromBlockchain{};

    /// @brief Optional. The color scheme that can be used by the gift's owner for the chat's name, replies to messages and link previews;
    /// for business account gifts and gifts that are currently on sale only
    Ptr<UniqueGiftColors> colors;

    /// @brief Optional. Information about the chat that published the gift
    Ptr<Chat> publisherChat;

    /// @brief Serializes this object to JSON
    /// @returns JSON representation of this object
    [[nodiscard]] nl::json toJson() const {
      nl::json json = nl::json::object();
      OBJECT_SERIALIZE_FIELD(json, "gift_id", giftId);
      OBJECT_SERIALIZE_FIELD(json, "base_name", baseName);
      OBJECT_SERIALIZE_FIELD(json, "name", name);
      OBJECT_SERIALIZE_FIELD(json, "number", number);
      OBJECT_SERIALIZE_FIELD_PTR(json, "model", model);
      OBJECT_SERIALIZE_FIELD_PTR(json, "symbol", symbol);
      OBJECT_SERIALIZE_FIELD_PTR(json, "backdrop", backdrop);
      OBJECT_SERIALIZE_FIELD(json, "is_premium", isPremium);
      OBJECT_SERIALIZE_FIELD(json, "is_burned", isBurned);
      OBJECT_SERIALIZE_FIELD(json, "is_from_blockchain", isFromBlockchain);
      OBJECT_SERIALIZE_FIELD_PTR(json, "colors", colors);
      OBJECT_SERIALIZE_FIELD_PTR(json, "publisher_chat", publisherChat);
      return json;
    }

    /// @brief Deserializes this object from JSON
    void fromJson(const nl::json& json) {
      OBJECT_DESERIALIZE_FIELD(json, "gift_id", giftId, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "base_name", baseName, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "name", name, "", false);
      OBJECT_DESERIALIZE_FIELD(json, "number", number, 0, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "model", model, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "symbol", symbol, false);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "backdrop", backdrop, false);
      OBJECT_DESERIALIZE_FIELD(json, "is_premium", isPremium, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_burned", isBurned, false, true);
      OBJECT_DESERIALIZE_FIELD(json, "is_from_blockchain", isFromBlockchain, false, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "colors", colors, true);
      OBJECT_DESERIALIZE_FIELD_PTR(json, "publisher_chat", publisherChat, true);
    }
  };
}