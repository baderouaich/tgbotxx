#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
#include <tgbotxx/objects/BusinessMessagesDeleted.hpp>
#include <tgbotxx/objects/PaidMediaPurchased.hpp>
#include <tgbotxx/objects/BusinessConnection.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
  : m_api{new Api(token)}, m_updates{}, m_lastUpdateId{0}, m_stopped{std::make_shared<std::atomic<bool>>(true)} {
}

Bot::~Bot() {
  stop();
}

void Bot::start() {
  if (not *m_stopped) return;
  *m_stopped = false;

  /// Callback -> onStart
  this->onStart();

  /// Start the Long Polling loop...
  while (not *m_stopped) {
    try {
      // Get updates from Telegram (any new events such as messages, commands, files, ...)
      m_updates = m_api->getUpdates(/*offset=*/m_lastUpdateId, m_stopped);
    } catch (const Exception& err) {
      /// Callback -> onLongPollError
      std::string errStr{err.what()};
      StringUtils::replace(errStr, m_api->m_token, "***REDACTED***"); // Hide bot token in the exception message for security reasons
      this->onLongPollError(errStr, err.errorCode());
      continue;
    } catch (const std::exception& err) {
      /// Callback -> onLongPollError
      std::string errStr{err.what()};
      StringUtils::replace(errStr, m_api->m_token, "***REDACTED***"); // Hide bot token in the exception message for security reasons
      this->onLongPollError(errStr, ErrorCode::OTHER);
      continue;
    } catch (...) {
      /// Callback -> onLongPollError
      this->onLongPollError("Unknown error", ErrorCode::OTHER);
      continue;
    }
    // Dispatch updates to callbacks (onCommand, onAnyMessage, onPoll, ...)
    for (const Ptr<Update>& update: m_updates) {
      if (update->updateId >= m_lastUpdateId) {
        m_lastUpdateId = update->updateId + 1;
        this->dispatch(update);
      }
    }
  }
}

void Bot::stop() {
  if (*m_stopped) return;
  *m_stopped = true;

  /// Callback -> onStop
  this->onStop();
}

const Ptr<Api>& Bot::getApi() const noexcept { return m_api; }
const Ptr<Api>& Bot::api() const noexcept { return m_api; }
bool Bot::isRunning() const noexcept { return not *m_stopped; }

void Bot::dispatch(const Ptr<Update>& update) {
  this->dispatchMessages(update);
  this->dispatchChannel(update);
  this->dispatchBusiness(update);
  this->dispatchMessageReaction(update);
  this->dispatchInlineMode(update);
  this->dispatchPayments(update);
  this->dispatchPoll(update);
  this->dispatchChat(update);
}

void Bot::dispatchMessages(const Ptr<Update>& update) {
  /// A Message can be a Command, EditedMessage, Normal Message, Channel Post...
  if (update->message) {
    const Ptr<Message>& message = update->message;
    /// ... dispatch the message accordingly
    /// Callback -> onAnyMessage
    this->onAnyMessage(message);

    const std::string_view text = message->text;
    if (not text.empty()) {
      if (text[0] != '/') {
        /// Callback -> onNonCommandMessage
        this->onNonCommandMessage(message);
      } else {
        // Cache bot commands & username locally (to avoid calling api()->getMyCommands() everytime we receive a command)
        if (m_api->m_cache.botCommands.empty()) [[unlikely]] {
          m_api->m_cache.refresh(m_api.get());
        }

        // 1 BotCommand entity must be in the message starting with /
        // assert(std::ranges::count_if(message->entities, [](const Ptr<MessageEntity>& entity) noexcept {return entity->type == MessageEntity::Type::BotCommand;}) == 1);
        const bool isKnownCommand = std::ranges::any_of(m_api->m_cache.botCommands, [&text, atMyUsername = '@' + m_api->m_cache.botUsername](const std::string& cmd) noexcept {
          // Handle both /start (in private chats)  /start@botusername (in groups)
          // text == cmd: example: /start
          // text.ends_with(atMyUsername): example: /start@mybotusername
          // In group chats, this bot must be mentioned with the command to avoid
          // conflicts with other bots having the same command
          return text == cmd || text.ends_with(atMyUsername);
        });
        if (isKnownCommand) {
          /// Callback -> onCommand
          this->onCommand(message);
        } else {
          /// Callback -> onUnknownCommand
          this->onUnknownCommand(message);
        }
      }
    }
  }

  if (update->editedMessage) {
    /// Callback -> onMessageEdited
    this->onMessageEdited(update->editedMessage);
  }
}
void Bot::dispatchChannel(const Ptr<Update>& update) {
  if (update->channelPost) {
    this->onChannelPost(update->channelPost);
  }
  if (update->editedChannelPost) {
    this->onChannelPostEdited(update->editedChannelPost);
  }
}
void Bot::dispatchBusiness(const Ptr<Update>& update) {
  if (update->businessConnection) {
    this->onBusinessConnection(update->businessConnection);
  }
  if (update->businessMessage) {
    this->onBusinessMessage(update->businessMessage);
  }
  if (update->editedBusinessMessage) {
    this->onBusinessMessageEdited(update->editedBusinessMessage);
  }
  if (update->deletedBusinessMessages) {
    this->onBusinessMessagesDeleted(update->deletedBusinessMessages);
  }
}
void Bot::dispatchMessageReaction(const Ptr<Update>& update) {
  if (update->messageReaction) {
    this->onMessageReactionUpdated(update->messageReaction);
  }
  if (update->messageReactionCount) {
    this->onMessageReactionCountUpdated(update->messageReactionCount);
  }
}
void Bot::dispatchInlineMode(const Ptr<Update>& update) {
  if (update->inlineQuery) {
    this->onInlineQuery(update->inlineQuery);
  }
  if (update->chosenInlineResult) {
    this->onChosenInlineResult(update->chosenInlineResult);
  }
  if (update->callbackQuery) {
    this->onCallbackQuery(update->callbackQuery);
  }
  if (update->shippingQuery) {
    this->onShippingQuery(update->shippingQuery);
  }
  if (update->preCheckoutQuery) {
    this->onPreCheckoutQuery(update->preCheckoutQuery);
  }
}
void Bot::dispatchPayments(const Ptr<Update>& update) {
  if (update->purchasedPaidMedia) {
    this->onPaidMediaPurchased(update->purchasedPaidMedia);
  }
}
void Bot::dispatchPoll(const Ptr<Update>& update) {
  if (update->poll) {
    this->onPoll(update->poll);
  }
  if (update->pollAnswer) {
    this->onPollAnswer(update->pollAnswer);
  }
}
void Bot::dispatchChat(const Ptr<Update>& update) {
  if (update->myChatMember) {
    this->onMyChatMemberUpdated(update->myChatMember);
  }
  if (update->chatMember) {
    this->onChatMemberUpdated(update->chatMember);
  }
  if (update->chatJoinRequest) {
    this->onChatJoinRequest(update->chatJoinRequest);
  }
  if (update->chatBoost) {
    this->onChatBoostUpdated(update->chatBoost);
  }
  if (update->removedChatBoost) {
    this->onChatBoostRemoved(update->removedChatBoost);
  }
}
