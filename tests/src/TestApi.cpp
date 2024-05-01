#include <chrono>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

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
}

TEST_CASE("Test Api ErrorCodes", "ErrorCode") {
  SECTION("ErrorCode::BAD_REQUEST") {
    try {
      auto invalid_chat_id = 0;
      API->sendMessage(invalid_chat_id, "test msg");
    } catch (const tgbotxx::Exception& e) {
      std::cerr << e.what() << " (" << (int) e.errorCode() << ") " << std::endl;
      REQUIRE(e.errorCode() == ErrorCode::BAD_REQUEST);
      REQUIRE(std::string(e.what()) == "Bad Request: chat not found");
    }
  }

  // Other error codes to be tested in manual_tests.cpp
}