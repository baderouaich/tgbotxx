#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {

  std::string getTestsBotToken() {
    if(char* token = std::getenv("TESTS_BOT_TOKEN"); token != nullptr)
      return std::string(token);
     throw std::runtime_error("Couldn't find TESTS_BOT_TOKEN in the env; please export an environment variable TESTS_BOT_TOKEN with your bot token");
  }

public:
    MyBot() : Bot(getTestsBotToken()) {
      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      getApi()->deleteWebhook(true);

      // Register bot commands ...
      std::vector<Ptr<BotCommand>> commands;
      Ptr<BotCommand> greet(new BotCommand());
      greet->command = "/greet";
      greet->description = "This command will greet you";
      commands.push_back(greet);
      getApi()->setMyCommands(commands); // The above commands will be shown in the bot chat menu (bottom left)
    }

public:
    void onAnyMessage(const Ptr<Message>& message) override {
      std::cout << __func__ << std::endl;
      if(message->text.starts_with("/")) { // >= C++20 (u can also use StringUtils::startsWith())
        std::cout << "Ignoring command: " << message->text << '\n';
        return;
      }
    }

    void onCommand(const Ptr<Message>& command) override {
      std::cout << __func__ << std::endl;
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
      std::cout << __func__ << std::endl;
    }


    void onUnknownCommand(const Ptr<Message> &message) override {
      std::cout << __func__ << std::endl;
    }

};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}