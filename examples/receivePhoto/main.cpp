#include <csignal>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;
#include <filesystem>
namespace fs = std::filesystem;

class ReceivePhotoBot final : public Bot {
  public:
    ReceivePhotoBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      if (not message->photo.empty()) {
        // Telegram creates multiple photo sizes for each received photo
        for (const Ptr<PhotoSize>& photo: message->photo) {
          // Download photo bytes from Telegram
          Ptr<File> photoFile = api()->getFile(photo->fileId);
          std::string bytes = api()->downloadFile(photoFile->filePath);
          // Save photo to a file
          fs::path filename = fs::path(photoFile->filePath).filename();
          std::ofstream ofs{filename, std::ios::binary};
          ofs << bytes;
          ofs.close();

          std::cout << "Downloaded photo to " << filename.string() << " (" << bytes.size() << " bytes)\n";
        }
      }
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nreceive_photo_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<ReceivePhotoBot> BOT(new ReceivePhotoBot(argv[1]));
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
