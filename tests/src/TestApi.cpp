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


}