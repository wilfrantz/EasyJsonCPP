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

    /**
     * @brief Validates the root element of the loaded JSON configuration.
     *
     * This method checks whether the root element of the JSON configuration is an array.
     * It is a critical validation step to ensure that the configuration file adheres to
     * the expected format. If the root element is not an array, a runtime error is thrown,
     * indicating an invalid configuration format.
     *
     * @param root A reference to the Json::Value object representing the root element of the JSON configuration.
     * @throws std::runtime_error If the root element of the JSON configuration is not an array.
     */
    void EasyJsonCPP::validateConfigRoot(const Json::Value &root)
    {
        _logger->debug("Validating configuration file.");
        if (!root.isArray())
        {
            throw std::runtime_error("Config file is not an array.");
        }
    }

    /**
     * @brief Parses the JSON configuration file's root element.
     *
     * This method iterates through each object in the root JSON array, validating and parsing its contents.
     * It checks if each element in the root is an object and then processes each key-value pair within these objects.
     * The method handles different types of values: it processes target keys with specific actions, parses arrays and
     * objects recursively, and throws an error for invalid formats. This comprehensive parsing ensures the configuration
     * data is correctly interpreted and integrated into the application's settings.
     *
     * @param root A reference to the Json::Value object representing the root element of the JSON configuration.
     * @throws std::runtime_error If any element in the root array is not an object, or if the format of an object's value is invalid.
     */
    void EasyJsonCPP::parseConfig(const Json::Value &root)
    {
        _logger->debug("Parsing configuration file.");

        for (const auto &object : root)
        {
            if (!object.isObject())
            {
                throw std::runtime_error("Invalid format for object in configuration file.");
            }
            for (const auto &key : object.getMemberNames())
            {
                const auto &value = object[key];

                if (isTargetKey(key))
                {
                    processTargetKeys(value, key);
                }
                else if (value.isArray())
                {
                    parseArrayConfig(value);
                }
                else if (value.isObject())
                {
                    parseObjectConfig(value);
                }
                else
                {
                    throw std::runtime_error("Invalid format for object value in configuration file.");
                }
            }
        }
    }

    /**
     * @brief Parses each object within a JSON array from the configuration file.
     *
     * This method iterates through an array of JSON objects, ensuring each element in the array is indeed an object.
     * It then delegates the parsing of each individual object to the `parseObjectConfig` method. If any element
     * in the array is not a JSON object, a runtime error is thrown, signaling an invalid format in the configuration file.
     * This method is typically called when a JSON array is encountered during the configuration parsing process.
     *
     * @param arrayValue A reference to the Json::Value object representing the JSON array to be parsed.
     * @throws std::runtime_error If any element within the array is not a JSON object.
     */
    void EasyJsonCPP::parseArrayConfig(const Json::Value &arrayValue)
    {
        for (const auto &object : arrayValue)
        {
            if (!object.isObject())
            {
                throw std::runtime_error("Invalid format for object in configuration file.");
            }

            parseObjectConfig(object);
        }
    }

    /**
     * @brief Parses and processes each key-value pair within a JSON object from the configuration file.
     *
     * This method iterates over each member (key-value pair) of a JSON object. For every pair encountered,
     * it calls the `processConfigValue` method to handle the processing of each specific key and its associated value.
     * This approach allows for a modular and flexible handling of various configuration settings defined in the JSON object.
     * It is typically invoked for each object encountered in the JSON configuration, enabling granular processing of configuration data.
     *
     * @param objectValue A reference to the Json::Value object representing the JSON object to be parsed.
     */
    void EasyJsonCPP::parseObjectConfig(const Json::Value &objectValue)
    {
        for (const auto &key : objectValue.getMemberNames())
        {
            const auto &value = objectValue[key];
            processConfigValue(key, value);
        }
    }
}

#endif // EASYJSONCPP_H