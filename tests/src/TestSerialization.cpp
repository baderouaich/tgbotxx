#define CATCH_CONFIG_MAIN
#include <tgbotxx/objects/User.hpp>
#include <catch2/catch.hpp>
using namespace tgbotxx;

TEST_CASE("Serialization & Deserialization", "User")
{
  User user;
  user.id = 1444;
  user.username = "@]qsdqsdqsd";
  user.lastName = "wdqsd";
  user.addedToAttachmentMenu = false;
  user.isBot = true;
  std::cout <<user.toJson().dump(2) << std::endl;
}
