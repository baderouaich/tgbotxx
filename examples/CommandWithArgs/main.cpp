#include <csignal>
#include <map>
#include <iostream>
#include <regex>
#include <tuple>
#include <tgbotxx/tgbotxx.hpp>

class CommandWithArgsBot final : public tgbotxx::Bot
{
public:
  CommandWithArgsBot(const std::string& token) : tgbotxx::Bot(token)
  {
  }

  using CommandHandler = void (CommandWithArgsBot::*)(std::int64_t senderId, const std::smatch& argsMatch);
  const std::map<std::tuple<const std::string_view, const std::string_view, const std::string_view>, CommandHandler> commandHandlers = {
    // command, regex, description: handler
    {{"/add", R"rgx(\/add ([0-9]+) ([0-9]+))rgx", "Addition - example: /add 2 8"}, &CommandWithArgsBot::handleCommandAdd},
    {{"/div", R"rgx(\/div ([0-9]+) ([0-9]+))rgx", "Division - example: /div 30 10"}, &CommandWithArgsBot::handleCommandDivide},
    {{"/mult", R"rgx(\/mult ([0-9]+) ([0-9]+))rgx", "Multiplication - example: /mult 256 128"}, &CommandWithArgsBot::handleCommandMultiply},
  };

private:
  void onStart() override
  {
    // Register my commands to be displayed in the Bot command menu list:
    std::vector<tgbotxx::Ptr<tgbotxx::BotCommand>> commands;
    commands.reserve(commandHandlers.size());
    for (const auto& command : commandHandlers | std::views::keys)
    {
      const auto& [cmdView, cmdRegexView, cmdDesc] = command;
      auto cmdPtr = tgbotxx::makePtr<tgbotxx::BotCommand>();
      cmdPtr->command = cmdView;
      cmdPtr->description = cmdDesc;
      commands.push_back(std::move(cmdPtr));
    }
    api()->setMyCommands(commands);


    std::cout << "Bot " << api()->getMe()->username << " Started\n";
  }

  void onAnyMessage(const tgbotxx::Ptr<tgbotxx::Message>& message) override
  {
    for (const auto& [command, handler] : commandHandlers)
    {
      const auto& [cmdView, cmdRegexView, cmdDesc] = command;
      std::smatch argsMatch{};
      if (std::regex_match(message->text, argsMatch, std::regex{cmdRegexView.data()}))
      {
        (this->*handler)(message->from->id, argsMatch);
        break;
      }
    }
  }

  void onStop() override
  {
    std::cout << "Bot " << api()->getMe()->username << " Stopped\n";
  }

private: // Command handlers
  // handler for: /add X Y
  void handleCommandAdd(std::int64_t senderId, const std::smatch& argsMatch)
  {
    const double leftNum = std::stod(argsMatch.str(1));
    const double rightNum = std::stod(argsMatch.str(2));

    api()->sendMessage(senderId, std::to_string(leftNum + rightNum));
  }

  // handler for: /div X Y
  void handleCommandDivide(std::int64_t senderId, const std::smatch& argsMatch)
  {
    const double leftNum = std::stod(argsMatch.str(1));
    const double rightNum = std::stod(argsMatch.str(2));
    if (rightNum == 0.0)
    {
      api()->sendMessage(senderId, "Division by zero!");
      return;
    }
    api()->sendMessage(senderId, std::to_string(leftNum / rightNum));
  }

  // handler for: /mult X Y
  void handleCommandMultiply(std::int64_t senderId, const std::smatch& argsMatch)
  {
    const double leftNum = std::stod(argsMatch.str(1));
    const double rightNum = std::stod(argsMatch.str(2));

    api()->sendMessage(senderId, std::to_string(leftNum * rightNum));
  }
};


int main(int argc, const char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Usage:\n" << argv[0] << " \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  static std::unique_ptr<CommandWithArgsBot> BOT(new CommandWithArgsBot(argv[1]));
  for (const int sig : {SIGINT, SIGTERM})
  {
    std::signal(sig, [](int)
    {
      // Graceful Bot exit on CTRL+C
      if (BOT)
      {
        std::cout << "Stopping Bot. Please wait..." << std::endl;
        BOT->stop();
      }
    });
  }
  BOT->start();
  return EXIT_SUCCESS;
}
