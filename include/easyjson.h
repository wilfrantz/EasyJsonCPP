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

#include <header.h>

namespace easyjson
{
    class EasyJsonCPP
    {
    public:
        EasyJsonCPP() = default;

        explicit EasyJsonCPP(const std::string &configFile,
                             const std::vector<std::string> targets = {})
            : _configFile(configFile), _targetKeys(targets)
        {
            _logger = spdlog::get("EasyJson");
            if (!_logger)
            {
                _logger = spdlog::stdout_color_mt("EasyJson");
            }
        }

        // void loadConfig(std::vector<std::string> targetKeys);
        void loadConfig();
        // std::map<std::string, std::map<std::string, std::string>> _configMap;
        static std::map<std::string, std::string> _configMap;

        void setLogLevel(const std::string &level);

        // Methods to parse the config Json file.
        void parseConfig(const Json::Value &root);
        bool isTargetKey(const std::string &key) const;
        void validateConfigRoot(const Json::Value &root);
        void parseArrayConfig(const Json::Value &arrayValue);
        void parseObjectConfig(const Json::Value &objectValue);
        void processConfigValue(const std::string &key, const Json::Value &value);

        virtual void processTargetKeys(const Json::Value &configValue,
                                       const std::string &key);

        const std::string &getFromConfigMap(const std::string &key,
                                            const std::map<std::string,
                                                           std::string> &configMap = _configMap);

        ~EasyJsonCPP() = default;

    private:
        std::string _configFile;
        const std::vector<std::string> _targetKeys{"easyJson", "jsonLib"};
        static std::shared_ptr<spdlog::logger> _logger;

        static constexpr std::size_t hash(const char *s, std::size_t h = 0)
        {
            return (*s == '\0') ? h : hash(s + 1, (h * 31) + static_cast<unsigned char>(*s));
        }
    };
} // ! EasyJson namespace

#endif // EASYJSONCPP_H