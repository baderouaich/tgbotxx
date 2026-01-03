#include <csignal>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;
#include <filesystem>
namespace fs = std::filesystem;

class ReceiveAudioBot final : public Bot {
  public:
    ReceiveAudioBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      if (message->audio) { // Does this message have any audio file?
        // Download audio bytes from Telegram
        Ptr<File> audioFile = api()->getFile(message->audio->fileId);
        std::string bytes = api()->downloadFile(audioFile->filePath);

        // Save audio to a file
        fs::path filename = fs::path(audioFile->filePath).filename();
        std::ofstream ofs{filename, std::ios::binary};
        ofs << bytes;
        ofs.close();

        std::cout << "Downloaded audio to " << filename.string() << " (" << bytes.size() << " bytes)\n";
      }
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nreceive_audio_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<ReceiveAudioBot> BOT(new ReceiveAudioBot(argv[1]));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if (BOT) {
      std::cout << "Stopping Bot. Please wait..." << std::endl;
      BOT->stop();
    }
  });
  BOT->start();
  return EXIT_SUCCESS;
}
