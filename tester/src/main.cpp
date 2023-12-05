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

#include "include/tester.hpp"

using namespace tester;
using namespace easyjson;

int main()
{
    Tester test;
    EasyJsonCPP configLoader("config.json", test._targetKeys);
    configLoader.loadConfig();
    test.printNestedMap();

    return EXIT_SUCCESS;
}
