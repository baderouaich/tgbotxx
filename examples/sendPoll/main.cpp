#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <csignal>

using namespace tgbotxx;

class PollBot : public Bot {
public:
    explicit PollBot(const std::string &token) : Bot(token) {}

private:
    void onStart() override {
      api()->setMyName("Poll Bot");
      api()->setMyDescription("This Telegram Bot will send you voting and quiz polls using the Api::sendPoll() method."
                              " Click menu button to see commands.");

      // Register my commands
      Ptr<BotCommand> pollCmd(new BotCommand());
      pollCmd->command = "/poll";
      pollCmd->description = "Receive a voting poll";
      Ptr<BotCommand> quizCmd(new BotCommand());
      quizCmd->command = "/quiz";
      quizCmd->description = "Receive a quiz";
      api()->setMyCommands({pollCmd, quizCmd});

      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onCommand(const Ptr<Message> &message) override {
      if (message->text == "/poll") {
        std::string question = "What to improve in this library ?";
        std::vector<std::string> options = {"Performance", "Documentation", "Examples"};
        bool isAnonymous = false;
        std::string pollType = "regular";

        api()->sendPoll(message->chat->id, question, options, isAnonymous, pollType);
      }

      if (message->text == "/quiz") {
        std::string question = "Which of the following empires had no written language?";
        std::vector<std::string> options = {
                "Aztec",
                "Egyptian",
                "Incan", // CORRECT answer index = 2
                "Roman",
        };
        std::int32_t correctAnswerIndex = 2;
        std::string explanation = "The Incas didn't have a written language in the way you might expect."
                                  " Instead, the way they recorded information was through a system of "
                                  "different knots tied in ropes attached to a longer cord."; // optional (0-200 character explanation will be shown to user as a notification after answer>)
        bool isAnonymous = true;
        bool allowsMultipleAnswers = false;
        std::string pollType = "quiz"; // <--- NOTICE: different poll type
        api()->sendPoll(message->chat->id, question, options, isAnonymous, pollType, allowsMultipleAnswers,
                        correctAnswerIndex, explanation);
      }
    }


    /// Triggered when a "regular" voting poll is finished (see sendPoll(openPeriod, closePeriod) args)
    /// Triggered when a "quiz" poll is answered
    void onPoll(const Ptr<Poll> &poll) override {
      // Get highest voted option (for quiz there will be only one option which is the answered one)
      const Ptr<PollOption> &option = *std::max_element(poll->options.begin(), poll->options.end(),
                                                        [](const Ptr<PollOption> &A, const Ptr<PollOption> &B) {
                                                            return A->voterCount < B->voterCount;
                                                        });
      if (poll->type == "regular")
        std::cout << "onPoll: Highest voted option: " << option->text << std::endl;
      else if (poll->type == "quiz")
        std::cout << "onPoll: Quiz answer option: " << option->text << std::endl;
    }

    /// Triggered when a user answers a "regular" or "quiz" poll
    void onPollAnswer(const Ptr<PollAnswer> &pollAnswer) override {
      std::cout << "onPollAnswer: User " << pollAnswer->user->username << " answered poll " << pollAnswer->pollId
                << std::endl;
    }

    void onStop() override {
      std::cout << "Bot " << api()->getMe()->username << " Stopping...\n";
    }

};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nsend_poll_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<PollBot> BOT(new PollBot(argv[1]));
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
