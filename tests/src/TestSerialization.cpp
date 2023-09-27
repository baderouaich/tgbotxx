#define CATCH_CONFIG_MAIN
#include <tgbotxx/objects/User.hpp>
#include <catch2/catch.hpp>
using namespace tgbotxx;

TEST_CASE("Serialization & Deserialization", "User")
{
  nl::json obj = nl::json::object();
  obj["id"] = 1000;
  obj["username"] = "@test";
  obj["first_name"] = "first name";
  obj["last_name"] = "last name";
  obj["is_bot"] = false;
  User user(obj);
  REQUIRE(user.id == 1000);
  REQUIRE(user.username == "@test");
  REQUIRE(user.firstName == "first name");
  REQUIRE(user.lastName == "last name");
  REQUIRE(user.isBot == false);
}
