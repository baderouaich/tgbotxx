#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <cpr/cpr.h>
#include <csignal>
using namespace tgbotxx;

class UrlShortenerBot : public Bot {
public:
  UrlShortenerBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override
  {
    // Drop pending updates
    api()->deleteWebhook(true);

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void onAnyMessage(const Ptr<Message> &message) override
  {
    if(isUrl(message->text))
    {
      std::string shortUrl = shortenUrl(message->text);
      api()->sendMessage(message->chat->id, shortUrl);
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }

protected:
  bool isUrl(const std::string& text){
    if(StringUtils::startsWith(text, "http")) return true;
    if(StringUtils::startsWith(text, "wwww.")) return true;
    return false;
  }

  std::string shortenUrl(const std::string& longUrl){
    std::ostringstream oss{};
    oss << "https://ulvis.net/api.php?url="
        << longUrl << "&private=1";
    cpr::Response res = cpr::Get(cpr::Url(oss.str()));
    return res.text;
  }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nurlshortener_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<UrlShortenerBot> BOT(new UrlShortenerBot(argv[1]));
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
