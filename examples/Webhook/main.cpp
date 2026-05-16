#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>
using namespace tgbotxx;

class WebhookBot final : public Bot {
public:
  WebhookBot() : Bot(std::getenv("BOT_TOKEN")) {}

private:
  /// Called before Bot starts receiving updates (triggered by Bot::start())
  /// Use this callback to initialize your code, set commands..
  void onStart() override {
    // Initialize webhook settings
    WebhookSettings ws{};
    ws.url = std::getenv("WEBHOOK_URL");
    ws.port = std::stoi(std::getenv("WEBHOOK_LISTENER_PORT"));
    ws.certificateFile = cpr::File{std::getenv("WEBHOOK_CERT_FILE")};
    ws.privateKeyFile = cpr::File{std::getenv("WEBHOOK_PRIVATE_FILE")};
    Bot::setWebhookSettings(ws);

    std::cout << "Bot " << api()->getMe()->firstName << " started\n";
  }

  /// Called when Bot is about to be stopped (triggered by Bot::stop())
  void onStop() override {
    /// Cleanup your code in this callback (close handles, backup data...)
    std::cout << "Bot " << api()->getMe()->firstName << " stopped\n";
  }

  /// Called when a new message is received of any kind - text, photo, sticker, etc.
  void onAnyMessage(const Ptr<Message> &message) override {
    std::cout << "Received " << message->text << " from " << message->from->username << std::endl;
    api()->sendMessage(message->chat->id, message->text); // Echo back message
  }

  /// @brief Called when there is an issue with the webhook listener.
  void onWebhookError(const std::string &errorMessage, ErrorCode errorCode) {
    std::cerr << "onWebhookError: " << errorMessage << std::endl;
  }
};

int main() {
  static std::unique_ptr<WebhookBot> BOT(new WebhookBot());
  std::signal(SIGINT, [](int) {
    // Graceful Bot exit on CTRL+C
    if (BOT) {
      std::cout << "Stopping Bot. Please wait..." << std::endl;
      BOT->stop();
    }
  });
  BOT->start();
  std::cout << "Bot Stopped." << std::endl;
  return EXIT_SUCCESS;
}
