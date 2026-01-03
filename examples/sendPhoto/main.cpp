#include <tgbotxx/tgbotxx.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <algorithm>
#include <csignal>
#include <array>
using namespace tgbotxx;

class PhotoBot final : public Bot {
public:
  PhotoBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override {
    // Drop pending updates
    api()->deleteWebhook(true);

    // Register my commands 
    Ptr<BotCommand> localPhotoCmd(new BotCommand());
    localPhotoCmd->command = "/local_photo";
    localPhotoCmd->description = "Get photo from bot photos/ directory";
    Ptr<BotCommand> networkPhotoCmd(new BotCommand());
    networkPhotoCmd->command = "/network_photo";
    networkPhotoCmd->description = "Get photo from the internet (URL)";
    api()->setMyCommands({localPhotoCmd, networkPhotoCmd});

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
    std::srand(std::time(nullptr));
  }

  void onCommand(const Ptr<Message> &message) override
  {
    if (message->text == "/local_photo")
    {
      cpr::File image(std::string(PHOTOS_DIR) + "/image1.jpg");
      api()->sendPhoto(message->chat->id, image);
    }
    else if (message->text == "/network_photo")
    {
      static std::array<std::string, 6> imageUrls = { 
          // Notes: 
          // - The photo must be at most 10 MB in size. 
          // - The photo's width and height must not exceed 10000 in total.
          // - Width and height ratio must be at most 20
          "https://images.alphacoders.com/129/1299740.jpg",
          "https://images2.alphacoders.com/112/1128233.jpg",
          "https://images2.alphacoders.com/131/1311487.jpg",
          "https://images5.alphacoders.com/129/1295587.jpg",
          "https://images5.alphacoders.com/121/1217119.png",
          "https://images6.alphacoders.com/510/510365.jpg",
      };
      std::string randomImageUrl = imageUrls[std::rand() % imageUrls.size()];
      std::cout << randomImageUrl << std::endl;
      api()->sendPhoto(message->chat->id, randomImageUrl);
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
   
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nphoto_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<PhotoBot> BOT(new PhotoBot(argv[1]));
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
