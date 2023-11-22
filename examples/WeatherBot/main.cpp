#include <cpp-httplib/httplib.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <expected>
#include <tgbotxx/tgbotxx.hpp>
#include <nlohmann/json.hpp>
#include <csignal>

using namespace tgbotxx;

class WeatherBot : public Bot {
public:
    WeatherBot(const std::string &token, const std::string &weatherApiKey)
            : Bot(token), m_weatherApiKey(weatherApiKey) {}

private:
    std::string m_weatherApiKey;
    inline static const std::string WEATHER_API_ENDPOINT = "http://api.weatherapi.com/v1";
    inline static const std::map<std::string, std::string> WEATHER_STATUS_EMOTICONS = {
            {"sun",      "🌞"},
            {"rain",     "🌧"},
            {"cloud",    "☁"},
            {"clear",    "🌅"},
            {"overcast", "🌫️"},
            {"mist",     "🌁"}
    };

protected:
    nl::json getCurrentWeatherInfo(const std::string &cityName) {
      std::ostringstream oss{};
      oss << "/current.json?key=" << m_weatherApiKey << "&q=" << cityName;
      httplib::Client cli(WEATHER_API_ENDPOINT);
      auto res = cli.Get(oss.str());
      switch (res->status) {
        case 200:
          return nl::json::parse(res->body);
        default: {
          nl::json err;
          err["error"]["message"] = "Failed to get weather info";
          return err;
        }
      }
    }

private:
    void onStart() override {
      // Drop pending updates
      api()->deleteWebhook(true);

      // Register my commands
      Ptr<BotCommand> startCmd(new BotCommand());
      startCmd->command = "/start";
      startCmd->description = "Start interacting with the bot";
      api()->setMyCommands({startCmd});

      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onStop() override {
      std::cout << "\nStopping Bot. Please wait...\n";
    }

    void onNonCommandMessage(const Ptr<Message> &message) override try {
      std::string cityName = message->text;
      nl::json info = getCurrentWeatherInfo(cityName);
      if (info.contains("error")) {
        api()->sendMessage(message->chat->id, info["error"]["message"]);
      } else {
        std::string name = info["location"]["name"];
        std::string region = info["location"]["region"];
        std::string country = info["location"]["country"];
        std::string localtime = info["location"]["localtime"];
        std::string condition = info["current"]["condition"]["text"];
        int humidity = info["current"]["humidity"];
        float wind_kph = info["current"]["wind_kph"];
        std::time_t lastUpdatedTime = info["current"]["last_updated_epoch"];
        int temp_c = info["current"]["temp_c"];
        float temp_f = info["current"]["temp_f"];
        std::string emoticon = "🌍";
        for (const auto &[key, value]: WEATHER_STATUS_EMOTICONS) {
          if (StringUtils::toLower(condition).find(key) != std::string::npos) {
            emoticon = value;
            break;
          }
        }
        std::ostringstream oss{};
        oss << "------ 🌡️ " << temp_c << " °C (" << temp_f << " °F) " << condition << " " << emoticon << " ------\n"
            << "* Humidity: " << humidity << '\n'
            << "* Wind (kph): " << wind_kph << '\n'
            << "* Name: " << name << '\n'
            << "* Country: " << country << '\n'
            << "* Region: " << region << '\n'
            << "* Local Time: " << localtime << '\n'
            << "* Updated On: " << DateTimeUtils::toString(lastUpdatedTime) << '\n'
            << "------------------------------------------------------\n";
        api()->sendMessage(message->chat->id, oss.str());
      }

    } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
    }

    void onCommand(const Ptr<Message> &message) override {
      if (message->text == "/start") {
        api()->sendMessage(message->chat->id, "Welcome to WeatherBot! Please send a city name to get weather information.");
      }
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\nweather_bot \"BOT_TOKEN\" \"WEATHER_API_KEY\"\n";
    return EXIT_FAILURE;
  }
  static std::unique_ptr<WeatherBot> BOT;
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
      if (BOT) {
        BOT->stop();
      }
      std::exit(EXIT_SUCCESS);
  });

  BOT = std::make_unique<WeatherBot>(argv[1], argv[2]);
  BOT->start();
  return EXIT_SUCCESS;
}
