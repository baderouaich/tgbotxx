#include <csignal>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;
#include <filesystem>
namespace fs = std::filesystem;

class ReceiveVideoBot final : public Bot {
  public:
    ReceiveVideoBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      if (message->video) {
        // Download video bytes from Telegram
        Ptr<File> videoFile = api()->getFile(message->video->fileId);
        std::string bytes = api()->downloadFile(videoFile->filePath, [](auto downloadTotal, auto downloadNow) -> bool {
          std::cout << "Downloading video " << downloadNow << "/" <<downloadTotal << " bytes..." <<std::endl;
          return true;
        });

        // Save video to a file
        fs::path filename = fs::path(videoFile->filePath).filename();
        std::ofstream ofs{filename, std::ios::binary};
        ofs << bytes;
        ofs.close();

        std::cout << "Downloaded video to " << filename.string() << " (" << bytes.size() << " bytes)\n";
      }
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nreceive_video_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<ReceiveVideoBot> BOT(new ReceiveVideoBot(argv[1]));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if (BOT) {
      std::cout << "Stopping Bot. Please wait..." << std::endl;
      BOT->stop();
    }
  });
  BOT->start();
  std::cout << "Bot Stopped." << std::endl;
  return EXIT_SUCCESS;
}
