#pragma once
#include <tgbotxx/objects/Object.hpp>
#include <tgbotxx/objects/InaccessibleMessage.hpp>
#include <variant>

namespace tgbotxx {
  struct Message;
  /// @brief This object describes a message that can be inaccessible to the bot. It can be one of
  /// - Message
  /// - InaccessibleMessage
  /// @tip: To find which type is held, use std::holds_alternative<T>(variant) with std::get<T>(variant),
  /// or test variant.index() against 0 - 1 where 0 = Ptr<Message> and 1 = Ptr<InaccessibleMessage>
  /// @ref https://core.telegram.org/bots/api#maybeinaccessiblemessage
  using MaybeInaccessibleMessage = std::variant<Ptr<Message>, Ptr<InaccessibleMessage>>;
}