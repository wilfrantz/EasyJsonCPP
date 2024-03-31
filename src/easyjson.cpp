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

        // Show library information
        showLibraryInfo();
    }

    /** @brief
     * Loads the configuration from the specified configuration file.
     * It first checks if the configuration file path is empty.
     * If it's not empty, it attempts to open the file and parse its contents into a JSON object.
     * It then validates the format of the root object using validateRootObject().
     * If successful, it returns the main map containing the parsed configuration data.
     * If any error occurs during the process, it logs an error message and throws a runtime_error.
     *
     * @return A map containing the parsed configuration data.
     * @throw std::runtime_error If there's an error processing the configuration file.
     */
    std::map<std::string, std::map<std::string, std::string>> EasyJsonCPP::loadConfiguration()
    {
        // Check if the configuration file path is empty
        if (_configFile.empty())
        {
            const std::string &errorMsg = _configFile + ": file is empty";
            _logger->error(errorMsg);
            throw std::runtime_error(errorMsg);
        }

        try
        {
            _logger->debug("Loading configuration file: {}", _configFile);

            // Open the configuration file
            std::ifstream file(_configFile);
            if (!file.is_open())
            {
                std::string error_msg = "Could not open config file: " + _configFile;
                _logger->error(error_msg);
                throw std::runtime_error(error_msg);
            }

            // Parse the JSON data
            Json::Value root;
            file >> root;

            // Validate the format of the root object and invoke the appropriate parsing method
            validateRootObject(root);

            // Return the map to the caller.
            return this->_mainMap;
        }
        catch (const std::exception &e)
        {
            std::string error_msg = "Error processing configuration file: " + std::string(e.what());
            _logger->error(error_msg);
            throw std::runtime_error(error_msg);
        }
    }

    /** @brief
     * Validates the root object of the configuration file.
     * It checks whether the root is an array or an object.
     * If it's an array, it calls parseArrayObjectData() to parse it.
     * If it's an object, it may perform additional validation or processing in the future.
     * If it's neither an array nor an object, it throws a runtime_error.
     *
     * @param root The root JSON value of the configuration file.
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

    /** @brief
     * Parses an array of objects from the configuration file rootObjects.
     * It iterates over each object in the array, verifying that each is indeed an object.
     * For each object, it iterates over its members and checks whether each member's value is an array or object.
     * If it's an array, it calls parseArrayMemberData() to process it.
     * If it's an object, it calls parseObjectMemberData() to process it.
     * If the value is neither an array nor an object, it throws a runtime_error.
     *
     * @param rootObjects The JSON array of objects to be parsed.
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

    /** @brief
     * Parses data for a member of type array in the configuration file.
     * It iterates over the elements of the arrayValue, each of which should be an object.
     * If any element is not an object, it throws a runtime_error.
     * For each object element, it calls parseObjectMemberData() to process the object.
     *
     * @param member The member name under which the data will be stored.
     * @param arrayValue The JSON array containing objects to be parsed.
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

    /** @brief
     * Parses data for a member of type object in the configuration file.
     * It iterates over the keys and values of the objectValue,
     * calling `processMemberData()` for each key-value pair.
     * @param member The member name under which the data will be stored.
     * @param objectValue The JSON object containing key-value pairs to be parsed.
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
     *  @brief data for a member in the configuration file.
     * If the section value is a string or an integer, it stores it in the main map
     *  under the given member and section name.
     * If the section value is neither a string nor an integer, it throws a runtime_error.
     * @param member The member name under which the data will be stored.
     * @param sectionName The name of the section within the member.
     * @param sectionValue The value associated with the section.
     */
    void EasyJsonCPP::processMemberData(const std::string &member,
                                        const std::string &sectionName,
                                        const Json::Value &sectionValue)
    {
        if (sectionValue.isString() || sectionValue.isInt())
        {
            this->_mainMap[member][sectionName] = sectionValue.asString();
        }
        else
        {
            throw std::runtime_error("Invalid format for object value in configuration file.");
        }
    }

    /**
     * Retrieves the value associated with the provided key from the given configuration map.
     * If the key is found, returns a reference to the corresponding value.
     * If the key is not found, logs an error message and returns a reference to a static error string.
     *
     * @param key The key whose associated value is to be retrieved.
     * @param configMap The configuration map to search for the key.
     * @return A reference to the value associated with the key if found, otherwise a reference to a static error string.
     */
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

    /** @brief
     * Sets the log level of the application based on the provided level string.
     * Valid log levels include 'debug', 'info', 'warn', 'error', 'critical', and 'off'.
     * If an invalid log level is provided, it defaults to 'debug' and logs a warning message.
     *
     * @param level The log level to set.
     */

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

    /** @brief:
     * Shows information about the library including project name, version, description, author, and log level.
     * Also reads information data from a JSON file and sets the log level based on the mode specified in the data.
     * Additionally, it logs the versions of jsoncpp and spdlog if available.
     * @return none.
     */
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

    /** @brief Reads information data from a JSON file named "infodata.json"
     * returns a map of string key-value pairs.
     * Each key-value pair corresponds to a member in the "info" object within the JSON file.
     * If the file cannot be parsed or an error occurs, it throws a runtime_error.
     *
     * @return A map containing information data read from the JSON file.
     */

    std::map<std::string, std::string> EasyJsonCPP::readInfoData()
    {
        const std::string &filename = "metadata.json";

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