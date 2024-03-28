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


        void displayMap(std::map<std::string, std::string> &configMap)
        {
            if (!configMap.empty())
            {

                // _logger->debug("Printing the map to stdout.");
                std::cout << "Printing the map to stdout." << std::endl;

                for (const auto &element : configMap)
                {
                    // _logger->debug(element.first + " : " + element.second);
                    std::cout << element.first << " : " << element.second << std::endl;
                }
            }
            else
            {
                std::cerr << "Map is empty" << std::endl;
                // _logger->error("Map is empty.");
                exit(EXIT_FAILURE);
            }
        }
        virtual bool supportsKey(const std::string &key) const = 0;
    };
}
namespace easyjson
{
    class EasyJsonCPP
    {
    public:
        EasyJsonCPP() = default;

        explicit EasyJsonCPP(const std::string &configFile);

        std::map<std::string, std::map<std::string, std::string>> loadConfiguration();
        void displayInfo();

        std::map<std::string, std::map<std::string, std::string>> _mainMap;
        static std::map<std::string, std::string> _configMap;

        void setLogLevel(const std::string &level);

        std::map<std::string, std::string> readInfoData();

        // Methods to parse the config Json file.
        void parseConfig(const Json::Value &root);
        bool isTargetKey(const std::string &key) const;
        void validateRoot(const Json::Value &root);
        void parseArrayConfig(const std::string member, const Json::Value &arrayValue);
        // void parseObjectConfig(const Json::Value &objectValue);
        void parseObjectConfig(const std::string &member, const Json::Value &objectValue);
        // void processConfigValue(const std::string &key, const Json::Value &value);
        void processConfigValue(const std::string &member, const std::string &key, const Json::Value &value);

        // void processTargetKeys(const Json::Value &configValue,
        //                                const std::string &key);

        // template <typename T>
        void processTargetKeys(const Json::Value &configValue,
                               const std::string &key);

        const std::string &getFromConfigMap(const std::string &key,
                                            const std::map<std::string,
                                                           std::string> &configMap = _configMap);

        template <typename T>
        void loadConfigMap(const std::string &element,
                           const std::string &value,
                           T &object)
        {
            /// NOTE: Dereference the std::unique_ptr to access the interface object
            (*object)._configMap[element] = value;

        }

        const std::vector<std::unique_ptr<keysupport::KeySupport>> _container;

        ~EasyJsonCPP() = default;

#ifdef UNIT_TEST
        friend class EasyJsonMock;
#endif
    private:
        std::string _configFile{};
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