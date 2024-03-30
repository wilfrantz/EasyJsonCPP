/**
 * @file main.cpp
 *
 * This is the main tester file for the EasyJsonCPP library. It demonstrates the usage of the EasyJsonCPP
 * class for loading and parsing JSON configuration files. The program creates an instance of EasyJsonCPP
 * and calls the loadConfig method to process a JSON configuration file.
 *
 * The purpose of this tester is to validate the functionality of the EasyJsonCPP library and to provide a
 * basic example of how the library can be utilized in C++ applications. It is part of the testing suite
 * for EasyJsonCPP, ensuring that the library's core features perform as expected.
 *
 * Usage:
 *     ./tester
 *
 * Note: The path to the JSON configuration file is expected to be provided by the EasyJsonCPP object
 * or set within its implementation prior to calling loadConfig.
 *
 * @author: (C) 2023 Wilfrantz Dede
 */

#include "tester.h"

using namespace tester;
using namespace tiktok;
using namespace twitter;
using namespace easyjson;
using namespace telegram;
using namespace instagram;

int main()
{
    EasyJsonCPP loader("easy_config.json");
    Tester test;

    test._mainMap = loader.loadConfiguration();

    /// Set the log level for the tester.
    test.setLogLevel(test._mainMap["info"]["mode"]);

    /// Actual RunTime test.
    Twitter tweet(test._mainMap["twitter"]);
    test.displayMap(tweet._configMap);

    Tiktok tiktok(test._mainMap["tiktok"]);
    test.displayMap(tiktok._configMap);

    Instagram gram(test._mainMap["instagram"]);
    test.displayMap(gram._configMap);

    Telegram telegram(test._mainMap["telegram"]);
    test.displayMap(telegram._configMap);

    return EXIT_SUCCESS;
}
