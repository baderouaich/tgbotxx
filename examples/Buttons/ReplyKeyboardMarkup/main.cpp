#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>

using namespace tgbotxx;

class KeyboardButtonsBot : public Bot {
public:
  KeyboardButtonsBot(const std::string &token) : Bot(token) {}

private:
  void onStart() override {
    Ptr<BotCommand> startCmd(new BotCommand());
    startCmd->command = "/start";
    startCmd->description = "Start the Bot";
    api()->setMyCommands({startCmd});

    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void onCommand(const Ptr<Message> &message) override {
    if (message->text == "/start") {
      /*
        Create a reply keyboard buttons:
        ReplyKeyboardMarkup
        2 Rows ->
        button1 button2 <- x2 KeyboardButton
        button3 button4 <- x2 KeyboardButton
      */
      Ptr<ReplyKeyboardMarkup> replyKeyboardMarkup(new ReplyKeyboardMarkup());
      replyKeyboardMarkup->oneTimeKeyboard = true;
      replyKeyboardMarkup->resizeKeyboard = true;
      std::vector<Ptr<KeyboardButton>> row1, row2;
      Ptr<KeyboardButton> button1(new KeyboardButton());
      button1->text = "Button1";
      row1.push_back(button1);
      Ptr<KeyboardButton> button2(new KeyboardButton());
      button2->text = "Button2";
      row1.push_back(button2);
      Ptr<KeyboardButton> button3(new KeyboardButton());
      button3->text = "Button3";
      row2.push_back(button3);
      Ptr<KeyboardButton> button4(new KeyboardButton());
      button4->text = "Button4";
      row2.push_back(button4);
      replyKeyboardMarkup->keyboard.push_back(row1);
      replyKeyboardMarkup->keyboard.push_back(row2);

      // User will click a button, and we will receive button text as a message:
      api()->sendMessage(message->chat->id, "Please answer by clicking one of the buttons:",
                         0, "", {}, false, false, false, 0, false, replyKeyboardMarkup);

    }
  }

  void onStop() override {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nkeyboard_buttons \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<KeyboardButtonsBot> BOT(new KeyboardButtonsBot(argv[1]));
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
