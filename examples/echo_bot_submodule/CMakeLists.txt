cmake_minimum_required(VERSION 3.10)
project(echo_bot_submodule)

add_subdirectory(lib/tgbotxx) # <-- clone tgbotxx in your lib/ directory
include_directories(lib/tgbotxx/include) # <-- include tgbotxx/ headers

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx) # <-- link to tgbotxx