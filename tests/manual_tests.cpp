#include <csignal>
#include <cstdlib>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>

using namespace tgbotxx;

class MyBot : public Bot {
  public:
    MyBot(const std::string& token) : Bot(token) {}

  private:
    /// Called before Bot starts receiving updates (triggered by Bot::start())
    /// Use this callback to initialize your code, set commands..
    void onStart() override {
      Ptr<User> me = getApi()->getMe();
      std::cout << __func__ << ": " << me->firstName << " bot started!" << std::endl;

      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      getApi()->deleteWebhook(true);

      // Register bot commands ...
      Ptr<BotCommand> greet(new BotCommand());
      greet->command = "/greet";
      greet->description = "This command will greet you";
      Ptr<BotCommand> stop(new BotCommand());
      stop->command = "/stop";
      stop->description = "Stop the bot";
      Ptr<BotCommand> photo(new BotCommand());
      photo->command = "/photo";
      photo->description = "You will receive a photo using Api::sendPhoto method";
      Ptr<BotCommand> buttons(new BotCommand());
      buttons->command = "/buttons";
      buttons->description = "You will receive an inline keyboard markup";
      Ptr<BotCommand> audio(new BotCommand());
      audio->command = "/audio";
      audio->description = "You will receive an audio";
      Ptr<BotCommand> document(new BotCommand());
      document->command = "/document";
      document->description = "You will receive a document";
      Ptr<BotCommand> animation(new BotCommand());
      animation->command = "/animation";
      animation->description = "You will receive an animation (GIF)";
      Ptr<BotCommand> voice(new BotCommand());
      voice->command = "/voice";
      voice->description = "You will receive a voice message";
      Ptr<BotCommand> mediaGroup(new BotCommand());
      mediaGroup->command = "/media_group";
      mediaGroup->description = "You will receive a media group";
      Ptr<BotCommand> location(new BotCommand());
      location->command = "/location";
      location->description = "You will receive a location";
      getApi()->setMyCommands({greet, stop, photo, buttons, audio, document, animation, voice, mediaGroup, location}); // The above commands will be shown in the bot chat menu (bottom left)
    }

    /// Called when Bot is about to be stopped (triggered by Bot::stop())
    /// Cleanup your code in this callback (close handles, backup data...)
    void onStop() override {
      std::cout << __func__ << ": " << getApi()->getMe()->firstName << " bot stopping..." << std::endl;
    }

    /// Called when a new message is received of any kind - text, photo, sticker, etc.
    void onAnyMessage(const Ptr<Message>& message) override {
      //std::cout << __func__ << ": " << message->toJson().dump(2) << std::endl;
      //Ptr<Message> msg = getApi()->sendMessage(message->chat->id, "Hi "+ message->from->firstName +", got ur msg");

      if (message->document) {
        Ptr<File> docFile = api()->getFile(message->document->fileId);
        std::string bytes = api()->downloadFile(docFile->filePath, [](cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow) -> bool {
          std::cout << "Downloading document " << downloadNow << " / " << downloadTotal << " bytes" << std::endl;
          // return false to cancel the download
          return true;
        });
      }
    }

