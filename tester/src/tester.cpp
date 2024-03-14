
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
    void Tester::printNestedMap(const std::string &prefix = "")
    {
        for (const auto &element : _configMap)
        {
            std::cout << prefix << element.first << " :\n";
            for (const auto &innerElement : element.second)
            {
                std::cout << prefix << "\t" << innerElement.first << " : " << innerElement.second << std::endl;
            }
        }
    }

    // void Tester::printNestedMap(const std::string &prefix = "")
    // {
    //     for (const auto &pair : _configMap)
    //     {
    //         std::cout << prefix << pair.first << ": " << std::endl;

    //         for (const auto &innerPair : pair.second)
    //         {
    //             std::cout << prefix << "  " << innerPair.first << ": " << innerPair.second << std::endl;
    //         }
    //     }
    // }
}