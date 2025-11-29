#include <tgbotxx/tgbotxx.hpp>
#include <iostream>
#include <chrono>
#include <cpr/threadpool.h>
#include <csignal>

using namespace tgbotxx;
using namespace std::chrono_literals;

class ThreadPoolBot final : public Bot {
public:
  ThreadPoolBot(const std::string &token) : Bot(token) {}

private:
  cpr::ThreadPool threadPool;

private:
  void onStart() override {
    std::cout << "Bot Started\n";

    // Init thread pool with up to 32 worker threads to do the submitted jobs
    threadPool.SetMaxThreadNum(32);
    // Set how many worker threads can minimally wait for new jobs,
    // 1 thread minimally is enough until there are more than 1 jobs to do then other worker threads will be created up to what we set in max above.
    threadPool.SetMinThreadNum(1);
    // Worker threads can idle up to 1 minute waiting for a job to do, this reduces CPU usage when there is nothing to do
    threadPool.SetMaxIdleTime(std::chrono::milliseconds(60 * 1000));
    // Start waiting for jobs to be submitted
    threadPool.Start();
  }

  void onStop() override {
    std::cout << "Bot Stopped\n";
    // Stop the thread pool
    threadPool.Stop();
  }


  void onNonCommandMessage(const Ptr<Message> &message) override {
    // Handle message in parallel by one of Thread pool worker threads
    threadPool.Submit([this, message]() -> void {
      handleNonCommandMessage(message);
    });
  }

  void onCommand(const Ptr<Message> &command) override {
    // Handle command in parallel by one of Thread pool worker threads
    threadPool.Submit([this, command]() -> void {
      handleCommand(command);
    });
  }

  // Handle non-command message by thread pool workers
  void handleNonCommandMessage(Ptr<Message> message) {
    std::cout << "Thread [" << std::this_thread::get_id() << "] is handling non command message: " << message->text << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Simulate actual work...
    std::cout << "Thread [id:" << std::this_thread::get_id() << "] non command message handled." << std::endl;
  }

  // Handle command message by thread pool workers
  void handleCommand(Ptr<Message> command) {
    std::cout << "Thread [id:" << std::this_thread::get_id() << "] is handling command: " << command->text << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10)); // Simulate actual work...
    std::cout << "Thread [id:" << std::this_thread::get_id() << "] command handled." << std::endl;
  }

};

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nthread_pool_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }

  // Create a single instance of the bot
  static std::unique_ptr<ThreadPoolBot> BOT(new ThreadPoolBot(argv[1]));

  // Graceful Bot exit CTRL+C
  std::signal(SIGINT, [](int s) {
    if (BOT) {
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });

  // Start the bot
  BOT->start();
  return EXIT_SUCCESS;
}
