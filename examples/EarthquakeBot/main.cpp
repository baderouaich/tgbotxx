#include <tgbotxx/tgbotxx.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <algorithm>
#include <csignal>
#include <set>
using namespace tgbotxx;

class EarthQuakeBot final : public Bot {
public:
  EarthQuakeBot(const std::string &token) : Bot(token) {}

private:
  const std::string EQ_API_ENDPOINT = "https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_hour.geojson";
  std::unique_ptr<std::thread> m_earthquakesMonitor;
  std::atomic<bool> m_earthquakesMonitorRunning;
  std::set<std::int64_t> m_chatIds; /// Chats to be alerted, user will be registered after /subscribe command
  std::vector<std::string> m_alreadyAlertedEqEvents;

private:
  void onStart() override {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Register my commands (/subscribe & /unsubscribe)
    Ptr<BotCommand> subscribeCmd(new BotCommand());
    subscribeCmd->command = "/subscribe";
    subscribeCmd->description = "Subscribe to recent earthquakes alerts";
    Ptr<BotCommand> unsubscribeCmd(new BotCommand());
    unsubscribeCmd->command = "/unsubscribe";
    unsubscribeCmd->description = "Unsubscribe from recent earthquakes alerts";
    api()->setMyCommands({subscribeCmd, unsubscribeCmd});

    // Load any registered user chat ids from a file (if available from previous run)
    if(std::ifstream ifs{"subscribed_chats.txt"}) {
      std::string id;
      while(std::getline(ifs, id))
        m_chatIds.insert(std::stoll(id));
      ifs.close();
    }

    // Start a thread that will retrieve earthquake news every 10 seconds
    m_earthquakesMonitor.reset(new std::thread([this] {
        m_earthquakesMonitorRunning = true;
        while(m_earthquakesMonitorRunning) 
        {
          cpr::Response res = cpr::Get(cpr::Url{EQ_API_ENDPOINT});
          if(res.status_code == cpr::status::HTTP_OK)
          {
            nl::json eqEvents = nl::json::parse(res.text);
            for(const nl::json& eqEvent : eqEvents["features"]) 
            {
              std::time_t eqTime = eqEvent["properties"]["time"].get<std::int64_t>() / 1000;
              std::time_t now = std::time(nullptr);
              std::time_t previousHour = now - 3600;

              // Only alert recent earthquakes (last hour)
              if (eqTime >= previousHour && eqTime <= now) 
              {
                  this->alertSubscribers(eqEvent);
              }
            }
          }            
          // Wait 10s before next check ...
          std::this_thread::sleep_for(std::chrono::seconds(10));
        } 
    }));

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void alertSubscribers(const nl::json &eqEvent) {
    /// Check if we have already sent alerts regarding this earthquake event (so we don't send it again)
    bool alreadyAlerted = std::any_of(m_alreadyAlertedEqEvents.begin(), m_alreadyAlertedEqEvents.end(), [&](const std::string &id)
                                      { return id == eqEvent["id"]; });
    if (alreadyAlerted)
      return;

    /// Alert all subscribed users about this new earthquake events
    float latitude = eqEvent["geometry"]["coordinates"][1].get<float>();
    float longitude = eqEvent["geometry"]["coordinates"][0].get<float>();
    std::ostringstream oss{};
    oss << "New earthquake!\n"
        << "* Title: " << eqEvent["properties"]["title"].get<std::string>() << '\n'
        << "* Date: " << DateTimeUtils::toString(eqEvent["properties"]["time"].get<std::time_t>() / 1000) << '\n'
        << "* Magnitude: " << eqEvent["properties"]["mag"].get<float>() << '\n'
        << "* Tsunami: " << eqEvent["properties"]["tsunami"].get<int>() << '\n'
        << "* Location: " << eqEvent["properties"]["place"].get<std::string>() << '\n'
        << "* Coordinates: (latitude: " << latitude << ", latitude: " << longitude << ")\n";
        ;
    for (const std::int64_t &chatId : m_chatIds)
    {
      api()->sendMessage(chatId, oss.str());
      api()->sendLocation(chatId, latitude, longitude);
    }

    /// Mark as alerted.
    m_alreadyAlertedEqEvents.push_back(eqEvent["id"]);
  }

  void onStop() override
  {
    m_earthquakesMonitorRunning = false;
    if (m_earthquakesMonitor && m_earthquakesMonitor->joinable())
    {
      m_earthquakesMonitor->join();
      m_earthquakesMonitor.reset(nullptr);
    }

    // Save registered user chat ids to a file
    if(std::ofstream ofs{"subscribed_chats.txt"}){
      for(const std::int64_t& chatId : m_chatIds)
        ofs << chatId << '\n';
      ofs.close();
    }
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if (message->text == "/subscribe")
    {
      m_chatIds.insert(message->chat->id);
      api()->sendMessage(message->chat->id, "You are successfully subscribed! You will receive a message when there is an earthquake somewhere in the world.");
    }
    else if (message->text == "/unsubscribe")
    {
      if (m_chatIds.contains(message->chat->id))
      {
        m_chatIds.erase(message->chat->id);
        api()->sendMessage(message->chat->id, "You are successfully unsubscribed. You will not receive any alerts.");
      }
      else
      {
        api()->sendMessage(message->chat->id, "You are already not subscribed to alerts.");
      }
    }
  }
};



int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nearthquake_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<EarthQuakeBot> BOT = std::make_unique<EarthQuakeBot>(argv[1]);
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if(BOT) {
      std::cout << "Stopping Bot. Please wait..." << std::endl;
      BOT->stop();
    }
  });
  BOT->start();
  std::cout << "Bot Stopped." << std::endl;
  return EXIT_SUCCESS;
}
