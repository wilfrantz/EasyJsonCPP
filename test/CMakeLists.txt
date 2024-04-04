cmake_minimum_required(VERSION 3.15)
project(easyjson_tests LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Locate and include GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add fmt and jsoncpp libraries
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
# find_library(JSONCPP_LIBRARIES NAMES jsoncpp)
# find_library(EASYJSON_LIBRARY NAMES easyjson)

# Add your test files here
set(TEST_SOURCES
    src/main.cpp
    src/UT_easyJsonTest.cpp
)

# Create an executable for tests
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link the test executable with GoogleTest, fmt, and jsoncpp
# if(UNIX AND NOT APPLE)
#     target_link_libraries(${PROJECT_NAME} PRIVATE
#         jsoncpp
#         fmt::fmt
#         spdlog::spdlog
#     )
# elseif(APPLE)
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     ${GTEST_BOTH_LIBRARIES}
#     fmt::fmt
#     spdlog::spdlog
#     /usr/local/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib
# )
# endif()

# Link the test executable with GoogleTest, fmt, spdlog, and jsoncpp
target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    fmt::fmt
    spdlog::spdlog
    jsoncpp
    /usr/local/Cellar/easyjson/0.0.1/lib/libeasyjson.dylib
)

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
