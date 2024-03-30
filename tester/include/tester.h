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
    class Twitter : public keysupport::KeySupport
    {
    public:
        Twitter(std::map<std::string, std::string> map) : _configMap(map) {}

        std::map<std::string, std::string> _configMap;

        bool supportsKey(const std::string &key) const override
        {
            return key == "twitter";
        }
    };
}
namespace instagram
{
    class Instagram : public keysupport::KeySupport
    {
    public:
        Instagram(const std::map<std::string, std::string> &map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;

        bool supportsKey(const std::string &key) const override
        {
            return key == "instagram";
        }
    };
}
namespace tiktok
{
    class Tiktok : public keysupport::KeySupport
    {
    public:
        Tiktok(const std::map<std::string, std::string> &map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;

        bool supportsKey(const std::string &key) const override
        {
            return key == "tiktok";
        }
    };
}
namespace telegram
{
    class Telegram : public keysupport::KeySupport
    {
    public:
        Telegram(std::map<std::string, std::string> map) : _configMap(map) {}
        std::map<std::string, std::string> _configMap;

        bool supportsKey(const std::string &key) const
        {
        std:;
            return key == "telegram";
        }
    };
}

using namespace easyjson;
namespace tester
{
    class Tester final : public EasyJsonCPP
    {
    public:
        Tester()
        {
            _logger = spdlog::get("Tester");
            if (!_logger)
            {
                _logger = spdlog::stdout_color_mt("Tester");
            }
        };

        void displayInfo();

        void displayMap(const std::map<std::string, std::string> &configMap);
        void displayMap(const std::map<std::string, std::map<std::string, std::string>> &configMap);

        void processTargetKeys(const Json::Value &configValue, const std::string &key);

        std::map<std::string, std::map<std::string, std::string>> _mainMap;

        static std::shared_ptr<spdlog::logger> _logger;

    private:
    };
}

#endif // !TESTER_HPP