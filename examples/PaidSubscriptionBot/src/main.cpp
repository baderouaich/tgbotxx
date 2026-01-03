#include "PaidSubscriptionBot.hpp"
#include <csignal>

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\npaid_subscription_bot \"BOT_TOKEN\" \"PAYMENT_PROVIDER_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  // Create a single instance of the bot
  static std::unique_ptr<PaidSubscriptionBot> BOT(new PaidSubscriptionBot(argv[1], argv[2]));

  // Graceful Bot exit on critical signals (CTRL+C, abort, seg fault...)
  for(const int sig : {/*Ctrl+C*/SIGINT,
                       /*sys kill*/SIGKILL,
                       /*std::abort*/SIGABRT,
                       /*seg fault*/SIGSEGV,
                       /*std::terminate*/SIGTERM})
  {
    std::signal(sig, [](int s) {
      if(BOT) {
        std::cout << "Stopping Bot. Please wait..." << std::endl;
        BOT->stop();
      }
    });
  }

  // Start the bot
  BOT->start();
  std::cout << "Bot Stopped." << std::endl;
  return EXIT_SUCCESS;
}
