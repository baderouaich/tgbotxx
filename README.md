> **Warning**
>
> this library is still under development.

# tgbotxx
Telegram Bot C++ Library



### Requirements
- [cpr](https://github.com/libcpr/cpr)
- [json](https://github.com/nlohmann/json)

### Target Usage
```cpp
#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {
public:
    MyBot() : Bot("BOT_API_KEY_FROM_BOT_FATHER") {
      std::vector<Ptr<Command>> commands;
      Ptr<Command> greet(new Command());
      greet->command = "/greet";
      greet->description = "This command will greet you";
      commands.push_back(greet);
      Bot::setCommands(commands); // The above commands will be shown in the bot chat menu (bottom left)
    }

public:
    void onAnyMessage(const Ptr<Message>& message) override {
      if(message->text.starts_with("/")) { // >= C++20 (u can also use StringUtils::startsWith())
          std::cout << "Ignoring command: " << message->text << '\n';
          return;
      }
    }

    void onCommand(const Ptr<Command>& command) override {
      if(command->text == "start") {
        getApi()->sendMessage(command->chat->id, "Welcome " + command->from->firstName + "!");
      }
      else if(command->text == "greet") {
        getApi()->sendMessage(command->chat->id, "Good day!");
      }
    }
    
    ...
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}
```