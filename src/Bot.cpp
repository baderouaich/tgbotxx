#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
    : m_api(new Api(token)), m_running(false), m_lastUpdateId(0) {
}

Bot::~Bot() {
  stop();
}

void Bot::start() {
  if (m_running) return;
  m_running = true;

  /// Callback -> onStart
  this->onStart();

  while (m_running) {
    // Dispatch updates
    for (const Ptr<Update>& update: m_updates) {
      if (update->updateId >= m_lastUpdateId)
        m_lastUpdateId = update->updateId + 1;
      this->dispatch(update);
    }

    if (m_running) {
      // Confirm dispatched updates
      m_updates = m_api->getUpdates(/*offset=*/m_lastUpdateId);
    } else {
      // Confirm last updates before stopping, timeout = 0
      // Requesting new updates from Telegram server lets the server know that you handled the previous updates,
      // so it will not send us duplicate updates.
      m_updates = m_api->getUpdates(/*offset=*/m_lastUpdateId, /*limit=*/100, /*timeout=*/0);
    }
  }
}

void Bot::stop() {
  if (not m_running) return;
  m_running = false;

  /// Callback -> onStop
  this->onStop();
}


void Bot::dispatch(const Ptr<Update>& update) {
  /// A Message can be a Command, EditedMessage, Normal Message, Channel Post...
  if (update->message) {
    /// ... this function will dispatch accordingly
    this->dispatchMessage(update->message);
  }

  if (update->editedMessage) {
    /// Callback -> onEditedMessage
    this->onEditedMessage(update->editedMessage);
  }

  if (update->channelPost) {
    this->dispatchMessage(update->channelPost);
  }

  if (update->editedChannelPost) {
    /// Callback -> onEditedMessage
    this->onEditedMessage(update->editedChannelPost);
  }

  if (update->inlineQuery) {
    /// Callback -> onInlineQuery
    this->onInlineQuery(update->inlineQuery);
  }
  if (update->chosenInlineResult) {
    /// Callback -> onChosenInlineResult
    this->onChosenInlineResult(update->chosenInlineResult);
  }
  if (update->callbackQuery) {
    /// Callback -> onCallbackQuery
    this->onCallbackQuery(update->callbackQuery);
  }
  if (update->shippingQuery) {
    /// Callback -> onShippingQuery
    this->onShippingQuery(update->shippingQuery);
  }
  if (update->preCheckoutQuery) {
    /// Callback -> onPreCheckoutQuery
    this->onPreCheckoutQuery(update->preCheckoutQuery);
  }
  if (update->poll) {
    /// Callback -> onPoll
    this->onPoll(update->poll);
  }
  if (update->pollAnswer) {
    /// Callback -> onPollAnswer
    this->onPollAnswer(update->pollAnswer);
  }
  if (update->myChatMember) {
    /// Callback -> onMyChatMember
    this->onMyChatMember(update->myChatMember);
  }
  if (update->chatMember) {
    /// Callback -> onChatMember
    this->onChatMember(update->chatMember);
  }
  if (update->chatJoinRequest) {
    /// Callback -> onChatJoinRequest
    this->onChatJoinRequest(update->chatJoinRequest);
  }
}

const Ptr<Api>& Bot::getApi() const noexcept {
  return m_api;
}

void Bot::dispatchMessage(const Ptr<Message>& message) {
  /// Callback -> onAnyMessage
  this->onAnyMessage(message);

  /// Command ?
  if (StringUtils::startsWith(message->text, "/")) {
    std::size_t splitPosition;
    std::size_t spacePosition = message->text.find(' ');
    std::size_t atSymbolPosition = message->text.find('@');
    if (spacePosition == std::string::npos) {
      if (atSymbolPosition == std::string::npos) {
        splitPosition = message->text.size();
      } else {
        splitPosition = atSymbolPosition;
      }
    } else if (atSymbolPosition == std::string::npos) {
      splitPosition = spacePosition;
    } else {
      splitPosition = (std::min)(spacePosition, atSymbolPosition);
    }
    std::string command = message->text.substr(1, splitPosition - 1);
    std::vector<Ptr<BotCommand>> myCommands = m_api->getMyCommands();
    bool isKnownCommand = std::any_of(myCommands.begin(), myCommands.end(), [&command](const Ptr<BotCommand>& cmd) noexcept {
      return cmd->command == command;
    });
    if (isKnownCommand) {
      /// Callback -> onCommand
      this->onCommand(message);
    } else {
      /// Callback -> onUnknownCommand
      this->onUnknownCommand(message);
    }
  } else {
    /// Callback -> onNonCommandMessage
    this->onNonCommandMessage(message);
  }
}
