#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <tgbotxx/tgbotxx.hpp>
using namespace tgbotxx;

TEST_CASE("StringUtils", "all functions") {
  SECTION("startsWith & endsWith") {
    std::string A = "Hello, world";
    SECTION("don't ignore case") {
      REQUIRE(StringUtils::startsWith(A, "Hello"));
      REQUIRE(StringUtils::endsWith(A, "world"));
    }
    SECTION("ignore case") {
      REQUIRE(StringUtils::startsWith(A, "Hello", true));
      REQUIRE(StringUtils::endsWith(A, "world", true));
    }
  }

  SECTION("replace & replaceCopy") {
    std::string A = "Hello, world";
    StringUtils::replace(A, "Hello", "world");
    REQUIRE(A == "world, world");
    std::string C = StringUtils::replaceCopy(A, "world", "Hello");
    REQUIRE(C == "Hello, Hello");
  }

  SECTION("split") {
    std::string str = "\"I Declare Bankruptcy!\". Michael Scott";
    auto parts = StringUtils::split(str, ' ');
    REQUIRE(parts.size() == 5);
    REQUIRE(parts[0] == "\"I");
    REQUIRE(parts[1] == "Declare");
    REQUIRE(parts[2] == "Bankruptcy!\".");
    REQUIRE(parts[3] == "Michael");
    REQUIRE(parts[4] == "Scott");
  }

  SECTION("join") {
    std::vector<int> ints = {1, 2, 3};
    std::array<int, 3> arr = {1, 2, 3};
    std::string str = StringUtils::join(std::span{ints}, ',');
    std::string str2 = StringUtils::join(ints, ',');
    REQUIRE(str == "1,2,3");
    REQUIRE(str2 == "1,2,3");

    std::string str3 = StringUtils::join(ints, "ok");
    REQUIRE(str3 == "1ok2ok3");

    std::string s = ",,,,,,";
    std::string r = StringUtils::join(std::span{s}, ',');
    std::string expected((s.size() * 2) - 1, ',');
    REQUIRE(r == expected);
  }
}

TEST_CASE("DateTimeUtils", "all functions") {
  SECTION("currentDateTime") {
    std::string nowStr = DateTimeUtils::now();
    Catch::cout() << nowStr << std::endl;
    REQUIRE(nowStr.find('-') != std::string::npos);
    REQUIRE(nowStr.find(':') != std::string::npos);

    std::string dateOnly = DateTimeUtils::now("%Y-%m-%d");
    Catch::cout() << dateOnly << std::endl;
    REQUIRE(dateOnly.find('-') != std::string::npos);

    std::string timeOnly = DateTimeUtils::now("%H:%M:%S");
    Catch::cout() << timeOnly << std::endl;
    REQUIRE(timeOnly.find(':') != std::string::npos);
  }

  SECTION("toString") {
    std::time_t now = std::time(nullptr);
    std::time_t oneHourFromNow = now + 3600;
    std::time_t oneHourBeforeNow = now - 3600;

    std::string nowStr = DateTimeUtils::toString(now);
    std::string oneHourFromNowStr = DateTimeUtils::toString(oneHourFromNow);
    std::string oneHourBeforeNowStr = DateTimeUtils::toString(oneHourBeforeNow);

    Catch::cout() << nowStr << std::endl;
    Catch::cout() << oneHourFromNowStr << std::endl;
    Catch::cout() << oneHourBeforeNowStr << std::endl;
  }
  SECTION("fromString") {
    {
      std::string str = "1970-01-01";
      std::time_t dt = DateTimeUtils::fromString(str, "%Y-%m-%d");
      std::string rec = DateTimeUtils::toString(dt, "%Y-%m-%d");
      Catch::cout() << dt << std::endl;
      Catch::cout() << rec << std::endl;
      REQUIRE(str == rec);
    }
    {
      std::string str = "2031/07/18 16:34:34";
      std::time_t dt = DateTimeUtils::fromString(str, "%Y/%m/%d %H:%M:%S");
      std::string rec = DateTimeUtils::toString(dt, "%Y/%m/%d %H:%M:%S");
      Catch::cout() << dt << std::endl;
      Catch::cout() << rec << std::endl;
      REQUIRE(str == rec);
    }
  }
}

TEST_CASE("Ptr", "all functions") {
  auto strPtr = makePtr<std::string>("Hello, World!");
  REQUIRE(strPtr);
  REQUIRE(*strPtr == "Hello, World!");
  strPtr.reset();
  REQUIRE(strPtr == nullptr);
}