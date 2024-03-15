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
        void displayMap();
        void displayInfo();
        const std::vector<std::string> _targetKeys = {"twitter", "tiktok", "instagram", "facebook"};

        void processTargetKeys(const Json::Value &configValue, const std::string &key) override;

        std::map<std::string, std::string> &_configMapRef = EasyJsonCPP::_configMap;

    private:
        std::shared_ptr<spdlog::logger> _logger;
    };
}

#endif // !TESTER_HPP