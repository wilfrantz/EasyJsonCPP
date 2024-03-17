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

namespace twitter
{
    class Twitter
    {
        std::map<std::string, std::string> _configMap;

        inline bool supportsKey(std::string &key) const
        {
            return key == "twitter";
        }
    };
}
namespace instagram
{
    class Instagram
    {
        std::map<std::string, std::string> _configMap;

        inline bool supportsKey(std::string &key) const
        {
            return key == "instagram";
        }
    };
}
namespace tiktok
{
    class Tiktok
    {
        std::map<std::string, std::string> _configMap;

        inline bool supportsKey(std::string &key) const
        {
            return key == "tiktok";
        }
    };
}
namespace telegram
{
    class Telegram
    {
        std::map<std::string, std::string> _configMap;

        inline bool supportsKey(std::string &key) const
        {
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

        // void printNestedMap(const std::string &prefix);
        void
        displayInfo();
        void displayMap(std::map<std::string, std::string> &configMap);

        void processTargetKeys(const Json::Value &configValue, const std::string &key) override;

        std::map<std::string, std::string> &_configMapRef = EasyJsonCPP::_configMap;

    private:
        std::shared_ptr<spdlog::logger> _logger;
    };
}

#endif // !TESTER_HPP