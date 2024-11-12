cmake_minimum_required(VERSION 3.15)
project(easyjson_tests LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Check for OS and set the correct architecture
if (APPLE)
    if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
endif()

# Locate and include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add fmt, spdlog, and jsoncpp libraries
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_library(JSONCPP_LIBRARIES NAMES jsoncpp)
find_library(EASYJSON_LIBRARY NAMES easyjson)
# find_package(jsoncpp REQUIRED)

# Add your test files here
set(TEST_SOURCES
    src/main.cpp
    src/UT_easyJsonTest.cpp
)

# Create an executable for tests
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link the test executable with GoogleTest, fmt, spdlog, and jsoncpp
target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    fmt::fmt
    spdlog::spdlog
    /usr/local/Cellar/easyjson/0.0.1/lib/libeasyjson.dylib
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
