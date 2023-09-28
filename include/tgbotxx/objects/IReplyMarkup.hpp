#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief The interface of reply markup objects InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove and ForceReply.
    /// @ref https://core.telegram.org/bots/api#sendmessage reply_markup param.
    struct IReplyMarkup {
        virtual nl::json toJson() const = 0;
        virtual void fromJson(const nl::json&) = 0;
    };
}