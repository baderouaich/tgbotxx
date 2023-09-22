#define CATCH_CONFIG_MAIN
#include <tgbotxx/tgbotxx.hpp>
#include <catch2/catch.hpp>
using namespace tgbotxx;

TEST_CASE("StringUtils", "endsWith & startsWith")
{
    std::string A = "Hello, world";
    SECTION("don't ignore case"){
      REQUIRE(StringUtils::startsWith(A, "Hello"));
      REQUIRE(StringUtils::endsWith(A, "world"));
    }
    SECTION("ignore case"){
      REQUIRE(StringUtils::startsWith(A, "Hello", true));
      REQUIRE(StringUtils::endsWith(A, "world", true));
    }
}