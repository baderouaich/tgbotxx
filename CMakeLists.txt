cmake_minimum_required(VERSION 3.20)
project(tgbotxx VERSION "0.0.1" DESCRIPTION "Telegram Bot C++ Library" LANGUAGES CXX)

# Options
option(ENABLE_TESTS "Enable/Disable building of tests" OFF)

# Libraries
############## cURL cpr ##################
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/cpr)
include_directories(${CMAKE_SOURCE_DIR}/lib/cpr/include)
##########################################

########## nlohmann json single header ############
include_directories(${CMAKE_SOURCE_DIR}/lib/json/include)
###################################################

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/**.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/tgbotxx/**.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CPR_LIBRARIES} pthread)

## Tests
if (ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()
