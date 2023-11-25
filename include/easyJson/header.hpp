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