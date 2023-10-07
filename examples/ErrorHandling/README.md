## Bot Error Handling
This library is using exceptions to manage errors. Using try catch within the callbacks will be the ideal way:

## Example

```cpp
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

class MyBot : public Bot {
  public:
    void onStart() override try {
        // Your logic
    } catch(const std::exception& e) {
        // handle thrown exceptions from onStart
        std::cerr << e.what() << std::endl;
    }

    void onAnyMessage(const Ptr<Message>& msg) override try {
        // Your logic
    } catch(const std::exception& e) {
        // handle thrown exceptions from onAnyMessage
        std::cerr << e.what() << std::endl;
    }

    void onCommand(const Ptr<Message>& msg) override try {
        // Your logic
    } catch(const std::exception& e) {
        // handle thrown exceptions from onCommand
        std::cerr << e.what() << std::endl;
    }
    
    // ...
};

int main() {
  MyBot bot;
  try {
    bot.start();
  } catch(const std::exception& e) {
    // handle thrown exceptions from bot api long polling 
    std::cerr << e.what() << std::endl;
  }
}
```