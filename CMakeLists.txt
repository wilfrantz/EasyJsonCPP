cmake_minimum_required(VERSION 3.15)
project(easyjson VERSION 0.0.1 LANGUAGES CXX)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Find required packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_library(JSONCPP_LIBRARIES NAMES jsoncpp REQUIRED)

# Define the source files for the library
set(SOURCE_FILES
    src/easyjson.cpp
)

# Create the shared library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Create the static library
add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})

# Add compile definitions
target_compile_definitions(${PROJECT_NAME}
    PUBLIC ENGINE_VERSION="${PROJECT_VERSION}"
)

# Add compile definitions for the static library
target_compile_definitions(${PROJECT_NAME}_static
    PUBLIC ENGINE_VERSION="${PROJECT_VERSION}"
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Include directories for the static library
target_include_directories(${PROJECT_NAME}_static
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries based on the operating system for shared library
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

# Link libraries based on the operating system for static library
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME}_static PRIVATE
        jsoncpp
        fmt::fmt
        spdlog::spdlog
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME}_static PRIVATE
        fmt::fmt
        spdlog::spdlog
        /usr/local/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib
    )
endif()

# Set the build type to Debug if not explicitly set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Check if we are on macOS or Linux
if(APPLE)
    set(LIB_DESTINATION "/usr/local/Cellar/easyjson")
elseif(UNIX)
    set(LIB_DESTINATION "/usr/lib")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Install the shared library
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${LIB_DESTINATION}
)

# Install the static library
install(TARGETS ${PROJECT_NAME}_static
    ARCHIVE DESTINATION ${LIB_DESTINATION}
)

# Optionally, update the linker cache (ldconfig) on Linux
if(UNIX AND NOT APPLE)
    install(CODE "execute_process(COMMAND ldconfig)")
endif()

# # Optionally build and run tests
# option(BUILD_TESTS "Build tests" ON)
# if(BUILD_TESTS)
#     message(STATUS "Building tests ...")
#     enable_testing()
#     add_subdirectory(test)
#     add_test(NAME ${PROJECT_NAME}_tests COMMAND test/${PROJECT_NAME}_test)
# endif()