#define CATCH_CONFIG_MAIN
#include <chrono>
#include <catch2/catch.hpp>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;
using namespace std::chrono_literals;

thread_local static Ptr<Api> API(new Api(std::getenv("TESTS_BOT_TOKEN") ?: "BOT_TOKEN"));


TEST_CASE("Test Api", "methods") {
  SECTION("getMe") {
    Ptr<User> me = API->getMe();
    REQUIRE(me);
    REQUIRE(me->isBot);
    REQUIRE(not me->username.empty());
    REQUIRE(not me->firstName.empty());
    REQUIRE(me->id != 0);
  }

  SECTION("deleteWebhook") {
    REQUIRE(API->deleteWebhook(false));
    REQUIRE(API->deleteWebhook(true));
  }

  SECTION("Cache") {
    REQUIRE(API->getMe()->username == API->getCache().botUsername);
    auto apiCommands = API->getMyCommands();
    auto cachedCommands = API->getCache().botCommands;
    REQUIRE(apiCommands.size() == cachedCommands.size());
    if (apiCommands.size() == cachedCommands.size()) {
      for (std::size_t i = 0; i < apiCommands.size(); ++i) {
        // std::cout << cachedCommands[i] << std::endl;
        REQUIRE(apiCommands[i]->command == cachedCommands[i]);
      }
    }
  }

  SECTION("timeouts") {
    std::srand(std::time(nullptr));
    for (int i = 0; i < 100; i++) {
      cpr::Timeout longPollTimeout = std::chrono::seconds(std::rand() % 1'000);
      cpr::Timeout timeout = std::chrono::seconds(std::rand() % 1'000);
      if (!!(std::rand() % 2)) {
        API->setLongPollTimeout(longPollTimeout);
        API->setTimeout(timeout);
      } else {
        API->setTimeout(timeout);
        API->setLongPollTimeout(longPollTimeout);
      }
      // Api request timeout should always be longer than long poll timeout.
      // Otherwise, the api request will time out before long polling finishes.
      REQUIRE(API->getLongPollTimeout().ms < API->getTimeout().ms);
    }
  }

  SECTION("Limit updates") {
    REQUIRE(API->getUpdatesLimit() == 100);
    API->setUpdatesLimit(30);
    REQUIRE(API->getUpdatesLimit() == 30);
    API->setUpdatesLimit(250);
    REQUIRE(API->getUpdatesLimit() == 100);
    API->setUpdatesLimit(-250);
    REQUIRE(API->getUpdatesLimit() == 1);
  }
}

TEST_CASE("Test Api ErrorCodes", "ErrorCode") {
  SECTION("Invalid chat/user id - ErrorCode::BAD_REQUEST") {
    try {
      auto invalid_chat_id = 0;
      API->sendMessage(invalid_chat_id, "test msg");
    } catch (const tgbotxx::Exception& e) {
      std::cerr << e.what() << " (" << e.errorCode() << ") " << std::endl;
      REQUIRE(e.errorCode() == ErrorCode::BAD_REQUEST);
      REQUIRE(std::string(e.what()) == "Bad Request: chat not found");
    }
  }

  SECTION("getUpdates Long polling cancellation - ErrorCode::REQUEST_CANCELLED") {
    std::shared_ptr<std::atomic<bool>> cancellationParam{new std::atomic<bool>{true}};

    std::thread([cancellationParam]() {
      std::cout << "Sleeping for 5s before cancelling long polling..." << std::endl;
      std::this_thread::sleep_for(5s);
      std::cout << "Cancelling long polling getUpdates()" << std::endl;
      *cancellationParam = false; // cancels long polling after 5s
    }).detach();

    API->setUpdatesLimit(100);
    API->setLongPollTimeout(5min);
    try {
      API->getUpdates(0, cancellationParam);
      REQUIRE(false);
    } catch (const tgbotxx::Exception& ex) {
      std::cout << ex.what() << " - " << ex.errorCode() << std::endl;
      REQUIRE(ex.errorCode() == tgbotxx::ErrorCode::REQUEST_CANCELLED);
    }
  }

  // Other error codes to be tested in manual_tests.cpp
}