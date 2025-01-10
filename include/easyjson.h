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

#include <unordered_map>
#include <header.h>

namespace easyjson
{
    class EasyJsonCPP
    {
    public:
        EasyJsonCPP() = default;

        explicit EasyJsonCPP(const std::string &configFile);

        // Initialization code for the EasyJsonCPP class.

        void showLibraryInfo();
        void setLogLevel(const std::string &level);
        std::unordered_map<std::string, std::string> readInfoData();
        std::unordered_map<std::string,
                           std::unordered_map<std::string, std::string>>
        loadConfiguration();

        // Methods to parse the Json configuration file.
        void validateRootObject(const Json::Value &root);
        void parseArrayObjectData(const Json::Value &root);
        void parseArrayMemberData(const std::string &member, const Json::Value &arrayValue);
        void parseObjectMemberData(const std::string &member, const Json::Value &objectValue);
        void processMemberData(const std::string &member, const std::string &key, const Json::Value &value);

        const std::string &getFromConfigMap(const std::string &key,
                                            const std::unordered_map<std::string,
                                                                     std::string> &configMap = _configMap);

        ~EasyJsonCPP() = default;

        /// NOTES: For integration testing purposes.
        void displayMap(const std::unordered_map<std::string, std::string> &configMap);
        void displayMap(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &configMap);

        static std::unordered_map<std::string, std::string> _configMap;
        std::unordered_map<std::string, 
        std::unordered_map<std::string, std::string>> _mainMap;
        bool isInitialized() const { return initialized; }

#ifdef UNIT_TEST
        friend class EasyJsonMock;
#endif
    private:
        bool initialized{true}; 
        std::string _configFile{};
        static std::shared_ptr<spdlog::logger> _logger;

        // NOTE: This function recursively calculates the hash value of a null-terminated string
        // using a simple algorithm: multiplying the current hash value by 31 and adding
        // the ASCII value of the current character.
        static constexpr std::size_t hash(const char *s, std::size_t h = 0)
        {
            return (*s == '\0') ? h : hash(s + 1, (h * 31) + static_cast<unsigned char>(*s));
        }
    };
} // ! EasyJson namespace

#endif // EASYJSONCPP_H