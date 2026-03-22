file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

## Catch2
add_library(catch2 STATIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/catch2/src/catch.cpp)
target_include_directories(catch2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/catch2/include)

## CTest
foreach (source ${TEST_SOURCES})
    get_filename_component(filename ${source} NAME_WE)
    add_executable(${filename} ${source})
    add_test(${filename} ${filename}) # add target to CTest flow
    target_compile_features(${filename} PRIVATE cxx_std_20)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/catch2/include)
    # Link the tests with the main project tgbotxx
    target_link_libraries(${filename} PRIVATE catch2 tgbotxx)
    target_compile_options(${filename}
            PRIVATE # Fix ".obj file too big" issue in windows/mingw
            $<$<AND:$<CXX_COMPILER_ID:GNU>,$<PLATFORM_ID:Windows>>:-Wa,-mbig-obj>)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        # valgrind memory leak checks (NOTE: valgrind has problems with clang symbols, compile with gcc before running this target)
        add_custom_target(check_memory_leaks_${filename}
                COMMAND valgrind --tool=memcheck --leak-check=full -s --show-leak-kinds=all --track-origins=yes ${CMAKE_CURRENT_BINARY_DIR}/${filename}
                )
    endif ()
endforeach ()

## Manual Tests
add_executable(manual_tests manual_tests.cpp)
target_compile_features(manual_tests PRIVATE cxx_std_20)
target_link_libraries(manual_tests PRIVATE tgbotxx ${TGBOTXX_LIBRARIES})
#target_compile_definitions(manual_tests PRIVATE RES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/res")
if (NOT DEFINED ENV{TESTS_BOT_TOKEN})
    message(FATAL_ERROR "Missing ENV variable TESTS_BOT_TOKEN\nObtain a bot token form @BotFather and export TESTS_BOT_TOKEN=YOUR_TESTING_BOT_TOKEN")
endif()


if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # valgrind memory leak checks (NOTE: valgrind has problems with clang symbols, compile with gcc before running this target)
    add_custom_target(check_memory_leaks_manual_tests
            COMMAND valgrind --tool=memcheck --leak-check=full -s --show-leak-kinds=all --track-origins=yes ${CMAKE_CURRENT_BINARY_DIR}/manual_tests
            )
endif ()