
#include "tester.h"

namespace tester
{
        std::shared_ptr<spdlog::logger> Tester::_logger = spdlog::stdout_color_mt("Tester");

        Tester::Tester(const std::map<std::string, std::map<std::string, std::string>> &configData)
            : _mainMap(configData)
        {
                _logger = spdlog::get("Tester");
                if (!_logger)
                {
                        _logger = spdlog::stdout_color_mt("Tester");
                }
                // Load the infoMap with data.
                testerInfoMap = retrieve("info");
                /// Set log level for the tester.
                setLogLevel(testerInfoMap["mode"]);
        };

        // Tester method to print the content of the nested map
        // void Tester::printNestedMap(const std::string &prefix = "")
        // void Tester::printNestedMap(const std::string &prefix = "")
        void Tester::displayMap(const std::map<std::string, std::string> &configMap)
        {
                if (!configMap.empty())
                {
                        for (const auto &element : configMap)
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

        void Tester::displayMap(const std::map<std::string, std::map<std::string, std::string>> &configMap)
        {
                if (configMap.empty())
                {
                        _logger->error("Map is empty.");
                        throw std::runtime_error("Map is empty");
                }

                for (const auto &outPair : configMap)
                {
                        for (const auto &innerPair : outPair.second)
                        {
                                _logger->debug(innerPair.first + " : " + innerPair.second);
                        }
                }
        }

        /// @brief  Print a welcome message
        /// @param  none.
        /// @return none.
        void Tester::displayInfo()
        {
                _logger->info("Welcome to {}", getFromConfigMap("project", this->_configMap));
                _logger->info("{}", getFromConfigMap("description", this->_configMap));
                _logger->info("Log level set to: {}", getFromConfigMap("mode", this->_configMap));

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

                // Display the configuration file in debug mode.
                for (const auto &element : this->_configMap)
                {
                        _logger->debug("{} : {}", element.first, element.second);
                }
        }

}