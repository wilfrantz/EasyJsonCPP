
#include "include/tester.hpp"

namespace tester
{
    // Tester method to print the content of the nested map
    void Tester::printNestedMap(const std::string &prefix = "")
    {
        for (const auto &pair : _configMap)
        {
            std::cout << prefix << pair.first << ": " << std::endl;

            for (const auto &innerPair : pair.second)
            {
                std::cout << prefix << "  " << innerPair.first << ": " << innerPair.second << std::endl;
            }
        }
    }
}