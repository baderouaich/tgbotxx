#define CATCH_CONFIG_MAIN
#include <tgbotxx/tgbotxx.hpp>
#include <catch2/catch.hpp>
using namespace tgbotxx;

static Ptr<Api> API(new Api(std::getenv("TESTS_BOT_TOKEN") ?: "BOT_TOKEN"));

TEST_CASE("Test Api", "Api methods")
{
    REQUIRE(API->getMe());
    REQUIRE(API->deleteWebhook(true));
}