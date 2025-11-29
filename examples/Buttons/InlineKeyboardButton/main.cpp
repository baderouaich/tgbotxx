#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>

using namespace tgbotxx;

class InlineButtonsBot final : public Bot {
public:
  InlineButtonsBot(const std::string &token) : Bot(token) {}

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
      /** === Create inline keyboard buttons === */
      /// InlineKeyboardMarkup:
      ///  Row ->
      ///  ______________   ______________
      /// |     Yes     |  |      No     | <--- 2x InlineKeyboardButton
      /// --------------   --------------
      Ptr<InlineKeyboardMarkup> keyboard(new InlineKeyboardMarkup());
      std::vector<Ptr<InlineKeyboardButton>> row;
      Ptr<InlineKeyboardButton> yesButton(new InlineKeyboardButton());
      yesButton->text = "Yes";
      yesButton->callbackData = "YesButton"; // will be received by below onCallbackQuery() method if the 'Yes' button was clicked.
      row.push_back(yesButton);
      Ptr<InlineKeyboardButton> noButton(new InlineKeyboardButton());
      noButton->text = "No";
      noButton->callbackData = "NoButton"; // will be received by below onCallbackQuery() method if the 'No' button was clicked.
      row.push_back(noButton);
      keyboard->inlineKeyboard.push_back(row);

      api()->sendMessage(message->chat->id, "Hello! Please click a button:", 0, "", {}, false, false, keyboard);
    }
  }

  void onCallbackQuery(const Ptr<CallbackQuery> &callbackQuery) override {
    auto chat = std::visit([](auto& msg) { return msg->chat; }, callbackQuery->message);
    if (callbackQuery->data == "YesButton") // callbackQuery->data will hold the InlineKeyboardButton::callbackData set above
    {
      api()->sendMessage(chat->id, "You have clicked the 'Yes' button!");
    } else if (callbackQuery->data == "NoButton") {
      api()->sendMessage(chat->id, "You have clicked the 'No' button!");
    }
  }

  void onStop() override {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\ninline_buttons \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<InlineButtonsBot> BOT(new InlineButtonsBot(argv[1]));
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
