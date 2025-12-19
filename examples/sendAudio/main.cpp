#include <tgbotxx/tgbotxx.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <algorithm>
#include <csignal>
#include <array>
using namespace tgbotxx;

class AudioBot final : public Bot {
public:
  AudioBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Register my commands 
    Ptr<BotCommand> localAudioCmd(new BotCommand());
    localAudioCmd->command = "/local_audio";
    localAudioCmd->description = "Get audio file from bot audio/ directory";
    Ptr<BotCommand> networkAudioCmd(new BotCommand());
    networkAudioCmd->command = "/network_audio";
    networkAudioCmd->description = "Get audio from the internet (URL)";
    api()->setMyCommands({localAudioCmd, networkAudioCmd});

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
    std::srand(std::time(nullptr));
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if (message->text == "/local_audio")
    {
      cpr::File audioFile(std::string(AUDIOS_DIR) +  (!(std::rand() % 2) ? "/audio.mp3" : "/audio.m4a"));
      api()->sendAudio(message->chat->id, audioFile);
    }
    else if (message->text == "/network_audio")
    {
      static std::array<std::string, 6> audioUrls = {
          "https://samples-files.com/samples/Audio/mp3/sample-file-1.mp3",
          "https://samples-files.com/samples/Audio/mp3/sample-file-2.mp3",
          "https://samples-files.com/samples/Audio/mp3/sample-file-3.mp3"
      };
      std::string randomAudioUrl = audioUrls[std::rand() % audioUrls.size()];
      std::cout << randomAudioUrl << std::endl;
      api()->sendAudio(message->chat->id, randomAudioUrl);
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
   
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\naudio_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<AudioBot> BOT(new AudioBot(argv[1]));
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
