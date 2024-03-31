cmake_minimum_required(VERSION 3.15)
project(easyjson_tests LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Locate and include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add your test files here
set(TEST_SOURCES
    src/main.cpp
    src/UT_loadconfig.cpp
)

# Create an executable for tests
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link the test executable with GoogleTest
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${GTEST_BOTH_LIBRARIES}
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
