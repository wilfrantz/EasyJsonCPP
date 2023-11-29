/**
 * easyJsonCPP offers streamlined JSON configuration file integration for C++ applications.
 *
 * (C) 2023 Wilfrantz Dede
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, see https://github.com/easyJsonCPP/easyJsonCPP/blob/main/LICENSE.txt.
 *
 * Contact: EasyJsonCPP Developers <contact@dede.dev>
 *
 * File description:
 * The easyJsonCPP library is designed to simplify the integration and handling
 * of JSON configuration files in C++ projects. It provides a set of intuitive
 * functions for reading, writing, and managing JSON data seamlessly.
 **/

#ifndef EASYJSONCPP_H
#define EASYJSONCPP_H

#include "header.hpp"

namespace easyjson
{

    class EasyJsonCPP
    {
    public:
        explicit EasyJsonCPP(const std::string &confifFile = "easyJson_config.json",
                             const std::vector<std::string> target)
            : _configFile(confifFile), _targetKeys(target)
        {
            _logger = spdlog::get("EasyJson");
            if (!_logger)
            {
                _logger = spdlog::stdout_color_mt("EasyJson");
            }
        }

        void loadConfig(std::vector<std::string> targetKeys = {});

        // void setLogLevel(const std::string &level);

        // Methods to parse the configuration file.
        void parseConfig(const Json::Value &root);
        bool isTargetKey(const std::string &key) const;
        void validateConfigRoot(const Json::Value &root);
        void parseArrayConfig(const Json::Value &arrayValue);
        void parseObjectConfig(const Json::Value &objectValue);
        void processConfigValue(const std::string &key, const Json::Value &value);
        // void processTargetKeys(const Json::Value &configValue, const std::string &key);

    private:
        std::string _configFile;
        static std::shared_ptr<spdlog::logger> _logger;
        const std::vector<std::string> _targetKeys;
    };

}

#endif // EASYJSONCPP_H