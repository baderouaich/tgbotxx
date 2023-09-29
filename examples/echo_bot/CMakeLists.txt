cmake_minimum_required(VERSION 3.10)
project(echo_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(tgbotxx REQUIRED)
if(NOT tgbotxx_FOUND)
  message(FATAL_ERROR "Did you install tgbotxx locally?")
endif()

add_executable(echo_bot main.cpp)

target_link_libraries(echo_bot PUBLIC 
  tgbotxx
  cpr::cpr
  nlohmann_json::nlohmann_json
)

