#include "easyjson.h"

namespace easyjson
{
    std::map<std::string, std::string> EasyJsonCPP::_configMap;
    std::shared_ptr<spdlog::logger> EasyJsonCPP::_logger = spdlog::stdout_color_mt("easyJson");

    EasyJsonCPP::EasyJsonCPP(const std::string &configFile)
        : _configFile(configFile)
    {
        _logger = spdlog::get("EasyJson");
        if (!_logger)
        {
            _logger = spdlog::stdout_color_mt("EasyJson");
        }

        // display library information
        showLibraryInfo();
    }

    /**
     * @brief Loads the JSON configuration file into the application.
     * This method checks if the configuration file path is set and non-empty. It then attempts to open the file,
     * read the JSON content, and parse it into the application's configuration structure. If the file is not found,
     * cannot be opened, or if its contents are not valid JSON, the method logs an appropriate error message and
     * throws a runtime exception. It also validates and processes the JSON content through 'validateConfigRoot'
     * and 'parseConfig' methods.
     */
    std::map<std::string, std::map<std::string, std::string>> EasyJsonCPP::loadConfiguration()
    {
        if (_configFile.empty())
        {
            const std::string &errorMsg = _configFile + ": file is empty";
            _logger->error(errorMsg);
            throw std::runtime_error(errorMsg);
        }

        try
        {
            _logger->debug("Loading configuration file: {}", _configFile);

            std::ifstream file(_configFile);

            if (!file.is_open())
            {
                std::string error_msg = "Could not open config file: " + _configFile;
                _logger->error(error_msg);
                throw std::runtime_error(error_msg);
            }

            Json::Value root;
            file >> root;

            // Validate the format of the root object.
            validateRootObject(root);
            return this->_mainMap;
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
    void EasyJsonCPP::validateRootObject(const Json::Value &root)
    {
        _logger->debug("Validating configuration file: {}.", this->_configFile);
        if (root.isArray())
        {
            parseArrayObjectData(root);
        }
        else if (root.isObject())
        {
        } // NOTE: Validate other possible formats of a json file here.
        else
        {
            throw std::runtime_error("Config file is not an array of Json objects.");
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
    void EasyJsonCPP::parseArrayObjectData(const Json::Value &rootObjects)
    {
        _logger->debug("Parsing configuration file: {}.", this->_configFile);

        for (const auto &object : rootObjects)
        {
            if (!object.isObject())
            {
                throw std::runtime_error("Invalid format for object in configuration file.");
            }

            for (const auto &member : object.getMemberNames())
            {
                const auto &key = object[member];

                if (key.isArray())
                {
                    this->parseArrayMemberData(member, key);
                }
                else if (key.isObject())
                {
                    this->parseObjectMemberData(member, key);
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
    void EasyJsonCPP::parseArrayMemberData(const std::string member, const Json::Value &arrayValue)
    {
        for (const auto &object : arrayValue)
        {
            if (!object.isObject())
            {
                throw std::runtime_error("Invalid format for object in configuration file.");
            }

            parseObjectMemberData(member, object);
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
    void EasyJsonCPP::parseObjectMemberData(const std::string &member, const Json::Value &objectValue)
    {

        for (const auto &key : objectValue.getMemberNames())
        {
            const auto &value = objectValue[key];
            processMemberData(member, key, value);
        }
    }

    /**
     * @brief Process and store a configuration value in the EasyJsonCPP multidimensional configuration map.
     *
     * This function is responsible for processing a key-value pair from a JSON configuration file.
     * It checks the type of the JSON value (string or integer) and stores it in the configuration map.
     * @param key The configuration key (string).
     * @param value The JSON value associated with the key.
     * @throws std::runtime_error if the JSON value is not a string or an integer.
     */
    void EasyJsonCPP::processMemberData(const std::string &member,
                                        const std::string &sectionName,
                                        const Json::Value &sectionValue)
    {
        if (sectionValue.isString() || sectionValue.isInt())
        {
            _mainMap[member][sectionName] = sectionValue.asString();
        }
        else
        {
            throw std::runtime_error("Invalid format for object value in configuration file.");
        }
    }

    /// @brief Read from the config file
    /// @param key[in] The key to read from the config file.
    /// @return The value of the key or an error string.
    const std::string &EasyJsonCPP::getFromConfigMap(const std::string &key,
                                                     const std::map<std::string, std::string> &configMap)
    {
        static std::string errorString;

        try
        {
            return configMap.at(key);
        }
        catch (const std::out_of_range &)
        {
            _logger->error("Error retrieving key: {} from config file.", key);
            static const std::string errorString = "Error retrieving " + key + " from config file";
            return errorString;
            throw std::runtime_error(errorString);
        }
        return errorString;
    }

    /// @brief Set the log level.
    /// @param level
    /// return none.
    void EasyJsonCPP::setLogLevel(const std::string &level)
    {
        spdlog::level::level_enum log_level;

        switch (hash(level.c_str()))
        {
        case hash("debug"):
            log_level = spdlog::level::debug;
            break;
        case hash("info"):
            log_level = spdlog::level::info;
            break;
        case hash("warn"):
            log_level = spdlog::level::warn;
            break;
        case hash("error"):
            log_level = spdlog::level::err;
            break;
        case hash("critical"):
            log_level = spdlog::level::critical;
            break;
        case hash("off"):
            log_level = spdlog::level::off;
            break;
        default:
            log_level = spdlog::level::debug;
            spdlog::debug("Invalid log level '{}'", level);
            return;
        }

        spdlog::set_level(log_level);
        _logger->info("Log level set to: {} \n", level);
    }

    /// @brief  Print a welcome message
    /// @param  none.
    /// @return none.
    void EasyJsonCPP::showLibraryInfo()
    {

        const std::map<std::string, std::string> infoDataMap = readInfoData();

        _logger->info("{} {}", getFromConfigMap("project", infoDataMap), getFromConfigMap("version", infoDataMap));
        _logger->info(getFromConfigMap("description", infoDataMap));
        _logger->info("Author: {}", getFromConfigMap("author", infoDataMap));
        setLogLevel(getFromConfigMap("mode", infoDataMap));

// Get the jsoncpp version, if available
#ifdef JSONCPP_VERSION_STRING
        _logger->debug("Using jsoncpp Version: {}.", JSONCPP_VERSION_STRING);
#else
        _logger->warn("Could not determine jsoncpp version.");
#endif

// Get the spdlog version, if available
#ifdef SPDLOG_VER_MAJOR
        _logger->debug("Using spdlog Version: {}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
#else
        _logger->warn("Could not determine spdlog version.");
#endif
    }

    // Function to read JSON data from infodata file
    std::map<std::string, std::string> EasyJsonCPP::readInfoData()
    {
        const std::string &filename = "infodata.json";

        std::ifstream file(filename);
        Json::Value root;
        Json::Reader reader;
        std::map<std::string, std::string> dataMap;

        // Read the file and parse JSON
        if (reader.parse(file, root))
        {
            const Json::Value &info = root["info"];

            // Iterate over the members of the "info" object and save them into the map
            for (const auto &key : info.getMemberNames())
            {
                dataMap[key] = info[key].asString();
            }
        }
        else
        {
            _logger->error("Failed to parse JSON from file: {}", filename);
            throw std::runtime_error("There was an error with the InfoData file");
        }

        return dataMap;
    }

} // ! EasyJson namespace