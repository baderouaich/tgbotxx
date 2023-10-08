#include <cpr/cpr.h>
#include <csignal>
#include <iostream>
#include <regex>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

class UrlShortenerBot : public Bot {
  public:
    UrlShortenerBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      // Drop pending updates
      api()->deleteWebhook(true);

      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onAnyMessage(const Ptr<Message>& message) override {
      if (isUrl(message->text)) {
        std::string shortUrl = shortenUrl(message->text);
        api()->sendMessage(message->chat->id, shortUrl);
      }
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
    }

  protected:
    bool isUrl(const std::string& text) {
      /// @ref https://stackoverflow.com/questions/66373198/regexp-for-url-validation
      static std::regex urlRegex(R"(^(?:(?:https?|ftp)://)(?:\S+@)?(?:(?!10(?:\.\d{1,3}){3})(?!127(?:\.\d{1,3}){3})(?!169\.254(?:\.\d{1,3}){2})(?!192\.168(?:\.\d{1,3}){2})(?!172\.(?:1[6-9]|2\d|3[0-1])(?:\.\d{1,3}){2})(?:[1-9]\d?|1\d\d|2[01]\d|22[0-3])(?:\.(?:1?\d{1,2}|2[0-4]\d|25[0-5])){2}(?:\.(?:[1-9]\d?|1\d\d|2[0-4]\d|25[0-4]))|(?:[a-z\u00a1-\uffff0-9]+-)*[a-z\u00a1-\uffff0-9]+(?:\.(?:[a-z\u00a1-\uffff0-9]+-)*[a-z\u00a1-\uffff0-9]+)*(?:\.(?:[a-z\u00a1-\uffff]{2,})))(?::\d{2,5})?(?:/\S*)?$)");
      return std::regex_match(text, urlRegex);
    }

    std::string shortenUrl(const std::string& longUrl) {
      std::ostringstream oss{};
      oss << "https://ulvis.net/api.php?url=" << longUrl << "&private=1";
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
    if (BOT) {
      std::cout << "Stopping Bot. Please wait...\n";
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });
  BOT->start();
  return EXIT_SUCCESS;
}
