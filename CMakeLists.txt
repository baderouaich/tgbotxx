cmake_minimum_required(VERSION 3.20)
project(tgbotxx VERSION "1.2.9.2" DESCRIPTION "Telegram Bot C++ Library" LANGUAGES C CXX)
# Note: tgbotxx version's patch & build is based on Telegram Bot Api version for compatibility. See https://core.telegram.org/bots/api-changelog
# <OurMajorVersion>.<OurMinorVersion>.<TelegramBotApiMajorVersion>.<TelegramBotApiMinorVersion>

################# Options ###########################
option(ENABLE_TESTS "Enable/Disable building of tests" OFF)
option(BUILD_DOCS "Build doxygen API documentation" OFF)
option(BUILD_SHARED_LIBS "Build tgbotxx as a shared/static library." OFF)
#####################################################


################## Libraries ##########################
## libcpr curl
#set(USE_LIBIDN2 OFF CACHE BOOL "Curl option - Use libidn2 for IDN support" FORCE)
#set(CURL_USE_LIBPSL OFF CACHE BOOL "Curl option - Use libpsl" FORCE)
#set(BUILD_CURL_EXE OFF CACHE BOOL "Curl option - Build curl executable" FORCE)
set(CPR_CURL_USE_LIBPSL OFF CACHE BOOL "Since curl 8.13 curl depends on libpsl (https://everything.curl.dev/build/deps.html#libpsl). By default cpr keeps this as a secure default enabled wich in turn requires meson as build dependency. If set to OFF, psl support inside curl will be disabled." FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/cpr)
######################################################


################# Main project ######################
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/tgbotxx/**.hpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS}) # Todo: allow building tgbotxx as a shared library
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/json/include> # nlohmann json (single include)
        ${CPR_INCLUDE_DIRS}                                             # libcpr includes
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CPR_LIBRARIES})
target_compile_definitions(${PROJECT_NAME} PUBLIC
        TGBOTXX_VERSION="${PROJECT_VERSION}"
        TGBOTXX_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
        TGBOTXX_VERSION_MINOR=${PROJECT_VERSION_MINOR}
        TGBOTXX_VERSION_PATCH=${PROJECT_VERSION_PATCH}
        TGBOTXX_VERSION_TWEAK=${PROJECT_VERSION_TWEAK}
)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wno-unused-function -Wno-unused-parameter)
elseif (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /wd4100 /wd4505)
endif()
###### Installation ######
include(cmake/install.cmake)
############################


###### Doxygen Documentation ######
if (BUILD_DOCS)
    message(STATUS "Building Doxygen docs is enabled")
    find_package(Doxygen REQUIRED)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    add_custom_target(build_docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating Doxygen API documentation..."
            VERBATIM
            )
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/html/ TYPE DOC)
endif ()
###################################


###### Tests ######
if (ENABLE_TESTS)
    message(STATUS "Building tests is enabled")
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif ()
####################
