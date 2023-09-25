#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {
  static std::string getTestsBotToken() {
    if(char* token = std::getenv("TESTS_BOT_TOKEN"); token != nullptr)
      return std::string(token);
     throw std::runtime_error("Couldn't find TESTS_BOT_TOKEN in the env; please export an environment variable TESTS_BOT_TOKEN with your bot token");
  }

public:
    MyBot() : Bot(getTestsBotToken()) {}

private:
    void onStart() override {
      std::cout << __func__ << std::endl;

      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      getApi()->deleteWebhook(true);

      // Register bot commands ...
      std::vector<Ptr<BotCommand>> commands;
      Ptr<BotCommand> greet(new BotCommand());
      greet->command = "greet";
      greet->description = "This command will greet you";
      commands.push_back(greet);
      Ptr<BotCommand> stop(new BotCommand());
      stop->command = "stop";
      stop->description = "Stop the bot";
      commands.push_back(stop);
      getApi()->setMyCommands(commands); // The above commands will be shown in the bot chat menu (bottom left)
    }

    void onStop() override {
      std::cout << __func__ << std::endl;
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }

    void onCommand(const Ptr<Message>& command) override {
      std::cout << __func__ << ": " << command->text << std::endl;
      if(command->text == "/stop") {
        Bot::stop();
        return;
      }

#if api_sendMessage_implemented
    if(command->text == "start") {
        getApi()->sendMessage(command->chat->id, "Welcome " + command->from->firstName + "!");
      }
      else if(command->text == "greet") {
        getApi()->sendMessage(command->chat->id, "Good day!");
      }
#endif
    }

    void onNonCommandMessage(const Ptr<Message> &message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }

    void onUnknownCommand(const Ptr<Message> &message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}