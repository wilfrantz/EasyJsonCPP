#include "tester.h"

namespace tester
{
        std::shared_ptr<spdlog::logger> Tester::_logger = spdlog::stdout_color_mt("Tester");

        Tester::Tester(const std::unordered_map<std::string,
                                                std::unordered_map<std::string, std::string>> &configData)
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

        // Print a welcome message
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

} // !namespace tester