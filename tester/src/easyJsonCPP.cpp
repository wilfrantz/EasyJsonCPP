#include "include/easyJsonCPP.hpp"

namespace easyjson
{

    /**
     * @brief Loads the JSON configuration file into the application.
     * This method checks if the configuration file path is set and non-empty. It then attempts to open the file,
     * read the JSON content, and parse it into the application's configuration structure. If the file is not found,
     * cannot be opened, or if its contents are not valid JSON, the method logs an appropriate error message and
     * throws a runtime exception. It also validates and processes the JSON content through 'validateConfigRoot'
     * and 'parseConfig' methods.
     */
    // void EasyJsonCPP::loadConfig();
    void EasyJsonCPP::loadConfig(std::vector<std::string> targetKeys = {})
    {
        if (_configFile.empty())
        {
            const std::string &error_msg = "Configuration file path is empty.";
            _logger->error(error_msg);
            throw std::runtime_error(error_msg);
        }

        std::ifstream file(_configFile);
        if (!file)
        {
            std::string error_msg = "Could not open config file: " + _configFile;
            _logger->error(error_msg);
            throw std::runtime_error(error_msg);
        }

        _logger->debug("Loading configuration file: {}", _configFile);

        try
        {
            Json::Value root;
            file >> root;
            if (file.fail())
            {
                std::string error_msg = "Failed to parse JSON from file: " + _configFile;
                _logger->error(error_msg);
                throw std::runtime_error(error_msg);
            }

            validateConfigRoot(root);
            parseConfig(root);
        }
        catch (const std::exception &e)
        {
            std::string error_msg = "Error processing configuration file: " + std::string(e.what());
            _logger->error(error_msg);
            throw std::runtime_error(error_msg);
        }
    }

    /**
     * @brief Validates the root element of the loaded JSON configuration.
     * This method checks whether the root element of the JSON configuration is an array.
     * It is a critical validation step to ensure that the configuration file adheres to
     * the expected format. If the root element is not an array, a runtime error is thrown,
     * indicating an invalid configuration format.
     * @param root A reference to the Json::Value object representing the root element of the JSON configuration.
     * @throws std::runtime_error If the root element of the JSON configuration is not an array.
     */
    void EasyJsonCPP::validateConfigRoot(const Json::Value &root)
    {
        _logger->debug("Validating configuration file.");
        if (!root.isArray())
        {
            throw std::runtime_error("Config file is not an array of Json object.");
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
     * @brief Checks if the provided key is a target key.
     *
     * This method determines if a given key is part of the predefined set of target keys. It searches
     * through the '_targetKeys' container to see if the specified key exists. This is useful for identifying
     * keys that require special processing or handling within the JSON configuration.
     *
     * @param key A string representing the key to be checked against the set of target keys.
     * @return bool Returns true if the key is a target key, false otherwise.
     */
    bool EasyJsonCPP::isTargetKey(const std::string &key) const
    {
        return std::find(_targetKeys.begin(), _targetKeys.end(), key) != _targetKeys.end();
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


    /**
     * @brief Process and store a configuration value in the EasyJsonCPP configuration map.
     *
     * This function is responsible for processing a key-value pair from a JSON configuration file.
     * It checks the type of the JSON value (string or integer) and stores it in the configuration map.
     *
     * @param key The configuration key (string).
     * @param value The JSON value associated with the key.
     *
     * @throws std::runtime_error if the JSON value is not a string or an integer.
     */
    void EasyJsonCPP::processConfigValue(const std::string &key, const Json::Value &value)
    {
        if (value.isString())
        {
            _configMap.emplace(key, value.asString());
        }
        else if (value.isInt())
        {
            _configMap.emplace(key, std::to_string(value.asInt()));
        }
        else
        {
            throw std::runtime_error("Invalid format for object value in configuration file.");
        }
    }
}