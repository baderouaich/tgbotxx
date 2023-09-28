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
    /// Called before Bot starts receiving updates (triggered by Bot::start())
    /// Use this callback to initialize your code, set commands..
    void onStart() override {
      Ptr<User> me = getApi()->getMe();
      std::cout << __func__ << ": " << me->firstName << " bot started!" << std::endl;

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
    /// Cleanup your code in this callback (close handles, backup data...)
    void onStop() override {
      std::cout << __func__ << ": " << getApi()->getMe()->firstName << " bot stopped." << std::endl;
    }

    /// Called when a new message is received of any kind - text, photo, sticker, etc.
    void onAnyMessage(const Ptr<Message>& message) override {
      std::cout << __func__ << ": " << message->toJson().dump(2) << std::endl;
      Ptr<Message> msg = getApi()->sendMessage(message->chat->id, "Hi "+ message->from->firstName +", got ur msg");
    }

    /// Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message> &message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }

    /// Called when a new command is received (messages with leading '/' char).
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

    /// Called when an unknown command is received (messages with leading '/' char).
    /// Known commands are set with Bot::setCommands()
    void onUnknownCommand(const Ptr<Message> &message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }

    // Other callbacks (optional overload)
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