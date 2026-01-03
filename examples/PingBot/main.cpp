#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>
using namespace tgbotxx;

class PingBot final : public Bot {
public:
  PingBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override
  {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Set my commands
    Ptr<BotCommand> pingCmd(new BotCommand());
    pingCmd->command = "/ping";
    pingCmd->description = "Ping bot. You'll receive pong!";
    api()->setMyCommands({ pingCmd });

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if(message->text == "/ping")
    {
      api()->sendMessage(message->chat->id, "pong!");
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nping_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<PingBot> BOT(new PingBot(argv[1]));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if(BOT) {
        std::cout << "Stopping Bot. Please wait..." << std::endl;
      BOT->stop();
    }
  });
  BOT->start();
  std::cout << "Bot Stopped." << std::endl;
  return EXIT_SUCCESS;
}