    /// Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message>& message) override {
      //std::cout << __func__ << ": " << message->text << std::endl;
    }

    /// Called when a new command is received (messages with leading '/' char).
    void onCommand(const Ptr<Message>& message) override {
      //std::cout << __func__ << ": " << message->text << std::endl;
      if (message->text == "/stop") {
        Bot::stop();
        return;
      } else if (message->text == "/start") {
        getApi()->sendMessage(message->chat->id, "Welcome " + message->from->firstName + "!");
      } else if (message->text == "/greet") {
        getApi()->sendMessage(message->chat->id, "Good day!");
      } else if (message->text == "/photo") {
        getApi()->sendMessage(message->chat->id, "Sending URL photo...");
        getApi()->sendPhoto(message->chat->id, "https://www.hdwallpapers.in/download/landscape_view_of_sunset_under_yellow_black_cloudy_sky_4k_5k_hd_nature-5120x2880.jpg");
        getApi()->sendMessage(message->chat->id, "Sending File photo...");
        getApi()->sendPhoto(message->chat->id, cpr::File{"/home/bader/Pictures/2021/05/30/thumb-1920-642642.jpg"});
      } else if (message->text == "/buttons") {
        /*
            Create inline keyboard buttons
               7 8 9
               4 5 6
               1 2 3
                 0
           */
        Ptr<InlineKeyboardMarkup> keyboard(new InlineKeyboardMarkup());
        std::vector<Ptr<InlineKeyboardButton>> row;
        for (int i = 0; i <= 9; i++) {
          Ptr<InlineKeyboardButton> button(new InlineKeyboardButton());
          button->text = std::to_string(i);
          button->callbackData = button->text;
          row.push_back(button);
          if (i % 3 == 0 || !i) {
            keyboard->inlineKeyboard.push_back(row);
            row.clear();
          }
        }
        std::reverse(keyboard->inlineKeyboard.begin(), keyboard->inlineKeyboard.end());
        api()->sendMessage(message->chat->id, "Buttons:", 0, "", {}, false, false, false, 0, false, keyboard);
      } else if (message->text == "/audio") {
        getApi()->sendMessage(message->chat->id, "Sending audio file...");
        getApi()->sendAudio(message->chat->id, cpr::File{"/media/bader/6296B2EC60F91DB6/Programs & Entertainment/Music/Navy Modern General Quarters Sound Effect.m4a"});
      } else if (message->text == "/document") {
        getApi()->sendMessage(message->chat->id, "Sending local document ...");
        getApi()->sendDocument(message->chat->id, cpr::File{__FILE__});
        getApi()->sendMessage(message->chat->id, "Sending document from the internet ...");
        getApi()->sendDocument(message->chat->id, "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2816r0.pdf");
      } else if (message->text == "/animation") {
        getApi()->sendMessage(message->chat->id, "Sending animation ...");
        getApi()->sendDocument(message->chat->id, "https://media2.giphy.com/media/cXblnKXr2BQOaYnTni/giphy.gif");
      } else if (message->text == "/voice") {
        getApi()->sendMessage(message->chat->id, "Sending voice message ...");
        getApi()->sendDocument(message->chat->id, "https://freetestdata.com/wp-content/uploads/2021/09/Free_Test_Data_100KB_OGG.ogg");
      } else if (message->text == "/media_group") {
        {
          getApi()->sendMessage(message->chat->id, "Sending pdf media group ...");
          std::vector<Ptr<InputMedia>> mediaGroup;
          for (const std::string_view docURL: {"https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4928.pdf",
                                               "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4933.pdf",
                                               "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4934.pdf",
                                               "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2759r0.pdf"}) {
            Ptr<InputMediaDocument> document(new InputMediaDocument());
            document->media = docURL;
            mediaGroup.push_back(document);
          }
          api()->sendMediaGroup(message->chat->id, mediaGroup);
        }
        {
          getApi()->sendMessage(message->chat->id, "Sending photo media group ...");
          std::vector<Ptr<InputMedia>> mediaGroup;
          for (const std::string_view photoURL: {"https://images.alphacoders.com/129/1299740.jpg",
                                                 "https://images2.alphacoders.com/112/1128233.jpg",
                                                 "https://images2.alphacoders.com/131/1311487.jpg",
                                                 "https://images5.alphacoders.com/129/1295587.jpg",
                                                 "https://images5.alphacoders.com/121/1217119.png",
                                                 "https://images6.alphacoders.com/510/510365.jpg"}) {
            Ptr<InputMediaPhoto> photo(new InputMediaPhoto());
            photo->media = photoURL;
            photo->hasSpoiler = !!(std::rand() % 3);
            mediaGroup.push_back(photo);
          }
          api()->sendMediaGroup(message->chat->id, mediaGroup);
        }
      } else if (message->text == "/location") {
        getApi()->sendMessage(message->chat->id, "Sending location ...");
        getApi()->sendLocation(message->chat->id, 65.590261f, -17.303453f); // Iceland
      }
    }

    /// Called when a new incoming callback query is received (e.g inline button callback query)
    void onCallbackQuery(const Ptr<CallbackQuery>& callbackQuery) override {
      std::cout << "You have clicked #" << callbackQuery->data << " button!" << std::endl;
      api()->sendMessage(callbackQuery->message->chat->id, "You have clicked #" + callbackQuery->data + " button!");
    }

    /// Called when an unknown command is received (messages with leading '/' char).
    /// Known commands are set with Bot::setCommands()
    void onUnknownCommand(const Ptr<Message>& message) override {
      std::cout << __func__ << ": " << message->text << std::endl;
    }

    // Other callbacks (optional overload)
    /// Called when a new version of a message that is known to the bot and was edited
    void onEditedMessage(const Ptr<Message>& editedMessage) override {
      std::cout << __func__ << ": " << editedMessage->text << std::endl;
    }
    /// Called when a new incoming inline query is received
    void onInlineQuery(const Ptr<InlineQuery>& inlineQuery) override {
      std::cout << __func__ << ": " << inlineQuery->query << std::endl;
    }
    /// Called when the result of an inline query that was chosen by a user and sent to their chat partner.
    void onChosenInlineResult(const Ptr<ChosenInlineResult>& chosenInlineResult) override {
      std::cout << __func__ << ": " << chosenInlineResult->query << std::endl;
    }
    /// Called when a new incoming shipping query is received.
    void onShippingQuery(const Ptr<ShippingQuery>& shippingQuery) override {
      std::cout << __func__ << ": " << shippingQuery->invoicePayload << std::endl;
    }
    /// Called when a new incoming pre-checkout query is received. Contains full information about checkout
    void onPreCheckoutQuery(const Ptr<PreCheckoutQuery>& preCheckoutQuery) override {
      std::cout << __func__ << ": " << preCheckoutQuery->invoicePayload << std::endl;
    }
    /// Called when a new poll state is received.
    void onPoll(const Ptr<Poll>& poll) override {
      std::cout << __func__ << ": " << poll->question << std::endl;
    }
    /// Called when a user changed their answer in a non-anonymous poll.
    void onPollAnswer(const Ptr<PollAnswer>& pollAnswer) override {
      std::cout << __func__ << ": " << pollAnswer->pollId << std::endl;
    }
    /// Called when the bot's chat member status was updated in a chat.
    void onMyChatMember(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) override {
      std::cout << __func__ << ": " << myChatMemberUpdated->from->username << std::endl;
    }
    /// Called when a chat member's status was updated in a chat.
    void onChatMember(const Ptr<ChatMemberUpdated>& chatMemberUpdated) override {
      std::cout << __func__ << ": " << chatMemberUpdated->from->username << std::endl;
    }
    /// Called when a A request to join the chat has been sent.
    void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) override {
      std::cout << __func__ << ": " << chatJoinRequest->from->username << std::endl;
    }
};

static std::string getToken() {
  if (char *token = std::getenv("TESTS_BOT_TOKEN"); token != nullptr)
    return std::string(token);
  throw std::runtime_error("Couldn't find TESTS_BOT_TOKEN in the env; please export an environment variable TESTS_BOT_TOKEN with your bot token");
}

int main() {
  static MyBot bot(getToken());
  std::signal(SIGINT, [](int) {
    std::cout << "Stopping Bot. Please wait...\n";
    bot.stop();
  });
  bot.start();
  return 0;
}
