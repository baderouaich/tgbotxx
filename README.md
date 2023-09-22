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
    MyBot() : Bot("BOT_TOKEN_FROM_BOT_FATHER") {
      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours 
      // in Telegram server before they get deleted or retrieved by BOT)
      getApi()->deleteWebhook(false);
      
      // Register commands ...
      std::vector<Ptr<BotCommand>> commands;
      Ptr<Command> greet(new BotCommand());
      greet->command = "/greet";
      greet->description = "This command will greet you";
      commands.push_back(greet);
      getApi()->setMyCommands(commands); // The above commands will be shown in the bot chat menu (bottom left)
    }

public:
    void onAnyMessage(const Ptr<Message>& message) override {
      if(message->text.starts_with("/")) { // >= C++20 (u can also use StringUtils::startsWith())
          std::cout << "Ignoring command: " << message->text << '\n';
          return;
      }
    }

    void onCommand(const Ptr<Message>& message) override {
      if(message->text == "start") {
        getApi()->sendMessage(message->chat->id, "Welcome " + message->from->firstName + "!");
      }
      else if(message->text == "greet") {
        getApi()->sendMessage(message->chat->id, "Good day!");
      } // or create a new method greet() ... do it your way 
    }
    
    void onNonCommandMessage(const Ptr<Message> &message) override {
      std::cout << "onNonCommandMessage: " << message->text << std::endl;
    }
    
    void onUnknownCommand(const Ptr<Message> &message) override {
        std::cout << "onUnknownCommand: " << message->text << std::endl;
    }
    
    ...
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}
```


#### Concepts
<details>
  <summary><small>Long polling</small></summary>
(Long polling)[https://en.wikipedia.org/wiki/Push_technology#Long_polling] is itself not a true push; long polling is a variation of the traditional polling technique, but it allows emulating a push mechanism under circumstances where a real push is not possible, such as sites with security policies that require rejection of incoming HTTP requests.

With long polling, the client requests information from the server exactly as in normal polling, but with the expectation the server may not respond immediately. If the server has no new information for the client when the poll is received, instead of sending an empty response, the server holds the request open and waits for response information to become available. Once it does have new information, the server immediately sends an HTTP response to the client, completing the open HTTP request. Upon receipt of the server response, the client often immediately issues another server request. In this way the usual response latency (the time between when the information first becomes available at the next client request) otherwise associated with polling clients is eliminated.[15]

For example, BOSH is a popular, long-lived HTTP technique used as a long-polling alternative to a continuous TCP connection when such a connection is difficult or impossible to employ directly (e.g., in a web browser);[16] it is also an underlying technology in the XMPP, which Apple uses for its iCloud push support.
</details>
