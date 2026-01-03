#include "tgbotxx/objects/ChatAdministratorRights.hpp"
#include "tgbotxx/objects/InputPaidMedia.hpp"
#include "tgbotxx/objects/InputPollOption.hpp"
#include "tgbotxx/objects/MenuButton.hpp"
#include "tgbotxx/objects/PollOption.hpp"
#include "tgbotxx/objects/WebAppInfo.hpp"
#include "tgbotxx/objects/WebhookInfo.hpp"
#include "tgbotxx/objects/MessageEntity.hpp"
#include <csignal>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <tgbotxx/tgbotxx.hpp>
#include <ranges>

using namespace tgbotxx;

class MyBot final : public Bot {
  using CommandHandler = void (MyBot::*)(const Ptr<Message>&);
  const std::map<std::pair<std::string, std::string>, CommandHandler> commandHandlers = {
    // command, description: handler
    {{"/stop", "Stop the bot"}, &MyBot::handleCommandStop},
    {{"/greet", "This command will greet you"}, &MyBot::handleCommandGreet},
    {{"/photo", "You will receive a photo using Api::sendPhoto method"}, &MyBot::handleCommandPhoto},
    {{"/audio", "You will receive an audio"}, &MyBot::handleCommandAudio},
    {{"/document", "You will receive a document"}, &MyBot::handleCommandDocument},
    {{"/animation", "You will receive an animation (GIF)"}, &MyBot::handleCommandAnimation},
    {{"/voice", "You will receive a voice message"}, &MyBot::handleCommandVoice},
    {{"/location", "You will receive a location"}, &MyBot::handleCommandLocation},
    {{"/sticker", "You will receive a sticker"}, &MyBot::handleCommandSticker},
    {{"/poll", "You will receive a voting poll"}, &MyBot::handleCommandPoll},
    {{"/quiz", "You will receive a quiz poll"}, &MyBot::handleCommandQuiz},
    {{"/edit_message_text", "You will receive a message that its text will be edited every second for 10 seconds"}, &MyBot::handleCommandEditMessageText},
    {{"/delete_message", "You will receive a message then it will be deleted after 2 seconds"}, &MyBot::handleCommandDeleteMessage},
    {{"/reply_message", "I will reply the last message I sent"}, &MyBot::handleCommandReplyMessage},
    {{"/message_effect", "I will reply the last message I sent"}, &MyBot::handleCommandMessageEffect},
    {{"/bot_name", "You will receive bot name"}, &MyBot::handleCommandBotName},
    {{"/media_group", "You will receive a media group"}, &MyBot::handleCommandMediaGroup},
    {{"/inline_buttons", "You will receive an inline keyboard markup"}, &MyBot::handleCommandInlineButtons},
    {{"/reply_keyboard_buttons", "You will receive a reply keyboard markup buttons (buttons will be placed in place of keyboard)"}, &MyBot::handleCommandReplyKeyboardButtons},
    {{"/user_profile_photos", "You will receive your (public) profile photos"}, &MyBot::handleCommandUserProfilePhotos},
    {{"/ban", "You will be banned for 1 minute seconds"}, &MyBot::handleCommandBan},
    {{"/webhook_info", "You will receive webhook info in JSON"}, &MyBot::handleCommandWebhookInfo},
    {{"/menubutton_webapp", "Change Menu button to MenuButtonWebApp"}, &MyBot::handleCommandMenuButtonWebApp},
    {{"/menubutton_default", "Change Menu button to default (MenuButtonCommands)"}, &MyBot::handleCommandMenuButtonDefault},
    {{"/show_administrator_rights", "Display bot's default administrator rights (in groups)"}, &MyBot::handleCommandShowAdministratorRights},
    {{"/send_invoice", "You will receive a test invoice"}, &MyBot::handleCommandSendInvoice},
    {{"/create_invoice_link", "You will receive a test invoice link"}, &MyBot::handleCommandCreateInvoiceLink},
    {{"/test_bot_blocked_by_user", "Block the bot within 10s after u receive a message"}, &MyBot::handleCommandTestBotBlockedByUser},
    {{"/send_paid_media", "send paid media to be unlocked with stars"}, &MyBot::handleCommandSendPaidMedia},
  };

public:
  explicit MyBot(const std::string& token) : Bot(token) {
    std::cout << "TGBOTXX_VERSION=" << TGBOTXX_VERSION << std::endl;
    std::cout << "TGBOTXX_VERSION_MAJOR=" << TGBOTXX_VERSION_MAJOR << std::endl;
    std::cout << "TGBOTXX_VERSION_MINOR=" << TGBOTXX_VERSION_MINOR << std::endl;
    std::cout << "TGBOTXX_VERSION_PATCH=" << TGBOTXX_VERSION_PATCH << std::endl;
    std::cout << "TGBOTXX_VERSION_TWEAK=" << TGBOTXX_VERSION_TWEAK << std::endl;
  }

private:
  /// Called before Bot starts receiving updates (triggered by Bot::start())
  /// Use this callback to initialize your code, set commands..
  void onStart() override {

    //      api()->setTimeout(std::chrono::seconds(60 * 3));
    //      api()->setLongPollTimeout(std::chrono::seconds(60 * 2));
    // Drop awaiting updates (when Bot is not running, updates will remain 24 hours
    // in Telegram server before they get deleted or retrieved by BOT)
    //api()->deleteWebhook(true);
    api()->setLongPollTimeout(cpr::Timeout(std::chrono::seconds(300)));
    api()->setUpdatesLimit(3); // memory tight? process updates 3 by 3...
    assert(api()->getUpdatesLimit() == 3);
    //      api()->setAllowedUpdates({
    //        "message_reaction",
    //        "message_reaction_count"
    //      });
    //      api()->setMyName("tgbotxx manual_tests");
    //      api()->setMyDescription("tgbotxx bot manual tests");

    // Register bot commands ...
    std::vector<Ptr<BotCommand>> commands;
    commands.reserve(commandHandlers.size());
    for (const auto& cmdInfo: commandHandlers | std::views::keys) {
      const auto& [command, description] = cmdInfo;
      Ptr<BotCommand> cmd(new BotCommand());
      cmd->command = command;
      cmd->description = description;
      commands.push_back(std::move(cmd));
    }
    api()->setMyCommands(commands);


    std::cout << __func__ << ": " << api()->getMyName()->name << " bot started!" << std::endl;
  }

