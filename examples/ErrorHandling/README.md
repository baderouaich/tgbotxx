## Bot Error Handling
- This library is using exceptions to manage errors. Wrapping Api methods with a try catch will be the ideal way. 
- To detect long polling errors, override the `onLongPollError` callback. (Bot will keep running after this callback is triggered, except if you call Bot::stop())

## Example

```cpp
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

class MyBot : public Bot {
  public:
    void onLongPollError(const std::string& reason) override {
      // Handle long polling error
      // Note: Bot will keep running even if this callback is triggered, to stop the bot call Bot::stop();
      std::cerr << "Long poll error: " << reason << std::endl; 
    }

    void onAnyMessage(const Ptr<Message>& msg) override try {
        try {
          // Your logic
          api()->sendMessage(msg->chat->id, "Possible failure");
        } catch(const Exception& e) {
          // handle api()->sendMessage() failure
          std::cerr << "sendMessage failed! reason: " << e.what() << std::endl;
        }
    }

    void onCommand(const Ptr<Message>& msg) override {
      try {
        // Your logic
        api()->sendPoll(msg->chat->id, poll);
      } catch(const Exception& e) {
        // handle api()->sendPoll() failure
        std::cerr << "sendPoll failed! reason: " << e.what() << std::endl;
      }
    }
    
    // ...
};

int main() {
  MyBot bot;
  bot.start(); // <- start the bot long polling loop 
}
```
