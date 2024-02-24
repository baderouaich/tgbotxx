#include <tgbotxx/Api.hpp>
#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Exception.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
    : m_api(new Api(token)), m_lastUpdateId(0), m_running(false) {
}

Bot::~Bot() {
  stop();
}

void Bot::start() {
  if (m_running) return;
  m_running = true;

  /// Callback -> onStart
  this->onStart();

  /// Start the Long Polling loop...
  while (m_running) {
    try {
      // Get updates from Telegram (any new events such as messages, commands, files, ...)
      m_updates = m_api->getUpdates(/*offset=*/m_lastUpdateId);
    } catch (const std::exception& err) {
      /// Callback -> onLongPollError
      std::string errStr = err.what();
      StringUtils::replace(errStr, m_api->m_token, "***HIDDEN_BOT_TOKEN***"); // Hide bot token in the exception message for security reasons
      this->onLongPollError(errStr);
      continue;
    } catch (...) {
      /// Callback -> onLongPollError
      this->onLongPollError("unknown error");
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

const Ptr<Api>& Bot::getApi() const noexcept { return m_api; }
const Ptr<Api>& Bot::api() const noexcept { return m_api; }

void Bot::dispatchMessage(const Ptr<Message>& message) {
  /// Callback -> onAnyMessage
  this->onAnyMessage(message);

  /// Is this message a Command ? (starts with '/' character)
  if (not message->text.empty() and message->text[0] == '/') {
    std::size_t firstSpacePos = message->text.find_first_of(" \t\n\r");
    if (firstSpacePos == std::string::npos)
      firstSpacePos = message->text.size();
    std::string command = message->text.substr(1, firstSpacePos - 1);
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
