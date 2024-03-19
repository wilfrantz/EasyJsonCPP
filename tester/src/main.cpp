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
using namespace keysupport;

int main()
{
    // Objects to move
    std::unique_ptr<KeySupport> twitterObjPtr = std::make_unique<Twitter>();
    std::unique_ptr<KeySupport> tiktokObjPtr = std::make_unique<Tiktok>();
    std::unique_ptr<KeySupport> instagramObjPtr = std::make_unique<Instagram>();
    std::unique_ptr<KeySupport> telegramObjPtr = std::make_unique<Telegram>();

    // Move objects into the vector
    std::vector<std::unique_ptr<KeySupport>> container;
    container.push_back(std::move(tiktokObjPtr));
    container.push_back(std::move(twitterObjPtr));
    container.push_back(std::move(instagramObjPtr));
    container.push_back(std::move(telegramObjPtr));

    // Targets list
    const std::vector<std::string> _targets = {"twitter", "tiktok",
                                               "instagram", "telegram"};

    // Create EasyJsonCPP object
    EasyJsonCPP loader("easy_config.json", _targets, std::move(container));
    loader.loadConfig();

    // Set the level of the tester class.
    loader.setLogLevel(loader.getFromConfigMap("mode"));

    // Display information using Tester class
    Tester test;
    test.displayInfo();
    test.displayMap(test._configMapRef);

    return EXIT_SUCCESS;
}
