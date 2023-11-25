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
        EasyJsonCPP() {}
        void loadConfig();

        // Methods to parse the configuration file.
        void parseConfig(const Json::Value &root);
        bool isTargetKey(const std::string &key) const;
        void validateConfigRoot(const Json::Value &root);
        void parseArrayConfig(const Json::Value &arrayValue);
        void parseObjectConfig(const Json::Value &objectValue);
        void processConfigValue(const std::string &key, const Json::Value &value);

    private:
        std::string _configFile;
        static std::shared_ptr<spdlog::logger> _logger;
    };

    /**
     * @brief Loads the JSON configuration file into the application.
     * This method checks if the configuration file path is set and non-empty. It then attempts to open the file,
     * read the JSON content, and parse it into the application's configuration structure. If the file is not found,
     * cannot be opened, or if its contents are not valid JSON, the method logs an appropriate error message and
     * throws a runtime exception. It also validates and processes the JSON content through 'validateConfigRoot'
     * and 'parseConfig' methods.
     */
    void EasyJsonCPP::loadConfig()
    {
        if (_configFile.empty())
        {
            _logger->error("Configuration file is empty.");
            throw std::runtime_error("Configuration file is empty.");
        }

        try
        {
            _logger->debug("Loading configuration file: {}.", _configFile);

            std::ifstream file(_configFile);

            if (!file.is_open())
            {
                throw std::runtime_error("Could not open config file: " + _configFile);
            }

            Json::Value root;
            file >> root;
            validateConfigRoot(root);
            parseConfig(root);
        }
        catch (const std::exception &e)
        {
            _logger->error("Error reading configuration file: {}", e.what());
            throw;
        }
    }
}

#endif // EASYJSONCPP_H