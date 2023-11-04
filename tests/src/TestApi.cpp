#include <chrono>
#define CATCH_CONFIG_MAIN
#include <tgbotxx/tgbotxx.hpp>
#include <catch2/catch.hpp>
using namespace tgbotxx;

thread_local static Ptr<Api> API(new Api(std::getenv("TESTS_BOT_TOKEN") ?: "BOT_TOKEN"));


TEST_CASE("Test Api", "methods")
{
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
      cpr::Timeout longPollTimeout = std::chrono::seconds(60);
      cpr::Timeout timeout = std::chrono::seconds(70); // Must be longer than long polling timeout
      API->setLongPollTimeout(longPollTimeout);
      API->setTimeout(timeout);

      // Getters & setters
      REQUIRE(timeout.ms == API->getTimeout().ms);
      REQUIRE(longPollTimeout.ms == API->getLongPollTimeout().ms);

      // Try set a timeout that is less than long polling timeout
      REQUIRE_THROWS(API->setTimeout(std::chrono::seconds(30)));
      // .. or vice versa
      REQUIRE_THROWS(API->setLongPollTimeout(std::chrono::seconds(80)));
      REQUIRE_THROWS_AS(API->setLongPollTimeout(std::chrono::seconds(80)), Exception);

    }

}