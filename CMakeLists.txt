cmake_minimum_required(VERSION 3.10)
project(tgbotxx VERSION "1.0.6.9" DESCRIPTION "Telegram Bot C++ Library" LANGUAGES C CXX)
# Note: tgbotxx version's patch & build is based on Telegram Bot Api version for compatibility. See https://core.telegram.org/bots/api-changelog
# <OurMajorVersion>.<OurMinorVersion>.<TelegramBotApiMajorVersion>.<TelegramBotApiMinorVersion>

################# Options ###########################
option(ENABLE_TESTS "Enable/Disable building of tests" OFF)
#####################################################


################# Libraries ###########################
include(cmake/find_or_fetch.cmake)
# Find or download all dependencies

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
        nlohmann_json
        https://github.com/nlohmann/json
        GIT_TAG bc889afb4c5bf1c0d8ee29ef35eaaf4c8bef8a5d # The commit hash for 3.11.2. Replace with the latest from: https://github.com/nlohmann/json/releases
)
FetchContent_MakeAvailable(${remote_dependencies})
set(TGBOTXX_LIBRARIES cpr::cpr nlohmann_json::nlohmann_json)
######################################################


################# Main project ######################
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/**.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/tgbotxx/**.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS}) # TODO: build shared libs
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME}
                            PUBLIC
                            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${TGBOTXX_LIBRARIES})

###### Installation ######
# @note: This installation script should work on Linux, Windows and macOS as long as the paths specified by
# the CMake variables (CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR) are set correctly
# for those platforms. These variables are typically set by CMake to appropriate default values based on the platform.
include(GNUInstallDirs) # Use standard CMake directory variables
# Install the main target (executable, library, or archive)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
# Install header files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# Enable position-independent code for shared libraries
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
#######################################################

## Tests
if (ON)#ENABLE_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()
