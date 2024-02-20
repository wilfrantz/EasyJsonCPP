cmake_minimum_required(VERSION 3.15)
project(easyjson VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Find required packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_library(JSONCPP_LIBRARIES NAMES jsoncpp)

# Option to build tests
option(BUILD_TESTS "Build tests" OFF)

# Add compile definitions
add_compile_definitions(ENGINE_VERSION="${PROJECT_VERSION}")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) # Adjust include directory as needed

# Define the source files for the executable
set(SOURCE_FILES
    src/easyJsonCPP.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set the build type to Debug if not explicitly set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Link libraries based on the operating system
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        jsoncpp
        fmt::fmt
        spdlog::spdlog
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        fmt::fmt
        spdlog::spdlog
        /usr/local/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib
    )
endif()

# Optionally build and run tests
# if(BUILD_TESTS)
#     message(STATUS "Building tests ...")
#     enable_testing()
#     add_subdirectory(test)
#     add_test(NAME ${PROJECT_NAME}_tests COMMAND test/${PROJECT_NAME}_test)
# endif()
