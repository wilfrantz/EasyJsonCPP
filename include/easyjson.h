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

namespace keysupport
{
    class KeySupport
    {
    public:
        virtual ~KeySupport() {}
        std::map<std::string, std::string> _configMap;
        virtual bool supportsKey(const std::string &key) const = 0;
    };
}
namespace easyjson
{
    class EasyJsonCPP
    {
    public:
        EasyJsonCPP() = default;

        explicit EasyJsonCPP(const std::string &configFile,
                             const std::vector<std::string> &targets,
                             std::vector<std::unique_ptr<keysupport::KeySupport>> &&container)
            : _configFile(configFile), _targetKeys(targets), _container(std::move(container))
        {
            _logger = spdlog::get("EasyJson");
            if (!_logger)
            {
                _logger = spdlog::stdout_color_mt("EasyJson");
            }

            // display library information
            displayInfo();
        }

        void loadConfig();
        void displayInfo();

        static std::map<std::string, std::string> _configMap;

        void setLogLevel(const std::string &level);

        std::map<std::string, std::string> readInfoData();

        // Methods to parse the config Json file.
        void parseConfig(const Json::Value &root);
        bool isTargetKey(const std::string &key) const;
        void validateConfigRoot(const Json::Value &root);
        void parseArrayConfig(const Json::Value &arrayValue);
        void parseObjectConfig(const Json::Value &objectValue);
        void processConfigValue(const std::string &key, const Json::Value &value);

        virtual void processTargetKeys(const Json::Value &configValue,
                                       const std::string &key);

        template <typename T>
        void processTargetKeys(const Json::Value &configValue,
                               const std::string &key, const T &object);

        const std::string &getFromConfigMap(const std::string &key,
                                            const std::map<std::string,
                                                           std::string> &configMap = _configMap);

        template <typename T>
        void loadConfigMap(const std::string &key,
                           const std::string &value,
                           T &object)
        {
            // _logger->info("Loading the {} map", key);
            /// NOTE: Dereference the std::unique_ptr to access the KeySupport (interface) object
            (*object)._configMap[key] = value;

            if ((*object)._configMap.empty())
                _logger->debug("Map is empty.");
            else
                _logger->debug("Map is not empty");
        }

        const std::vector<std::unique_ptr<keysupport::KeySupport>> _container;

        ~EasyJsonCPP() = default;

#ifdef UNIT_TEST
        friend class EasyJsonMock;
#endif
    private:
        std::string _configFile;
        const std::string VERSION = "0.0.1";
        static std::shared_ptr<spdlog::logger> _logger;
        std::vector<std::string> _targetKeys{};

        // This function recursively calculates the hash value of a null-terminated string
        // using a simple algorithm: multiplying the current hash value by 31 and adding
        // the ASCII value of the current character.
        static constexpr std::size_t hash(const char *s, std::size_t h = 0)
        {
            return (*s == '\0') ? h : hash(s + 1, (h * 31) + static_cast<unsigned char>(*s));
        }
    };
} // ! EasyJson namespace

#endif // EASYJSONCPP_H