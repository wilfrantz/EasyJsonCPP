
#include "tester.h"

    namespace tester
{
    /// @brief Process the target keys in the config file
    /// @param configValue[in] The value of the target key
    /// @param key[in] The name of the target key
    /// @return none.
    void Tester::processTargetKeys(const Json::Value &configValue, const std::string &key)
    {
        _logger->debug("Processing target key: {}", key);
        if (configValue.isArray())
        {
            // implementation not needed for this tester.
        }
        else
        {
            // Invalid value type
            throw std::runtime_error("Invalid format for object value in the configuration file.");
        }
    }

    // Tester method to print the content of the nested map
    // void Tester::printNestedMap(const std::string &prefix = "")
    // void Tester::printNestedMap(const std::string &prefix = "")
    void Tester::displayMap()
    {
        if (!_configMapRef.empty())
        {

            _logger->debug("Printing the map to stdout.");

            for (const auto &element : _configMapRef)
            {
                _logger->debug(element.first + " : " + element.second);
            }
        }
        else
        {
            _logger->error("Map is empty.");
            exit(EXIT_FAILURE);
        }
    }
}