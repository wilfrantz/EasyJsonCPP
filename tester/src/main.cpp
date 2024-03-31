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
    Tester test(loader.loadConfiguration());

    /// Set the log level for the tester.
    test.setLogLevel(test.testerInfoMap["mode"]);

    /// RunTime test.
    Twitter tweet(test.retrieve("twitter"));
    test.displayMap(tweet._configMap);

    Tiktok tiktok(test.retrieve("tiktok"));
    test.displayMap(tiktok._configMap);

    Instagram gram(test.retrieve("instagram"));
    test.displayMap(gram._configMap);

    Telegram telegram(test.retrieve("telegram"));
    test.displayMap(telegram._configMap);

    return EXIT_SUCCESS;
}
