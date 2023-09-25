#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Api.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
  : m_api(new Api(token)), m_running(false), m_lastUpdateId(0) {
}

void Bot::start() {
  if(m_running) return;
  m_running = true;

  /// Callback -> onStart
  this->onStart();

  while(m_running)
  {
    // Dispatch updates
    for (const Ptr<Update>& update : m_updates) {
      if (update->updateId >= m_lastUpdateId)
        m_lastUpdateId = update->updateId + 1;
      this->dispatch(update);
    }

    if(m_running) {
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
  if(not m_running) return;
  m_running = false;

  /// Callback -> onStop
  this->onStop();
}


void Bot::dispatch(const Ptr<Update> &update) {
  if(update->message) {
    const Ptr<Message>& message = update->message;

    /// Callback -> onAnyMessage
    this->onAnyMessage(message);

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
        splitPosition = std::min(spacePosition, atSymbolPosition);
      }
      std::string command = message->text.substr(1, splitPosition - 1);
      std::vector<Ptr<BotCommand>> myCommands = m_api->getMyCommands();
      bool isKnownCommand = std::any_of(myCommands.begin(), myCommands.end(), [&command](const Ptr<BotCommand>& cmd) noexcept {
         return cmd->command == command;
      });
      if (isKnownCommand) {
        /// Callback -> onCommand
        this->onCommand(message);
      }
      else {
        /// Callback -> onUnknownCommand
        this->onUnknownCommand(message);
      }
    } else {
      /// Callback -> onNonCommandMessage
      this->onNonCommandMessage(message);
    }
  }
}

const Ptr<Api>& Bot::getApi() const noexcept {
  return m_api;
}
