# @note: This installation script should work on Linux, Windows and macOS as long as the paths specified by
# the CMake variables (CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR) are set correctly
# for those platforms. These variables are typically set by CMake to appropriate default values based on the platform.
include(GNUInstallDirs) # Use standard CMake directory variables

# Install header files (our headers & lib single headers)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/tgbotxx DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/json/include/nlohmann DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Enable position-independent code for shared libraries
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

# Define export set and associate it with the targets we want to export (cpr)
install(TARGETS tgbotxx cpr
        EXPORT tgbotxx-targets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the library interface & target
install(EXPORT tgbotxx-targets
        NAMESPACE tgbotxx::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tgbotxx
        )

# Create and install the version file
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/tgbotxx-config-version.cmake"
        VERSION ${tgbotxx_VERSION}
        COMPATIBILITY AnyNewerVersion # SameMajorVersion
        )
install(
        FILES
        ${CMAKE_SOURCE_DIR}/cmake/tgbotxx-config.cmake
        ${PROJECT_BINARY_DIR}/tgbotxx-config-version.cmake
        DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/tgbotxx
)

# Install pkg-config file
configure_file(${PROJECT_SOURCE_DIR}/tgbotxx.pc.in ${CMAKE_BINARY_DIR}/tgbotxx.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/tgbotxx.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)