  /// Called when Bot is about to be stopped (triggered by Bot::stop())
  /// Cleanup your code in this callback (close handles, backup data...)
  void onStop() override {
    std::cout << __func__ << ": " << api()->getMe()->firstName << " bot stopping..." << std::endl;
  }

  /// Called when a new message is received of any kind - text, photo, sticker, etc.
  void onAnyMessage(const Ptr<Message>& message) override {
    // std::cout << __func__ << ": " << message->toJson().dump(2) << std::endl;
    //Ptr<Message> msg = api()->sendMessage(message->chat->id, "Hi "+ message->from->firstName +", got ur msg");

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
    std::cout << __func__ << ": " << message->text << std::endl;

    std::string msgEntities = "";
    for (const Ptr<MessageEntity>& entity: message->entities) {
      msgEntities += MessageEntity::TypeToString(entity->type).value();
      msgEntities += ',';
    }
    if (!msgEntities.empty()) {
      msgEntities.pop_back();
      api()->sendMessage(message->chat->id, "Message Entities are: " + msgEntities);
    }
  }

  void onLongPollError(const std::string& errorMessage, ErrorCode errorCode) override {
    switch (errorCode) {
      case ErrorCode::OTHER:
        std::cerr << "Long polling error: " << errorMessage << " (" << static_cast<int>(errorCode) << ") (" << errorCode << ")" << std::endl;
        break;
      case ErrorCode::SEE_OTHER:
      case ErrorCode::BAD_REQUEST:
      case ErrorCode::UNAUTHORIZED:
      case ErrorCode::FORBIDDEN:
      case ErrorCode::NOT_FOUND:
      case ErrorCode::NOT_ACCEPTABLE:
      case ErrorCode::FLOOD:
      case ErrorCode::CONFLICT:
      case ErrorCode::TOO_MANY_REQUESTS:
      case ErrorCode::BAD_GATEWAY:
      case ErrorCode::INTERNAL:
        std::cerr << "Long polling error: " << errorMessage << " (" << static_cast<int>(errorCode) << ") (" << errorCode << ")" << std::endl;
        break;
      case ErrorCode::REQUEST_CANCELLED:
        std::cout << "Long polling cancelled" << std::endl;
        break;
    }
  }

