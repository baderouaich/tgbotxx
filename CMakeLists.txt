cmake_minimum_required(VERSION 3.10)
project(tgbotxx VERSION "1.0.6.9" DESCRIPTION "Telegram Bot C++ Library" LANGUAGES C CXX)
# Note: tgbotxx version's patch & build is based on Telegram Bot Api version for compatibility. See https://core.telegram.org/bots/api-changelog
# <OurMajorVersion>.<OurMinorVersion>.<TelegramBotApiMajorVersion>.<TelegramBotApiMinorVersion>


################# Options ###########################
option(ENABLE_TESTS "Enable/Disable building of tests" OFF)
option(BUILD_DOCS "Build doxygen API documentation" OFF)
option(BUILD_SHARED_LIBS "Build tgbotxx as a shared/static library." OFF)
#####################################################


################## Libraries ##########################
## libcpr curl
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


###### Installation ######
include(cmake/install.cmake)
############################


###### Doxygen Documentation ######
if(BUILD_DOCS)
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
endif()
###################################


###### Tests ######
if (ENABLE_TESTS)
    message(STATUS "Building tests is enabled")
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
####################
