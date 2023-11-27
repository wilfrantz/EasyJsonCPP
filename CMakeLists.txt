cmake_minimum_required(VERSION 3.10...3.20)
project(easyjson VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_library(JSONCPP_LIBRARIES NAMES jsoncpp)

OPTION(BUILD_TESTS "Build tests" ON)
OPTION(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

add_compile_definitions(ENGINE_VERSION="${PROJECT_VERSION}")

add_executable(${PROJECT_NAME}
  src/main.cpp
)

set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        jsoncpp
        fmt::fmt
        spdlog::spdlog
    )
else(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
    fmt::fmt
    spdlog::spdlog
    /usr/local/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib
    )
endif()

# if (BUILD_TESTS)
#   message(STATUS "Building tests ...")
#   enable_testing()
#   add_subdirectory(test)
#   add_test(NAME ${PROJECT_NAME}_tests COMMAND test/${PROJECT_NAME}_test)
# endif (BUILD_TESTS)
