#pragma once
#include <tgbotxx/objects/Object.hpp>

namespace tgbotxx {
    /// @brief The interface of reply markup objects InlineKeyboardMarkup, ReplyKeyboardMarkup, ReplyKeyboardRemove and ForceReply.
    /// @ref https://core.telegram.org/bots/api#sendmessage reply_markup param.
    struct IReplyMarkup {
        IReplyMarkup() = default;
        virtual ~IReplyMarkup() = default;
    };
}