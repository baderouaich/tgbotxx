cmake_minimum_required(VERSION 3.10)
project(thread_pool_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(tgbotxx
  GIT_REPOSITORY "https://github.com/baderouaich/tgbotxx"
  GIT_TAG        "error_code"
)
FetchContent_MakeAvailable(tgbotxx)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC tgbotxx)