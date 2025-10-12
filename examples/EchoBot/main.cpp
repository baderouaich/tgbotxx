#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>
using namespace tgbotxx;

class EchoBot : public Bot {
public:
    EchoBot(const std::string& token) : Bot(token) { }

private:
    /// Called before Bot starts receiving updates (triggered by Bot::start())
    /// Use this callback to initialize your code, set commands..
    void onStart() override {
      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      api()->deleteWebhook(true);
      std::cout << "Bot " << api()->getMe()->firstName << " started\n";
    }
    
    /// Called when Bot is about to be stopped (triggered by Bot::stop())
    void onStop() override {
      /// Cleanup your code in this callback (close handles, backup data...)
      std::cout << "Bot " << api()->getMe()->firstName << " stopped\n";
    }
    
    /// Called when a new message is received of any kind - text, photo, sticker, etc.
    void onAnyMessage(const Ptr<Message>& message) override {
      std::cout << "Received " << message->text << " from " << message->from->username << std::endl;
      api()->sendMessage(message->chat->id, message->text); // Echo back message
    }
    
    /// ============ [OPTIONAL OVERLOAD] =============
    /// Called when a new command is received (messages with leading '/' char).
    void onCommand(const Ptr<Message>& message) override {}
    /// Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message> &message) override {}
    /// Called when an unknown command is received (messages with leading '/' char).
    /// Known commands are set with Bot::setCommands()
    void onUnknownCommand(const Ptr<Message> &message) override {}
    /// Called when a new version of a message that is known to the bot and was edited
    void onMessageEdited(const Ptr<Message>& editedMessage) override {}
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
    void onMyChatMemberUpdated(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) override {}
    /// Called when a chat member's status was updated in a chat.
    void onChatMemberUpdated(const Ptr<ChatMemberUpdated>& chatMemberUpdated) override {}
    /// Called when a A request to join the chat has been sent.
    void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) override {}
};

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\necho_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<EchoBot> BOT(new EchoBot(argv[1]));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if(BOT) {
      std::cout << "Stopping Bot. Please wait...\n";
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });
  BOT->start();
  return EXIT_SUCCESS;
}
