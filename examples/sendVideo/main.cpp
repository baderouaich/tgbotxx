#include <tgbotxx/tgbotxx.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <algorithm>
#include <csignal>
#include <array>
using namespace tgbotxx;

class VideoBot final : public Bot {
public:
  VideoBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Register my commands 
    Ptr<BotCommand> localVideoCmd(new BotCommand());
    localVideoCmd->command = "/local_video";
    localVideoCmd->description = "Get video from bot videos/ directory";
    Ptr<BotCommand> networkVideoCmd(new BotCommand());
    networkVideoCmd->command = "/network_video";
    networkVideoCmd->description = "Get video from the internet (URL)";
    api()->setMyCommands({localVideoCmd, networkVideoCmd});

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
    std::srand(std::time(nullptr));
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if (message->text == "/local_video")
    {
      cpr::File video(std::string(VIDEOS_DIR) + "/video.mp4");
      api()->sendVideo(message->chat->id, video);
    }
    else if (message->text == "/network_video")
    {
      static std::array<std::string, 6> imageUrls = {
        // Bots can currently send video files of up to 50 MB in size, this limit may be changed in the future.
        "https://www.pexels.com/download/video/5752729/?fps=30.0&h=240&w=426",
        "https://www.pexels.com/download/video/3209828/?fps=25.0&h=240&w=426",
        "https://www.pexels.com/download/video/5532765/?fps=25.0&h=426&w=226",
        "https://www.pexels.com/download/video/5532771/?fps=25.0&h=426&w=226",
        "https://www.pexels.com/download/video/5722113/?fps=25.0&h=426&w=226",
        "https://www.pexels.com/download/video/7220850/?fps=25.0&h=426&w=226"
      };
      std::string randomVideoUrl = imageUrls[std::rand() % imageUrls.size()];
      std::cout << randomVideoUrl << std::endl;
      api()->sendVideo(message->chat->id, randomVideoUrl);
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
   
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nsend_video_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<VideoBot> BOT(new VideoBot(argv[1]));
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
