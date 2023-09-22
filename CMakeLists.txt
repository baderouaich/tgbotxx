cmake_minimum_required(VERSION 3.5)
project(tgbotxx VERSION "0.0.1" DESCRIPTION "Telegram Bot C++ Library" LANGUAGES CXX)

# Options
option(ENABLE_TESTS "Enable/Disable building of tests" OFF)

############## Libraries ###########################
include(cmake/find_or_fetch.cmake)

## cURL cpr
# Find the cpr library, or download it in build/_deps
find_or_fetch(
        cpr
        https://github.com/libcpr/cpr.git
        31251f2b726fb954b0f2503ef3e1b72bfa773e50 # The commit hash for 1.10.4. Replace with the latest from: https://github.com/libcpr/cpr/releases
)
# nlohmann json
# Find the nlohmann json library, or download it in build/_deps
find_or_fetch(
        json
        https://github.com/nlohmann/json
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d # The commit hash for 3.11.2. Replace with the latest from: https://github.com/nlohmann/json/releases
)
FetchContent_MakeAvailable(${remote_dependencies})
set(TGBOTXX_LIBRARIES cpr::cpr nlohmann_json::nlohmann_json)
###################################################

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/**.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/tgbotxx/**.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PRIVATE ${TGBOTXX_LIBRARIES})

## Tests
if (ON) #(ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()
