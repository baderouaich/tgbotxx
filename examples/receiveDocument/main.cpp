#include <csignal>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;
#include <filesystem>
namespace fs = std::filesystem;

class ReceiveDocumentBot final : public Bot {
  public:
    ReceiveDocumentBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      if (message->document) {
        // Download document bytes from Telegram
        Ptr<File> documentFile = api()->getFile(message->document->fileId);
        std::string bytes = api()->downloadFile(documentFile->filePath);

        // Save document to a file
        fs::path filename = fs::path(documentFile->filePath).filename();
        std::ofstream ofs{filename, std::ios::binary};
        ofs << bytes;
        ofs.close();

        std::cout << "Downloaded document to " << filename.string() << " (" << bytes.size() << " bytes)\n";
      }
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nreceive_document_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<ReceiveDocumentBot> BOT(new ReceiveDocumentBot(argv[1]));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if (BOT) {
      std::cout << "Stopping Bot. Please wait...\n";
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });
  BOT->start();
  return EXIT_SUCCESS;
}
