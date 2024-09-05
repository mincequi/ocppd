CPMAddPackage(
    NAME Catch2
    GITHUB_REPOSITORY catchorg/Catch2
    VERSION 3.7.0
    OPTIONS
        "CATCH_BUILD_TESTING OFF"
        "CATCH_INSTALL_DOCS OFF"
        "CATCH_INSTALL_HELPERS OFF"
)

# Ensure Catch2 is available
find_package(Catch2 3 REQUIRED)

# Add test executable
add_executable(OcppMessageParserTest
  OcppMessageParserTest.cpp
)

# Link Catch2 to the test executable
target_link_libraries(OcppMessageParserTest
PRIVATE
  ocpp
  Catch2::Catch2WithMain
)

# Enable testing
enable_testing()

# Register the test executable with CTest
add_test(NAME OcppMessageParserTest COMMAND OcppMessageParserTest)
