cmake_minimum_required(VERSION 3.15)
project(earthquake_bot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(tgbotxx REQUIRED tgbotxx)

if(NOT tgbotxx_FOUND)
  message(FATAL_ERROR "Did you install tgbotxx locally?")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_LIBRARY_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${tgbotxx_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${tgbotxx_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PUBLIC  ${tgbotxx_LIBRARIES})
