#include <tgbotxx/Bot.hpp>
#include <tgbotxx/objects/Command.hpp>
#include <tgbotxx/objects/Message.hpp>
#include <tgbotxx/objects/Update.hpp>
#include <tgbotxx/objects/User.hpp>
using namespace tgbotxx;

Bot::Bot(const std::string& token)
  : m_token(token), m_api(new Api(token)), /*m_thread(nullptr),*/ m_running(false) {
}

void Bot::start() {
  if(m_running.load(std::memory_order::relaxed)) return;

  m_running.store(true, std::memory_order::relaxed);
  while(m_running)
  {
    std::cout << "Getting updates...\n";
    std::vector<Ptr<Update>> updates = m_api->getUpdates();
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

const Ptr<Api>& Bot::getApi() const noexcept {
  return m_api;
}

void Bot::restart() {
  stop();
  start();
}
