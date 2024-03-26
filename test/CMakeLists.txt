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

# Link the test executable with easyjson library and GoogleTest
target_link_libraries(${PROJECT_NAME} PRIVATE
    easyjson
    ${GTEST_BOTH_LIBRARIES}
)

# Add compile definitions for tests if needed
# target_compile_definitions(${PROJECT_NAME}
#     PRIVATE SOME_DEFINE
# )

# Optionally, specify include directories for tests
# target_include_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

# Optionally, specify additional link directories for tests
# target_link_directories(${PROJECT_NAME} PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/lib
# )

# Add tests to CTest
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
