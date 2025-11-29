#include <tgbotxx/tgbotxx.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <csignal>
using namespace tgbotxx;

class DocumentBot final : public Bot {
public:
  DocumentBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Register my commands 
    Ptr<BotCommand> localDocumentCmd(new BotCommand());
    localDocumentCmd->command = "/local_document";
    localDocumentCmd->description = "Get document file from bot directory";
    Ptr<BotCommand> networkDocumentCmd(new BotCommand());
    networkDocumentCmd->command = "/network_document";
    networkDocumentCmd->description = "Get document from the internet (URL)";
    api()->setMyCommands({localDocumentCmd, networkDocumentCmd});

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if (message->text == "/local_document")
    {
      cpr::File documentFile(__FILE__);
      api()->sendDocument(message->chat->id, documentFile);
    }
    else if (message->text == "/network_document")
    {
      std::string documentUrl = "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2816r0.pdf";
      api()->sendDocument(message->chat->id, documentUrl);
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
   
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\ndocument_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<DocumentBot> BOT(new DocumentBot(argv[1]));
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
