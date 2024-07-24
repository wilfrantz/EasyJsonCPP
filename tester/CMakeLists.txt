cmake_minimum_required(VERSION 3.15)
project(easyjson_tester)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)

# Enable verbose Makefile if desired
option(CMAKE_VERBOSE_MAKEFILE "Verbose Makefile" ON)

# Find required packages
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_library(JSONCPP_LIBRARIES NAMES jsoncpp)
find_library(EASYJSON_LIBRARY NAMES easyjson)


# Add your executable
add_executable(${PROJECT_NAME}
    src/main.cpp 
    src/tester.cpp
)

# include directory
target_include_directories(${PROJECT_NAME} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries based on the operating system
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        jsoncpp
        fmt::fmt
        spdlog::spdlog
        /usr/local/lib/easyjson/0.0.1/lib/libeasyjson.so
    )
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        fmt::fmt
        spdlog::spdlog
        /usr/local/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib
        /usr/local/Cellar/easyjson/0.0.1/lib/libeasyjson.dylib
    )
endif()
