/**
 * @file tester.hpp
 * @brief Header file for the Tester class.
 *
 * This file contains the definition of the Tester class, which is used for
 *
 * The class provides // TODO
 *
 *
 * @author: (C) 2023 Wilfrantz Dede
 */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <easyjson.h>

// Interface for classes that support the key
namespace twitter
{
    class Twitter
    {
    public:
        Twitter(const std::map<std::string, std::string> &map) : _configMap(map) {}

        std::map<std::string, std::string> _configMap;
    };
}
namespace instagram
{
    class Instagram
    {
    public:
        Instagram(const std::map<std::string, std::string> &map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;
    };
}
namespace tiktok
{
    class Tiktok
    {
    public:
        Tiktok(const std::map<std::string, std::string> &map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;
    };
}
namespace telegram
{
    class Telegram
    {
    public:
        Telegram(const std::map<std::string, std::string> &map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;
    };
}

using namespace easyjson;
namespace tester
{
    class Tester final : public EasyJsonCPP
    {
    public:
        Tester(const std::map<std::string, std::map<std::string, std::string>> &configData)
            : _mainMap(configData)
        {
            _logger = spdlog::get("Tester");
            if (!_logger)
            {
                _logger = spdlog::stdout_color_mt("Tester");
            }
            // Load the infoMap with data.
            testerInfoMap = retrieve("info");
        };

        void displayInfo();

        void displayMap(const std::map<std::string, std::string> &configMap);
        void displayMap(const std::map<std::string, std::map<std::string, std::string>> &configMap);

        inline const std::map<std::string, std::string> retrieve(std::string key)
        {
            return _mainMap.at(key);
        }

        static std::shared_ptr<spdlog::logger> _logger;
        std::map<std::string, std::string> testerInfoMap;

    private:
        const std::map<std::string, std::map<std::string, std::string>> _mainMap;
    };
}

#endif // !TESTER_HPP