  /// Called when a new command is received (messages with leading '/' char).
  void onCommand(const Ptr<Message>& message) override {
    std::cout << __func__ << ": " << message->text << std::endl;

    static const std::string atMyUsername = '@' + api()->getMe()->username; // marked static to avoid to call it everytime we receive a command, see also api()->getCache().
    for (const auto& [cmdInfo, handler]: commandHandlers) {
      const auto& [command, desc] = cmdInfo;
      // look for /start or /start@myusername (in groups)
      if (command == message->text or message->text == command + atMyUsername) {
        // Call the proper command handler
        (this->*handler)(message);
        break;
      }
    }
  }

  /// Called when a new incoming callback query is received (e.g. inline button callback query)
  void onCallbackQuery(const Ptr<CallbackQuery>& callbackQuery) override {
    std::cout << "You have clicked #" << callbackQuery->data << " button!" << std::endl;
    auto chat = std::visit([](auto& msg) { return msg->chat; }, callbackQuery->message);
    api()->sendMessage(chat->id, "You have clicked #" + callbackQuery->data + " button!");
  }

  /// Called when an unknown command is received (messages with leading '/' char).
  /// Known commands are set with Bot::setCommands()
  void onUnknownCommand(const Ptr<Message>& message) override {
    std::cout << __func__ << ": " << message->text << std::endl;
  }

