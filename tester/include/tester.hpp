/**
 * @file tester.hpp
 * @brief Header file for the Tester class.
 *
 * This file contains the definition of the Tester class, which is used for
 *
 * The class provides // TODO
 *
 *
 * @author: (C) 2023 Wilfrantz Dede
 */

#ifndef TESTER_HPP
#define TESTER_HPP

#include "include/header.hpp"

namespace tester
{

    class Tester
    {
    public:
        Tester() {}
        static std::map<std::string, std::string> _configMap;
        std::shared_ptr<spdlog::logger> _logger = spdlog::stdout_color_mt("Tester");
        const std::vector<std::string> _targetKeys = {"twitter", "tiktok", "instagram", "facebook"};

    private:
    };
}

#endif // !TESTER_HPP