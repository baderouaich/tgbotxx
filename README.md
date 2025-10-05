<!--
> **Warning**
>
> this library is still under development.
>
 ![](https://geps.dev/progress/80) 
-->
[![MIT License](https://img.shields.io/badge/license-MIT-yellow)](https://github.com/baderouaich/tgbotxx/blob/main/LICENSE)
[![Docs](https://codedocs.xyz/doxygen/doxygen.svg)](https://baderouaich.github.io/tgbotxx)
[![Language](https://img.shields.io/badge/C++-20-blue.svg?style=flat&logo=c%2B%2B)](https://img.shields.io/badge/C++-20-blue.svg?style=flat&logo=c%2B%2B)

# tgbotxx

Telegram Bot C++ Library

Compatible with Telegram [Bot API 9.2 (August 15, 2025)](https://core.telegram.org/bots/api-changelog)

[//]: # (### Third party libs)

[//]: # (- [nlohmann-json]&#40;https://github.com/nlohmann/json&#41; for JSON parsing)

[//]: # (- [cpr]&#40;https://github.com/libcpr/cpr&#41; for HTTP client)

### CI Status

| Operating system | Build status                                                                                                                                                                                      |
|------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Ubuntu (x64)     | [![Ubuntu](https://img.shields.io/github/actions/workflow/status/baderouaich/tgbotxx/build-ubuntu.yml?branch=main)](https://github.com/baderouaich/tgbotxx/actions/workflows/build-ubuntu.yml)    |
| Windows (x64)    | [![Windows](https://img.shields.io/github/actions/workflow/status/baderouaich/tgbotxx/build-windows.yml?branch=main)](https://github.com/baderouaich/tgbotxx/actions/workflows/build-windows.yml) |
| macOS            | [![macOS](https://img.shields.io/github/actions/workflow/status/baderouaich/tgbotxx/build-macos.yml?branch=main)](https://github.com/baderouaich/tgbotxx/actions/workflows/build-macos.yml)       | 

### Examples

> see [examples](examples/) for more

| Example                                                       | Description                                                                                                                      |                                           Preview                                           |
|:--------------------------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------:|
| [WeatherBot](examples/WeatherBot)                             | Bot that displays the weather information of a city using the [weather api](https://www.weatherapi.com/).                        |          <img src="examples/WeatherBot/img/preview.jpg" alt="preview" width="200">          |
| [EarthquakeBot](examples/EarthquakeBot)                       | Bot that will alert you if there is a recent earthquake somewhere in the world.                                                  |         <img src="examples/EarthquakeBot/img/alerts.jpg" alt="preview" width="200">         |
| [QrCodeBot](examples/QrCodeBot)                               | Bot that can generate QrCode images from text and extract text from QrCode Images.                                               |           <img src="examples/QrCodeBot/img/encode.jpg" alt="preview" width="200">           |
| [UrlShortenerBot](examples/UrlShortenerBot)                   | Bot for shortening URLs.                                                                                                         |       <img src="examples/UrlShortenerBot/img/preview.jpg" alt="preview" width="200">        |
| [Inline Buttons](examples/Buttons/InlineKeyboardButton)       | Bot that uses inline keyboard buttons to interact with users.                                                                    | <img src="examples/Buttons/InlineKeyboardButton/img/preview.jpg" alt="preview" width="200"> |
| [Keyboard Buttons](examples/Buttons/ReplyKeyboardMarkup)      | Bot that uses keyboard buttons to interact with users.                                                                           | <img src="examples/Buttons/ReplyKeyboardMarkup/img/preview.jpg" alt="preview" width="200">  |
| [PaidSubscriptionBot](examples/PaidSubscriptionBot)           | Bot that offers it's services for a paid subscription.                                                                           |   <img src="examples/PaidSubscriptionBot/photos/checkout2.jpg" alt="preview" width="200">   |
| [ThreadPoolBot](examples/ThreadPoolBot)                       | Bot that uses a ThreadPool to handle multiple requests simultaneously.                                                           |        <img src="examples/ThreadPoolBot/img/preview2.png" alt="preview" width="200">        |
| [GitWatcherBot](https://github.com/baderouaich/GitWatcherBot) | Real world Bot that you can use to watch repositories changes and get notified about (stars, forks, issues, watchers and pulls). |           <img src="https://i.ibb.co/XDXV2PZ/NEW.jpg" alt="preview" width="200">            |

[//]: # (### Usage)

[//]: # ()

[//]: # (This library is using Inheritance-Based Extensibility technique providing a Bot class which you can inherit from)

[//]: # (and optionally override callback events depending on your Bot needs.)

[//]: # ()

[//]: # (This also allows you to instantiate multiple bots in the same program. Just make sure each Bot is running on a separate)

[//]: # (thread. )

#### Basic sample

> see [examples](examples/) for more

```cpp
#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {
public:
  MyBot() : Bot("Bot token here from @BotFather") {}
    
private:
  // Called before Bot starts receiving updates
  void onStart() override {
    // Initialize your code here...
    std::cout << "Bot Started\n";
  }
  
  // Called before Bot shuts down (triggered by Bot::stop())
  void onStop() override {
    // Cleanup your code here
    std::cout << "Bot Stopped\n";
  }
  
  // Called when Bot receives a new message of any kind
  // NB: Ptr<T> = std::shared_ptr<T>
  void onAnyMessage(const Ptr<Message>& message) override {
    std::string reply = "Hi " + message->from->firstName
                        + "!, got your message!";
    api()->sendMessage(message->chat->id, reply);
  }
  
  // override other callbacks if needed... 
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}
```

#### Extensive sample

Creating a new Bot called `MyBot` that overrides all callbacks:
<details>
<summary>Show</summary>

```cpp
#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {
public:
    MyBot() : Bot("BOT_TOKEN_FROM_BOT_FATHER") {}

private:
    /// Called before Bot starts receiving updates (triggered by Bot::start())
    /// Use this callback to initialize your code, set commands..
    void onStart() override {
      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      api()->deleteWebhook(true);

      // Register bot commands ...
      Ptr<BotCommand> greet(new BotCommand());
      greet->command = "greet";
      greet->description = "This command will greet you";
      Ptr<BotCommand> stop(new BotCommand());
      stop->command = "stop";
      stop->description = "Stop the bot";
      api()->setMyCommands({greet, stop}); // The above commands will be shown in the bot chat menu (bottom left)
      
      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }
    
    /// Called when Bot is about to be stopped (triggered by Bot::stop())
    void onStop() override {
      /// Cleanup your code in this callback (close handles, backup data...)
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }
    
    /// Called when a new message is received of any kind - text, photo, sticker, etc.
    void onAnyMessage(const Ptr<Message>& message) override {
        api()->sendMessage(message->chat->id, "Hi " + message->from->firstName + "!, got your message!");
    }
    
    /// Called when a new command is received (messages with leading '/' char).
    void onCommand(const Ptr<Message>& message) override {
      if(message->text == "/stop") {
        api()->sendMessage(message->chat->id, "Bot stopping...");
        Bot::stop();
        return;
      }
    }
    
    /// Called when long polling fails
    void onLongPollError(const std::string& errorMessage, ErrorCode errorCode) override {
      std::cerr <<  "Long polling error: " << errorMessage << ". Error code: " << errorCode << std::endl;
    }
    
    /// @brief Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message>& message) override {}
    
    /// @brief Called when an unknown command is received (messages with leading '/' char).
    /// @note Known commands are set with Bot::setCommands()
    void onUnknownCommand(const Ptr<Message>& message) override {}

    /// @brief Called when a new version of a message that is known to the bot and was edited
    void onEditedMessage(const Ptr<Message>& editedMessage) override {}

    /// @brief Called when a reaction to a message was changed by a user.
    /// @note The bot must be an administrator in the chat and must explicitly specify "message_reaction" in the list of allowed_updates to receive these updates using Api::setAllowedUpdates().
    /// The update isn't received for reactions set by bots.
    void onMessageReactionUpdated(const Ptr<MessageReactionUpdated>& messageReaction) override {}

    /// @brief Called when reactions to a message with anonymous reactions were changed.
    /// @note The bot must be an administrator in the chat and must explicitly specify "message_reaction_count" in the list of allowed_updates to receive these updates using Api::setAllowedUpdates().
    /// The updates are grouped and can be sent with delay up to a few minutes.
    void onMessageReactionCountUpdated(const Ptr<MessageReactionCountUpdated>& messageReactionCount) override {}

    /// @brief Called when a new incoming inline query is received
    void onInlineQuery(const Ptr<InlineQuery>& inlineQuery) override {}

    /// @brief Called when the result of an inline query that was chosen by a user and sent to their chat partner.
    /// @note Please see our documentation on the feedback collecting for details on how to enable these updates for your bot. https://core.telegram.org/bots/inline#collecting-feedback
    void onChosenInlineResult(const Ptr<ChosenInlineResult>& chosenInlineResult) override {}

    /// @brief Called when a new incoming callback query is received
    void onCallbackQuery(const Ptr<CallbackQuery>& callbackQuery) override {}

    /// @brief Called when a new incoming shipping query is received.
    /// @note Only for invoices with flexible price
    void onShippingQuery(const Ptr<ShippingQuery>& shippingQuery) override {}

    /// @brief Called when a new incoming pre-checkout query is received. Contains full information about checkout
    void onPreCheckoutQuery(const Ptr<PreCheckoutQuery>& preCheckoutQuery) override {}

    /// @brief Called when a new poll state is received.
    /// @note Bots receive only updates about stopped polls and polls, which are sent by the bot
    void onPoll(const Ptr<Poll>& poll) override {}

    /// @brief Called when a user changed their answer in a non-anonymous poll.
    /// @note Bots receive new votes only in polls that were sent by the bot itself.
    void onPollAnswer(const Ptr<PollAnswer>& pollAnswer) override {}

    /// @brief Called when the bot's chat member status was updated in a chat.
    /// @note For private chats, this update is received only when the bot is blocked or unblocked by the user.
    void onMyChatMember(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) override {}

    /// @brief Called when a chat member's status was updated in a chat.
    /// @note The bot must be an administrator in the chat and must explicitly specify “chat_member” in the list of allowed_updates to receive these updates.
    void onChatMember(const Ptr<ChatMemberUpdated>& chatMemberUpdated) override {}

    /// @brief Called when a request to join the chat has been sent.
    /// @note The bot must have the can_invite_users administrator right in the chat to receive these updates.
    void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) override {}

    /// @brief Called when a chat boost was added or changed.
    void onChatBoostUpdated(const Ptr<ChatBoostUpdated>& chatBoostUpdated) override {}

    /// @brief Called when a boost was removed from a chat.
    void onChatBoostRemoved(const Ptr<ChatBoostRemoved>& chatBoostRemoved) override {}

    /// @brief Called when the long polling getUpdates fails.
    void onLongPollError(const std::string& errorMessage, ErrorCode errorCode) override {}
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}
```

</details>

### Usage (4 approaches)

#### 1. `FetchContent` *(recommended)*

Simply use CMake's `FetchContent` in your project's `CMakeLists.txt` as below:

```cmake
cmake_minimum_required(VERSION 3.20)
project(my_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(tgbotxx
        GIT_REPOSITORY "https://github.com/baderouaich/tgbotxx"
        GIT_TAG "v1.1.9.2" # Compatible with Telegram Api 9.2
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(tgbotxx)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx)
```

#### 2. `PkgConfig`: clone and install the library locally, then use PkgConfig:

<details>
  <summary>example</summary>

```shell
git clone https://github.com/baderouaich/tgbotxx
cd tgbotxx
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make install 
# On Windows run `make install` as administrator 
```

```cmake
cmake_minimum_required(VERSION 3.20)
project(my_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(tgbotxx REQUIRED tgbotxx)

if (NOT tgbotxx_FOUND)
    message(FATAL_ERROR "Did you install tgbotxx locally?")
endif ()

add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_LIBRARY_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${tgbotxx_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${tgbotxx_LIBRARIES})
```

</details>

#### 3. `find_package`: clone and install the library locally, then use find_package(tgbotxx REQUIRED):

<details>
  <summary>example</summary>

```cmake
cmake_minimum_required(VERSION 3.20)
project(my_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(tgbotxx REQUIRED)

if (NOT tgbotxx_FOUND)
    message(FATAL_ERROR "Did you install tgbotxx locally?")
endif ()

add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_LIBRARY_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${tgbotxx_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC ${tgbotxx_LIBRARIES})
```

</details>

#### 4. `Submodule`: Use tgbotxx as a project submodule (without installation)

<details>
  <summary>example</summary>

You can also use this library as a submodule in your bot project without the need of installing it in your system.
Use git clone or git submodule add the library:

```shell
git submodule add https://github.com/baderouaich/tgbotxx ./lib/tgbotxx
```

or

```shell
git clone https://github.com/baderouaich/tgbotxx ./lib/tgbotxx
```

Then add `add_subdirectory(lib/tgbotxx)` in your `CMakeLists.txt`.

```cmake
cmake_minimum_required(VERSION 3.20)
project(my_bot)

add_subdirectory(lib/tgbotxx) # <-- clone tgbotxx in your project's lib/ directory

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx) # <-- link with tgbotxx
```

</details>

### Other actively maintained Telegram Bot C++ Libraries

- [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp): C++ library for Telegram bot API
- [tgbot](https://github.com/egorpugin/tgbot): C++ library for Telegram Bot API with generated API types and methods

### Refs:

[Telegram Api Documentation](https://core.telegram.org/bots/api)