  // Other callbacks (optional overload)
  /// Called when a new version of a message that is known to the bot and was edited
  void onMessageEdited(const Ptr<Message>& editedMessage) override {
    std::cout << __func__ << ": " << editedMessage->text << std::endl;
  }
  /// Called when a new incoming inline query is received (when user writes in the chat text box: @botname QUERY)
  void onInlineQuery(const Ptr<InlineQuery>& inlineQuery) override {
    std::cout << __func__ << ": " << inlineQuery->query << std::endl;
    std::string query = inlineQuery->query;

    if (query.starts_with("photo")) {
      std::vector<Ptr<InlineQueryResult>> inlineQueryResults;
      for (const std::string_view photoURL: {"https://images.alphacoders.com/129/1299740.jpg",
                                             "https://images2.alphacoders.com/112/1128233.jpg",
                                             "https://images2.alphacoders.com/131/1311487.jpg"}) {
        auto photoPtr = makePtr<InlineQueryResultPhoto>();
        photoPtr->id = StringUtils::random(16);
        photoPtr->photoUrl = photoURL;
        photoPtr->thumbnailUrl = photoURL;
        inlineQueryResults.push_back(std::move(photoPtr));
      }
      try {
        api()->answerInlineQuery(inlineQuery->id, inlineQueryResults, 300, "");
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
    }
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
  void onMyChatMemberUpdated(const Ptr<ChatMemberUpdated>& myChatMemberUpdated) override {
    std::cout << __func__ << ": " << myChatMemberUpdated->from->username << std::endl;
  }
  /// Called when a chat member's status was updated in a chat.
  void onChatMemberUpdated(const Ptr<ChatMemberUpdated>& chatMemberUpdated) override {
    std::cout << __func__ << ": " << chatMemberUpdated->from->username << std::endl;
  }
  /// Called when a request to join the chat has been sent.
  void onChatJoinRequest(const Ptr<ChatJoinRequest>& chatJoinRequest) override {
    std::cout << __func__ << ": " << chatJoinRequest->from->username << std::endl;
  }
  void onMessageReactionUpdated(const Ptr<MessageReactionUpdated>& messageReaction) override {
    if (messageReaction->newReaction.empty()) {
      std::cout << __func__ << ": all reactions removed" << std::endl;
    } else {
      std::cout << __func__ << ": " << messageReaction->newReaction[0]->type << std::endl;
    }
  }
  void onMessageReactionCountUpdated(const Ptr<MessageReactionCountUpdated>& messageReactionCount) override {
    std::cout << __func__ << ": " << messageReactionCount->reactions.size() << std::endl;
  }
  void onChatBoostUpdated(const Ptr<ChatBoostUpdated>& chatBoostUpdated) override {
    std::cout << __func__ << ": " << chatBoostUpdated->boost->boostId << std::endl;
  }
  void onChatBoostRemoved(const Ptr<ChatBoostRemoved>& chatBoostRemoved) override {
    std::cout << __func__ << ": " << chatBoostRemoved->boostID << std::endl;
  }

private: // Command handlers
  void handleCommandStop([[maybe_unused]] const Ptr<Message>& message) {
    if (Bot::isRunning()) {
      Bot::stop();
    } else {
      api()->sendMessage(message->chat->id, "Stopping... Please wait.");
    }
  }
  void handleCommandGreet(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Good day!");
  }
  void handleCommandPhoto(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending URL photo...");
    api()->sendPhoto(message->chat->id, "https://www.hdwallpapers.in/download/landscape_view_of_sunset_under_yellow_black_cloudy_sky_4k_5k_hd_nature-5120x2880.jpg");
    api()->sendMessage(message->chat->id, "Sending File photo...");
    api()->sendPhoto(message->chat->id, cpr::File{(fs::path(__FILE__).parent_path().parent_path() / "examples/sendPhoto/photos/image1.jpg").string()});
  }
  void handleCommandInlineButtons(const Ptr<Message>& message) {
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
    std::ranges::reverse(keyboard->inlineKeyboard);
    api()->sendMessage(message->chat->id, "Buttons:", 0, "", {}, false, false, keyboard);
  }
  void handleCommandReplyKeyboardButtons(const Ptr<Message>& message) {
    /*
       * Bots are able to interpret free text input from users, but offering specific suggestions is often more intuitive –
       * this is where custom keyboards can be extremely useful.
        Whenever your bot sends a message, it can display a special keyboard with predefined reply options (see ReplyKeyboardMarkup).
        Telegram apps that receive the message will display your keyboard to the user. Using any of the buttons will immediately send the respective text.
        This way you can drastically simplify and streamline user interaction with your bot.

          Create a reply keyboard buttons
           button1 button2
           button3 button4
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

    api()->sendMessage(message->chat->id, "Keyboard buttons:", 0, "", {}, false, false, replyKeyboardMarkup);
  }
  void handleCommandAudio(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending audio file...");
    api()->sendAudio(message->chat->id, "https://samples-files.com/samples/Audio/mp3/sample-file-1.mp3");
  }
  void handleCommandDocument(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending local document ...");
    api()->sendDocument(message->chat->id, cpr::File{__FILE__});
    api()->sendMessage(message->chat->id, "Sending document from the internet ...");
    api()->sendDocument(message->chat->id, "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2816r0.pdf");
  }
  void handleCommandAnimation(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending animation ...");
    api()->sendDocument(message->chat->id, "https://media2.giphy.com/media/cXblnKXr2BQOaYnTni/giphy.gif");
  }
  void handleCommandVoice(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending voice message ...");
    api()->sendDocument(message->chat->id, "https://freetestdata.com/wp-content/uploads/2021/09/Free_Test_Data_100KB_OGG.ogg");
  }
  void handleCommandMediaGroup(const Ptr<Message>& message) {
    {
      api()->sendMessage(message->chat->id, "Sending pdf media group ...");
      std::vector<Ptr<InputMedia>> mediaGroup;
      for (const std::string docURL: {"https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4928.pdf",
                                      "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4933.pdf",
                                      "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4934.pdf",
                                      "https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p2759r0.pdf"}) {
        Ptr<InputMediaDocument> document(new InputMediaDocument());
        document->media = docURL;
        mediaGroup.push_back(document);
      }
      // add extra local doc
      Ptr<InputMediaDocument> localDoc(new InputMediaDocument());
      localDoc->media = cpr::File{__FILE__};
      mediaGroup.push_back(localDoc);

      api()->sendMediaGroup(message->chat->id, mediaGroup);
    }
    {
      api()->sendMessage(message->chat->id, "Sending photo media group ...");
      std::vector<Ptr<InputMedia>> mediaGroup;
      for (const fs::path& localPhotoPath: {fs::path(__FILE__).parent_path().parent_path() / "examples/sendPhoto/photos/image1.jpg",
                                            fs::path(__FILE__).parent_path().parent_path() / "examples/sendPhoto/photos/image2.jpg"}) {
        Ptr<InputMediaPhoto> photo(new InputMediaPhoto());
        photo->media = cpr::File{localPhotoPath.string()}; // Local
        photo->hasSpoiler = false;
        mediaGroup.push_back(photo);
      }
      for (const std::string photoURL: {"https://images.alphacoders.com/129/1299740.jpg",
                                        "https://images2.alphacoders.com/112/1128233.jpg",
                                        "https://images2.alphacoders.com/131/1311487.jpg",
                                        "https://images5.alphacoders.com/129/1295587.jpg",
                                        "https://images5.alphacoders.com/121/1217119.png",
                                        "https://images6.alphacoders.com/510/510365.jpg"}) {
        Ptr<InputMediaPhoto> photo(new InputMediaPhoto());
        photo->media = photoURL; // URL
        photo->hasSpoiler = false;
        mediaGroup.push_back(photo);
      }
      api()->sendMediaGroup(message->chat->id, mediaGroup);
    }
  }
  void handleCommandLocation(const Ptr<Message>& message) {
    api()->sendMessage(message->chat->id, "Sending location ...");
    api()->sendLocation(message->chat->id, 65.590261f, -17.303453f); // Iceland
  }
  void handleCommandSticker(const Ptr<Message>& message) {
    api()->sendSticker(message->chat->id, "https://t.ly/uQ6Zx");
  }
  void handleCommandUserProfilePhotos(const Ptr<Message>& message) {
    std::int64_t userId = message->from->id;
    Ptr<UserProfilePhotos> userProfilePhotos = api()->getUserProfilePhotos(userId);
    api()->sendMessage(message->chat->id, "You have " + std::to_string(userProfilePhotos->totalCount) + " profile photos");
    for (const std::vector<Ptr<PhotoSize>>& photoResolutions: userProfilePhotos->photos) {
      for (const Ptr<PhotoSize>& photo: photoResolutions) {
        Ptr<File> photoFile = api()->getFile(photo->fileId);
        std::string bytes = api()->downloadFile(photoFile->filePath, [](cpr::cpr_off_t downloadTotal, cpr::cpr_off_t downloadNow) -> bool {
          std::cout << "Downloading Photo " << downloadNow << " / " << downloadTotal << " bytes" << std::endl;
          // return false to cancel the download
          return true;
        });
        std::ofstream{photoFile->fileUniqueId + ".jpg"} << bytes;
      }
    }
  }
  void handleCommandBan(const Ptr<Message>& message) {
    std::time_t now = std::time(nullptr);
    std::time_t oneMinuteAfter = now + 60;
    api()->sendMessage(message->chat->id, "Banning you for 1 minute. You will be able to use this bot after " + DateTimeUtils::toString(oneMinuteAfter));
    api()->banChatMember(message->chat->id, message->from->id, oneMinuteAfter);
  }
  void handleCommandPoll(const Ptr<Message>& message) {
    std::vector<Ptr<InputPollOption>> options;
    Ptr<InputPollOption> option1 = makePtr<InputPollOption>();
    option1->text = "Answer 1";
    options.push_back(option1);
    Ptr<InputPollOption> option2 = makePtr<InputPollOption>();
    option2->text = "Answer 2";
    options.push_back(option2);
    Ptr<InputPollOption> option3 = makePtr<InputPollOption>();
    option3->text = "Answer 3";
    options.push_back(option3);
    api()->sendPoll(message->chat->id, "Please choose an answer", options);
  }
  void handleCommandQuiz(const Ptr<Message>& message) {
    std::string question = "Which of the following empires had no written language: Incan, Aztec, Egyptian, Roman? ";
    std::vector<Ptr<InputPollOption>> options;
    Ptr<InputPollOption> option1 = makePtr<InputPollOption>();
    option1->text = "Aztec";
    options.push_back(option1);
    Ptr<InputPollOption> option2 = makePtr<InputPollOption>();
    option2->text = "Egyptian";
    options.push_back(option2);
    Ptr<InputPollOption> option3 = makePtr<InputPollOption>();
    option3->text = "Incan"; // CORRECT answer index = 2
    options.push_back(option3);
    Ptr<InputPollOption> option4 = makePtr<InputPollOption>();
    option4->text = "Roman";
    options.push_back(option4);
    std::int32_t correctAnswerIndex = 2;
    std::string explanation =
      "The Incas didn't have a written language in the way you might expect."
      " Instead, the way they recorded information was through a system of "
      "different knots tied in ropes attached to a longer cord."; // optional (0-200 character explanation will be shown to user as a notification after answer>)
    api()->sendPoll(message->chat->id, question, options, 0, "", {}, false, "quiz", false, correctAnswerIndex, explanation);
  }
  void handleCommandWebhookInfo(const Ptr<Message>& message) {
    Ptr<WebhookInfo> info = api()->getWebhookInfo();
    api()->sendMessage(message->chat->id, info->toJson().dump(2));
  }
  void handleCommandBotName(const Ptr<Message>& message) {
    Ptr<BotName> botName = api()->getMyName();
    api()->sendMessage(message->chat->id, botName->name);
  }
  void handleCommandMenuButtonWebApp(const Ptr<Message>& message) {
    Ptr<WebAppInfo> webApp(new WebAppInfo());
    webApp->url = "https://google.com";
    Ptr<MenuButtonWebApp> menuButtonWebApp(new MenuButtonWebApp());
    menuButtonWebApp->text = "Click Me";
    menuButtonWebApp->webApp = webApp;
    api()->setChatMenuButton(message->chat->id, menuButtonWebApp);
  }
  void handleCommandMenuButtonDefault(const Ptr<Message>& message) {
    Ptr<MenuButtonDefault> menuButtonDefault(new MenuButtonDefault());
    api()->setChatMenuButton(message->chat->id, menuButtonDefault);
  }
  void handleCommandShowAdministratorRights(const Ptr<Message>& message) {
    Ptr<ChatAdministratorRights> chatAdministratorRights = api()->getMyDefaultAdministratorRights();
    api()->sendMessage(message->chat->id, chatAdministratorRights->toJson().dump(2));
  }
  void handleCommandEditMessageText(const Ptr<Message>& message) {
    Ptr<Message> originalMessage = api()->sendMessage(message->chat->id, "Progress started...");
    for (int i = 0; i <= 100; i += 10) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::ostringstream oss{};
      oss << "Progress: " << i << '/' << 100;
      api()->editMessageText(oss.str(), originalMessage->chat->id, originalMessage->messageId);
      // Note: current message must not be equal to previous message!!
    }
    api()->editMessageText("Done.", originalMessage->chat->id, originalMessage->messageId);
  }
  void handleCommandDeleteMessage(const Ptr<Message>& message) {
    Ptr<Message> twoSecondsMsg = api()->sendMessage(message->chat->id, "Hello! my life span is 2 seconds only so I don't have much time. Goodbye!");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    api()->deleteMessage(twoSecondsMsg->chat->id, twoSecondsMsg->messageId);
  }
  void handleCommandReplyMessage(const Ptr<Message>& message) {
    Ptr<Message> msg = api()->sendMessage(message->chat->id, "Hello! waiting to be replied to...");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto replyParams = makePtr<ReplyParameters>();
    replyParams->chatId = message->chat->id;
    replyParams->messageId = msg->messageId;
    api()->sendMessage(message->chat->id, "Done!", 0, "", {},
                       false, false, nullptr, "", 0, nullptr,
                       false, "", nullptr, replyParams);
  }
  void handleCommandMessageEffect(const Ptr<Message>& message) {
    // See https://stackoverflow.com/questions/78600012/message-effect-id-in-telegram-bot-api
    // See https://gist.github.com/wiz0u/2a6d40c8f635687be363d72251a264da (Telegram Bot API - All message_effect_id values)
    const std::unordered_map<std::string, std::string> effectIds = {
      {"👍", "5107584321108051014"},
      {"🎉", "5046509860389126442"},
      {"👎", "5104858069142078462"},
    };

    for (const auto& [emoji, effectId]: effectIds) {
      try {
        api()->sendMessage(message->chat->id, emoji, 0, "", {},
                           false, false, nullptr, "", 0, nullptr,
                           false, effectId, nullptr, nullptr);
        std::this_thread::sleep_for(std::chrono::seconds(1));
      } catch (const std::exception& e) {
        std::cerr << e.what() << ": " << emoji << " - " << effectId << std::endl;
      }
    }
  }
  void handleCommandSendInvoice(const Ptr<Message>& message) {
    const std::string providerToken = getPaymentProviderToken();
    if (providerToken.empty()) // Create telegram invoice that will be paid using stars
    {
      std::vector<Ptr<LabeledPrice>> prices;
      Ptr<LabeledPrice> originalPrice = std::make_shared<LabeledPrice>();
      originalPrice->label = "STARS";
      originalPrice->amount = 1000;
      prices.push_back(originalPrice);
      api()->sendInvoice(message->chat->id, "Product name", "Product description", "payload", "XTR", prices, providerToken);
    } else {
      std::vector<Ptr<LabeledPrice>> prices;
      Ptr<LabeledPrice> originalPrice = std::make_shared<LabeledPrice>();
      originalPrice->label = "Original price";
      originalPrice->amount = 150; // 1.50$
      prices.push_back(originalPrice);
      Ptr<LabeledPrice> discountPrice = std::make_shared<LabeledPrice>();
      discountPrice->label = "Discount";
      discountPrice->amount = -50; // -0.5$
      prices.push_back(discountPrice);
      api()->sendInvoice(message->chat->id, "Product name", "Product description", "payload", "USD", prices, providerToken);
    }
  }
  void handleCommandCreateInvoiceLink(const Ptr<Message>& message) {
    // Create invoice link
    const std::string providerToken = getPaymentProviderToken();
    if (providerToken.empty()) // Create telegram invoice that will be paid using stars
    {
      std::vector<Ptr<LabeledPrice>> prices;
      Ptr<LabeledPrice> originalPrice = std::make_shared<LabeledPrice>();
      originalPrice->label = "STARS";
      originalPrice->amount = 1000;
      prices.push_back(originalPrice);
      std::string link = api()->createInvoiceLink("Product name", "Product description", "payload", "XTR", prices, "", providerToken);
      // Send link to user
      api()->sendMessage(message->chat->id, link);
    } else {
      std::vector<Ptr<LabeledPrice>> prices;
      Ptr<LabeledPrice> originalPrice = std::make_shared<LabeledPrice>();
      originalPrice->label = "Original price";
      originalPrice->amount = 150; // 1.50$
      prices.push_back(originalPrice);
      Ptr<LabeledPrice> discountPrice = std::make_shared<LabeledPrice>();
      discountPrice->label = "Discount";
      discountPrice->amount = -50; // -0.5$
      prices.push_back(discountPrice);
      std::string link = api()->createInvoiceLink("Product name", "Product description", "payload", "USD", prices,
                                                  "", providerToken);
      // Send link to user
      api()->sendMessage(message->chat->id, link);
    }
  }
  void handleCommandTestBotBlockedByUser(const Ptr<Message>& message) {
    try {
      api()->sendMessage(message->from->id, "Block me now, I will try to send you a msg after 10 seconds");
      std::this_thread::sleep_for(std::chrono::seconds(10));
      api()->sendMessage(message->from->id, "You shouldn't receive this msg if you have blocked me"); // this will throw a tgbotxx::Exception(FORBIDDEN) if the user blocked us.
    } catch (const tgbotxx::Exception& e) {
      std::cerr << __func__ << ": " << e.what() << " (error_code: " << (int) e.errorCode() << ')' << std::endl;
      assert(e.errorCode() == ErrorCode::FORBIDDEN && std::string(e.what()) == "Forbidden: bot was blocked by the user");
    }
  }
  void handleCommandSendPaidMedia(const Ptr<Message>& message) {
    std::vector<Ptr<InputPaidMedia>> paidMedia;
    for (const std::string url: {"https://images.alphacoders.com/129/1299740.jpg",
                                 "https://images2.alphacoders.com/112/1128233.jpg",
                                 "https://images2.alphacoders.com/131/1311487.jpg"}) {
      Ptr<InputPaidMediaPhoto> photo(new InputPaidMediaPhoto());
      photo->media = url;
      paidMedia.push_back(photo);
    }
    // add local video to the order list
    Ptr<InputPaidMediaVideo> video(new InputPaidMediaVideo());
    video->media = cpr::File{(fs::path(__FILE__).parent_path().parent_path() / "examples/sendVideo/videos/video.mp4").string()}; // Local
    video->startTimestamp = 3;                                                                                                   // start from 3rd second
    video->supportsStreaming = true;
    paidMedia.push_back(video);

    constexpr std::int32_t starsPrice = 100;
    std::string payload = "some payload to receive back if this got purchased";
    api()->sendPaidMedia(message->from->id, starsPrice, paidMedia, payload);
    // the user will get access to the photos only after the payment is completed
  }


private:
  static std::string getPaymentProviderToken() {
    if (char* token = std::getenv("TESTS_PAYMENT_PROVIDER_TOKEN"); token != nullptr)
      return std::string(token);
    return {}; // empty? will use star payments
    // throw std::runtime_error("Couldn't find PAYMENT_PROVIDER_TOKEN in the env; please export an environment variable PAYMENT_PROVIDER_TOKEN with your payment provider token");
  }
};

static std::string getToken() {
  if (char* token = std::getenv("TESTS_BOT_TOKEN"); token != nullptr)
    return std::string(token);
  throw std::runtime_error("Couldn't find TESTS_BOT_TOKEN in the env; please export an environment variable TESTS_BOT_TOKEN with your bot token");
}

int main() try {
  // Create the bot
  static auto bot = std::make_unique<MyBot>(getToken());
  // Listen to stop signals for graceful bot exit
  for (const int sig: {SIGINT, SIGTERM, SIGHUP, SIGABRT}) {
    std::signal(sig, [](int sig) {
      std::cout << "Signal (" << sig << ") received! Stopping Bot. Please wait..." << std::endl;
      bot->stop();
    });
  }
  // Start the bot
  std::cout << "Bot Starting..." << std::endl;
  bot->start();
  std::cout << "Bot Stopped" << std::endl;
  return EXIT_SUCCESS;
} catch (const std::exception& e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
} catch (...) {
  std::cerr << "Unknown Error" << std::endl;
  return EXIT_FAILURE;
}
