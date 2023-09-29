> **Warning**
>
> this library is still under development.
>
 ![](https://geps.dev/progress/50) 


# tgbotxx
Telegram Bot C++ Library

Compatible with Telegram [Bot API 6.9 (September 22, 2023)](https://core.telegram.org/bots/api-changelog)

### Usage
```cpp
#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
using namespace tgbotxx;

class MyBot : public Bot {
public:
    MyBot() : Bot("BOT_TOKEN_FROM_BOTH_FATHER") {}

private:
    /// Called before Bot starts receiving updates (triggered by Bot::start())
    /// Use this callback to initialize your code, set commands..
    void onStart() override {
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
    
    /// Called when Bot is about to be stopped (triggered by Bot::stop())
    void onStop() override {
        /// Cleanup your code in this callback (close handles, backup data...)
    }
    
    /// Called when a new message is received of any kind - text, photo, sticker, etc.
    void onAnyMessage(const Ptr<Message>& message) override {
        getApi()->sendMessage(message->chat->id, "Hi " + message->from->firstName + "!, got your message!");
    }
    
    /// Called when a new command is received (messages with leading '/' char).
    void onCommand(const Ptr<Message>& message) override {
      if(message->text == "/stop") {
        getApi()->sendMessage(message->chat->id, "Bot stopping...");
        Bot::stop();
        return;
      }
    }
    
    // Other callbacks (optional overload)
    /// Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message> &message) override {}
    /// Called when an unknown command is received (messages with leading '/' char).
    /// Known commands are set with Bot::setCommands()
    void onUnknownCommand(const Ptr<Message> &message) override {}
    /// Called when a new version of a message that is known to the bot and was edited
    void onEditedMessage(const Ptr<Message>& editedMessage) override {}
    /// Called when a new incoming inline query is received
    void onInlineQuery(const Ptr<InlineQuery>& inlineQuery) override {}
    /// Called when the result of an inline query that was chosen by a user and sent to their chat partner.
    void onChosenInlineResult(const Ptr<ChosenInlineResult>& chosenInlineResult) override {}
    /// Called when a new incoming callback query is received
    void onCallbackQuery(const Ptr<CallbackQuery>& callbackQuery) override {}
    /// Called when a new incoming shipping query is received.
    void onShippingQuery(const Ptr<ShippingQuery>& shippingQuery) override {}
    /// Called when a new incoming pre-checkout query is received. Contains full information about checkout
    void onPreCheckoutQuery(const Ptr<PreCheckoutQuery>& preCheckoutQuery) override {}
    /// Called when a new poll state is received.
    void onPoll(const Ptr<Poll>& poll) override {}
    /// Called when a user changed their answer in a non-anonymous poll.
    void onPollAnswer(const Ptr<PollAnswer>& pollAnswer) override {}
    /// Called when the bot's chat member status was updated in a chat.
    void onMyChatMember(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) override {}
    /// Called when a chat member's status was updated in a chat.
    void onChatMember(const Ptr<ChatMemberUpdated>& chatMemberUpdated) override {}
    /// Called when a A request to join the chat has been sent.
    void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) override {}
};

int main() {
  MyBot bot;
  bot.start();
  return 0;
}
```


### Install the library
```bash
git clone https://github.com/baderouaich/tgbotxx
cd tgbotxx
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
sudo make install
```
-  *Requirements (will be downloaded by cmake if not found in system)*
    - [cpr](https://github.com/libcpr/cpr)
    - [nlohmann_json](https://github.com/nlohmann/json)


### Ref:
[Telegram Api Documentation](https://core.telegram.org/bots/api)

[Telegram Api Schema](https://core.telegram.org/schema) [Json Schema](https://core.telegram.org/schema/json)