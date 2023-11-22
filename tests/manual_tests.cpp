#include "tgbotxx/objects/ChatAdministratorRights.hpp"
#include "tgbotxx/objects/MenuButton.hpp"
#include "tgbotxx/objects/PollOption.hpp"
#include "tgbotxx/objects/WebAppInfo.hpp"
#include "tgbotxx/objects/WebhookInfo.hpp"
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
      //      api()->setTimeout(std::chrono::seconds(60 * 3));
      //      api()->setLongPollTimeout(std::chrono::seconds(60 * 2));
      // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
      // in Telegram server before they get deleted or retrieved by BOT)
      getApi()->deleteWebhook(true);
      //      api()->setMyName("tgbotxx manual_tests");
      //      api()->setMyDescription("tgbotxx bot manual tests");

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
      Ptr<BotCommand> userProfilePhotos(new BotCommand());
      userProfilePhotos->command = "/user_profile_photos";
      userProfilePhotos->description = "You will receive a location";
      Ptr<BotCommand> ban(new BotCommand());
      ban->command = "/ban";
      ban->description = "You will be banned for 1 minute seconds";
      Ptr<BotCommand> poll(new BotCommand());
      poll->command = "/poll";
      poll->description = "You will receive a voting poll";
      Ptr<BotCommand> quiz(new BotCommand());
      quiz->command = "/quiz";
      quiz->description = "You will receive a quiz poll";
      Ptr<BotCommand> webhookInfo(new BotCommand());
      webhookInfo->command = "/webhook_info";
      webhookInfo->description = "You will receive webhook info in JSON";
      Ptr<BotCommand> botName(new BotCommand());
      botName->command = "/bot_name";
      botName->description = "You will receive bot name";
      Ptr<BotCommand> menuButtonWebApp(new BotCommand());
      menuButtonWebApp->command = "/menubutton_webapp";
      menuButtonWebApp->description = "Change Menu button to MenuButtonWebApp";
      Ptr<BotCommand> menuButtonDefault(new BotCommand());
      menuButtonDefault->command = "/menubutton_default";
      menuButtonDefault->description = "Change Menu button to default (MenuButtonCommands)";
      Ptr<BotCommand> showAdministratorRights(new BotCommand());
      showAdministratorRights->command = "/show_administrator_rights";
      showAdministratorRights->description = "Display bot's default administrator rights in JSON";
      Ptr<BotCommand> editMessageText(new BotCommand());
      editMessageText->command = "/edit_message_text";
      editMessageText->description = "You will receive a message that its text will be edited every second for 10 seconds.";
      Ptr<BotCommand> deleteMessage(new BotCommand());
      deleteMessage->command = "/delete_message";
      deleteMessage->description = "You will receive a message then it will be deleted after 2 seconds.";
      getApi()->setMyCommands({greet, stop, photo, buttons, audio, document, animation, voice, mediaGroup, location, userProfilePhotos, ban, poll, quiz, webhookInfo, botName, menuButtonWebApp, menuButtonDefault, showAdministratorRights, editMessageText, deleteMessage}); // The above commands will be shown in the bot chat menu (bottom left)

      std::cout << __func__ << ": " << api()->getMyName()->name << " bot started!" << std::endl;
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
        std::string bytes = api()->downloadFile(docFile->filePath);
        std::cout << "downloaded document " << bytes.size() << " bytes\n";
      }
      if (not message->photo.empty()) {
        Ptr<File> docFile = api()->getFile(message->photo[0]->fileId);
        std::string bytes = api()->downloadFile(docFile->filePath);
        std::cout << "downloaded image " << bytes.size() << " bytes\n";
      }
    }

    /// Called when a non-command message is received of any kind - text, photo, sticker, etc.
    void onNonCommandMessage(const Ptr<Message>& message) override {
      //std::cout << __func__ << ": " << message->text << std::endl;
    }

    void onLongPollError(const std::string& reason) override {
      std::cerr << "Long polling error: " << reason << std::endl;
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
        getApi()->sendPhoto(message->chat->id, std::string("https://www.hdwallpapers.in/download/landscape_view_of_sunset_under_yellow_black_cloudy_sky_4k_5k_hd_nature-5120x2880.jpg"));
        getApi()->sendMessage(message->chat->id, "Sending File photo...");
        getApi()->sendPhoto(message->chat->id, fs::path{"/home/bader/Pictures/2021/05/30/thumb-1920-642642.jpg"});
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
        getApi()->sendAudio(message->chat->id, fs::path{"/media/bader/6296B2EC60F91DB6/Entertainment/Music/Navy Modern General Quarters Sound Effect.m4a"});
      } else if (message->text == "/document") {
        getApi()->sendMessage(message->chat->id, "Sending local document ...");
        getApi()->sendDocument(message->chat->id, fs::path{__FILE__});
        getApi()->sendMessage(message->chat->id, "Sending document from the internet ...");
        getApi()->sendDocument(message->chat->id, std::string("https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2816r0.pdf"));
      } else if (message->text == "/animation") {
        getApi()->sendMessage(message->chat->id, "Sending animation ...");
        getApi()->sendDocument(message->chat->id, std::string("https://media2.giphy.com/media/cXblnKXr2BQOaYnTni/giphy.gif"));
      } else if (message->text == "/voice") {
        getApi()->sendMessage(message->chat->id, "Sending voice message ...");
        getApi()->sendDocument(message->chat->id, std::string("https://freetestdata.com/wp-content/uploads/2021/09/Free_Test_Data_100KB_OGG.ogg"));
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
      } else if (message->text == "/user_profile_photos") {
        std::int64_t userId = message->from->id;
        Ptr<UserProfilePhotos> userProfilePhotos = api()->getUserProfilePhotos(userId);
        api()->sendMessage(message->chat->id, "You have " + std::to_string(userProfilePhotos->totalCount) + " profile photos");
        for (const std::vector<Ptr<PhotoSize>>& photoResolutions: userProfilePhotos->photos) {
          for (const Ptr<PhotoSize>& photo: photoResolutions) {
            Ptr<File> photoFile = api()->getFile(photo->fileId);
            std::string bytes = api()->downloadFile(photoFile->filePath);
            std::ofstream{photoFile->fileUniqueId + ".jpg"} << bytes;
            std::cout << "Downloaded.\n";
          }
        }
      } else if (message->text == "/ban") {
        std::time_t now = std::time(nullptr);
        std::time_t oneMinuteAfter = now + 60;
        api()->sendMessage(message->chat->id, "Banning you for 1 minute. You will be able to use this bot after " + DateTimeUtils::toString(oneMinuteAfter));
        api()->banChatMember(message->chat->id, message->from->id, oneMinuteAfter);
      } else if (message->text == "/poll") {
        std::vector<std::string> options = {
          "Answer 1",
          "Answer 2",
          "Answer 3",
        };
        api()->sendPoll(message->chat->id, "Please choose an answer", options);
      } else if (message->text == "/quiz") {
        std::string question = "Which of the following empires had no written language: Incan, Aztec, Egyptian, Roman? ";
        std::vector<std::string> possibleAnswers = {
          "Aztec",
          "Egyptian",
          "Incan", // CORRECT answer index = 2
          "Roman",
        };
        std::int32_t correctAnswerIndex = 2;
        std::string explanation = "The Incas didn't have a written language in the way you might expect."
                                  " Instead, the way they recorded information was through a system of "
                                  "different knots tied in ropes attached to a longer cord."; // optional (0-200 character explanation will be shown to user as a notification after answer>)
        api()->sendPoll(message->chat->id, question, possibleAnswers, false, "quiz", false, correctAnswerIndex, explanation);
      } else if (message->text == "/webhook_info") {
        Ptr<WebhookInfo> info = api()->getWebhookInfo();
        api()->sendMessage(message->chat->id, info->toJson().dump(2));
      } else if (message->text == "/bot_name") {
        Ptr<BotName> botName = api()->getMyName();
        api()->sendMessage(message->chat->id, botName->name);
      } else if (message->text == "/menubutton_webapp") {
        Ptr<WebAppInfo> webApp(new WebAppInfo());
        webApp->url = "https://google.com";
        Ptr<MenuButtonWebApp> menuButtonWebApp(new MenuButtonWebApp());
        menuButtonWebApp->text = "Click Me";
        menuButtonWebApp->webApp = webApp;
        api()->setChatMenuButton(message->chat->id, menuButtonWebApp);
      } else if (message->text == "/menubutton_default") {
        Ptr<MenuButtonDefault> menuButtonDefault(new MenuButtonDefault());
        api()->setChatMenuButton(message->chat->id, menuButtonDefault);
      } else if (message->text == "/show_administrator_rights") {
        Ptr<ChatAdministratorRights> chatAdministratorRights = api()->getMyDefaultAdministratorRights();
        api()->sendMessage(message->chat->id, chatAdministratorRights->toJson().dump(2));
      } else if (message->text == "/edit_message_text") {
        Ptr<Message> originalMessage = api()->sendMessage(message->chat->id, "Progress started...");
        for (int i = 0; i <= 100; i += 10) {
          std::this_thread::sleep_for(std::chrono::seconds(1));
          std::ostringstream oss{};
          oss << "Progress: " << i << '/' << 100;
          api()->editMessageText(oss.str(), originalMessage->chat->id, originalMessage->messageId);
        }
        api()->editMessageText("Done.", originalMessage->chat->id, originalMessage->messageId);
      } else if (message->text == "/delete_message") {
        Ptr<Message> twoSecondsMsg = api()->sendMessage(message->chat->id, "Hello! my life span is 2 seconds only so I don't have much time. Goodbye!");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        api()->deleteMessage(twoSecondsMsg->chat->id, twoSecondsMsg->messageId);
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
      const Ptr<PollOption>& highestVotedOption = *std::max_element(poll->options.begin(), poll->options.end(), [](const Ptr<PollOption>& A, const Ptr<PollOption>& B) {
        return A->voterCount < B->voterCount;
      });
      std::cout << __func__ << ": Highest voted option: " << highestVotedOption->text << std::endl;
    }
    /// Called when a user changed their answer in a non-anonymous poll.
    void onPollAnswer(const Ptr<PollAnswer>& pollAnswer) override {
      std::cout << __func__ << ": " << pollAnswer->optionIds.front() << std::endl;
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

int main() try {
  static MyBot bot(getToken());
  std::signal(SIGINT, [](int) {
    std::cout << "Stopping Bot. Please wait...\n";
    bot.stop();
    std::exit(EXIT_SUCCESS);
  });
  bot.start();
  return EXIT_SUCCESS;
} catch (const std::exception& e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
