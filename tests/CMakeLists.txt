
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
foreach(source ${TEST_SOURCES})
    get_filename_component(filename ${source} NAME_WE)
    add_executable(${filename} ${source})
    target_compile_features(${filename} PRIVATE cxx_std_20)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/catch2/include)
    include_directories(${CPR_INCLUDE_DIRS})
     # Link the tests with the main project tgbotxx
    target_link_libraries(${filename} PRIVATE tgbotxx ${TGBOTXX_LIBRARIES})
    # valgrind memory leak checks (NOTE: valgrind has problems with clang symbols, compile with gcc before running this target)
    add_custom_target(check_memory_leaks_${filename}
            COMMAND valgrind --tool=memcheck --leak-check=full -s --show-leak-kinds=all ${CMAKE_CURRENT_BINARY_DIR}/${filename}
    )
endforeach()


## Manual Tests
add_executable(manual_tests manual_tests.cpp)
target_compile_features(manual_tests PRIVATE cxx_std_20)
target_link_libraries(manual_tests PRIVATE tgbotxx ${TGBOTXX_LIBRARIES})

# valgrind memory leak checks (NOTE: valgrind has problems with clang symbols, compile with gcc before running this target)
add_custom_target(check_memory_leaks_manual_tests
    COMMAND valgrind --tool=memcheck --leak-check=full -s --show-leak-kinds=all ${CMAKE_CURRENT_BINARY_DIR}/manual_tests
)