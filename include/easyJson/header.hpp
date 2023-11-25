/**
 * @file HEADER.hpp
 * 
 * This header file contains the necessary includes and definitions for cross-platform
 * compatibility and functionality in a C++ project. It includes a variety of standard
 * and third-party libraries to support a range of functionalities such as file system
 * operations, logging, JSON parsing, and network communication.
 *
 * Key Features:
 * - Cross-Platform Support: Conditional compilation for Windows and Apple platforms to handle platform-specific includes.
 * - JSON Handling: Includes JSON parsing libraries, with variations for Apple and other platforms.
 * - File System and I/O: Standard file system and input/output operations.
 * - Networking: Curl library for network requests.
 * - Logging: spdlog library for efficient and flexible logging.
 * - Multithreading and Synchronization: Includes for threading, atomic operations, mutexes, and condition variables.
 * - Utility Libraries: Various standard libraries for data structures, string processing, and other utilities.
 *
 * Usage Notes:
 * - Ensure that all third-party libraries (like spdlog, jsoncpp, and curl) are properly installed and configured in your build environment.
 * - This header is designed for use in projects that require cross-platform capabilities and network communication.
 *
 * (C) 2023 Wilfrantz Dede
 */

#ifndef HEADER_HPP
#define HEADER_HPP

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#define F_OK 0
#define access _access
#endif // !_WIN32

#ifdef __APPLE__
#include <json/json.h>
#include <json/reader.h>

#else
#include <iostream>
#include <filesystem>
#include <curl/curl.h>
#include <bits/stdc++.h>

#include <spdlog/spdlog.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

#endif // !__APPLE__

#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <curl/curl.h>
#include <cstdlib>
#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#endif // !HEADER_HPP