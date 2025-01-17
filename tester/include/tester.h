/**
 * @file tester.hpp
 * @brief Header file for the Tester class.
 *
 * This file contains the definition of the Tester class, which is used to test the EasyJsonCPP library.
 * It also contains the definitions of the Twitter, Instagram, Tiktok, and Telegram classes, which are used
 * to test the EasyJsonCPP library.
 *
 * @author: (C) 2023 Wilfrantz Dede
 */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <easyjson.h>

// Interface for classes that support the key

using namespace easyjson;
namespace tester
{
    class Tester final : public EasyJsonCPP
    {
    public:
        Tester(const std::unordered_map<std::string, std::unordered_map<std::string,
                                                                        std::string>> &configData);

        inline const std::unordered_map<std::string, std::string> retrieve(std::string key)
        {
            return _mainMap.at(key);
        }

        void displayInfo();
        static std::shared_ptr<spdlog::logger> _logger;
        std::unordered_map<std::string, std::string> testerInfoMap;

    private:
        const std::unordered_map<std::string,
                                 std::unordered_map<std::string,
                                                    std::string>>
            _mainMap;

        std::unordered_map<std::string, std::string> _configMap; 
    };
}
namespace twitter
{
    class Twitter
    {
    public:
        Twitter(const std::unordered_map<std::string, std::string> &map) : _configMap(map) {}

        std::unordered_map<std::string, std::string> _configMap;
    };
}
namespace instagram
{
    class Instagram
    {
    public:
        Instagram(const std::unordered_map<std::string, std::string> &map) : _configMap(map) {}
        std::unordered_map<std::string, std::string> _configMap;
    };
}
namespace tiktok
{
    class Tiktok
    {
    public:
        Tiktok(const std::unordered_map<std::string, std::string> &map) : _configMap(map) {}
        std::unordered_map<std::string, std::string> _configMap;
    };
}
namespace telegram
{
    class Telegram
    {
    public:
        Telegram(const std::unordered_map<std::string, std::string> &map) : _configMap(map) {}
        std::unordered_map<std::string, std::string> _configMap;
    };
}

#endif // !TESTER_HPP