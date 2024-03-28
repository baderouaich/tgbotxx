## Bot Error Handling
- This library is using exceptions to manage errors. Wrapping Api methods with a try catch will be the ideal way. 
- To detect long polling errors, override the `onLongPollError` callback. (Bot will keep running after this callback is triggered, except if you call Bot::stop())
- Within the thrown `tgbotxx::Exception`, you can access the error message `Exception::what()` and error code enum `Exception::errorCode()`
## Example

```cpp
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

class MyBot : public Bot {
  public:
    void onLongPollError(const std::string& errorMessage, ErrorCode errorCode) override {
      // Handle long polling error
      // Note: Bot will keep running even if this callback is triggered, to stop the bot call Bot::stop();
      std::cerr << "Long poll error: " << errorMessage << " (error_code: " << (int)errorCode << ")" << std::endl;
    }

    void onAnyMessage(const Ptr<Message>& msg) override {
        try {
          // Your logic
          api()->sendMessage(msg->chat->id, "Possible failure");
        } catch(const Exception& e) {
          // handle api()->sendMessage() failure
          std::cerr << "sendMessage failed! reason: " << e.what() << " (error_code: " << (int)e.errorCode() << ")" << std::endl;
          switch(e.errorCode()) {
            case ErrorCode::FORBIDDEN:
                std::cerr << "Blocked by user\n";
                break;
            case ErrorCode::FLOOD:
                std::cout << "Flood, try again later..\n";
                break;
            case ErrorCode::UNAUTHORIZED:
                std::cout << "Need permission..\n";
                break;
            ...
          }
        }
    }

    void onCommand(const Ptr<Message>& msg) override {
      try {
        // Your logic
        api()->sendPoll(msg->chat->id, poll);
      } catch(const Exception& e) {
        // handle api()->sendPoll() failure with ErrorCode enum
        switch(e.errorCode()) {
            case ErrorCode::FORBIDDEN:
                std::cerr << "Blocked by user\n";
                break;
            case ErrorCode::FLOOD:
                std::cout << "Flood, try again later..\n";
                break;
            ...
        }
      }
    }
    

    
    // ...
};

int main() {
  MyBot bot;
  bot.start(); // <- start the bot long polling loop 
}
```
