#include <tgbotxx/Bot.hpp>
#include <tgbotxx/Api.hpp>
#include <tgbotxx/objects/BotCommand.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/User.hpp>
#include <tgbotxx/utils/StringUtils.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
  : m_token(token), m_api(new Api(token)), /*m_thread(nullptr),*/ m_running(false), m_lastUpdateId(0) {
}

void Bot::start() {
  if(m_running.load(std::memory_order::relaxed)) return;

  m_running.store(true, std::memory_order::relaxed);
  while(m_running)
  {
    std::cout << "Getting updates (long poll)...\n";
    std::vector<Ptr<Update>> updates = m_api->getUpdates(/*offset=*/m_lastUpdateId);
    std::cout << "Got " << updates.size() << " updates\n";
    for (const Ptr<Update>& update : updates) {
      if (update->updateId >= m_lastUpdateId) {
        m_lastUpdateId = update->updateId + 1;
      }
      this->dispatch(update);
    }

  }
//  m_thread.reset(new std::thread([this]{
//      while(m_running) {
//          std::vector<Ptr<Update>> updates = m_api->getUpdates();
//      }
//  }));
}

void Bot::stop() {
  if(not m_running.load(std::memory_order::relaxed)) return;

  m_running.store(false, std::memory_order::relaxed);
//  if(m_thread && m_thread->joinable()) {
//    m_thread->join();
//    m_thread.reset();
//  }
}


void Bot::restart() {
  stop();
  start();
}

void Bot::dispatch(const Ptr<Update> &update) {
  std::cout << "Dispatching update " << update->updateId << "..."<<std::endl;

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
      bool isKnownCommand = std::any_of(myCommands.begin(), myCommands.end(), [&command](const Ptr<BotCommand>& cmd) {
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
