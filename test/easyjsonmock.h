#ifndef EASYJSON_MOCK_H
#define EASYJSON_MOCK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "easyjson.h"

using ::testing::AtLeast;

namespace easyjson
{
    class EasyJsonMock : public ::testing::Test
    {
    public:
        EasyJsonMock() : easyjson(new EasyJsonCPP()) {}
        ~EasyJsonMock() { delete easyjson; }

        void parseConfigMock(const Json::Value &root)
        {
            easyjson->parseConfig(root);
        }

        bool isTargetKeyMock(const std::string &key) const
        {
            return easyjson->isTargetKey(key);
        }

        void validateConfigRootMock(const Json::Value &root)
        {
            easyjson->validateConfigRoot(root);
        }

        void parseArrayConfigMock(const Json::Value &arrayValue)
        {
            easyjson->parseArrayConfig(arrayValue);
        }

        void parseObjectConfigMock(const Json::Value &objectValue)
        {
            easyjson->parseObjectConfig(objectValue);
        }

        void processConfigValueMock(const std::string &key, const Json::Value &value)
        {
            easyjson->processConfigValue(key, value);
        }

        // Mock methods
        MOCK_METHOD(void, parseConfig, (const Json::Value &root));
        MOCK_METHOD(bool, isTargetKey, (const std::string &key), (const));
        MOCK_METHOD(void, validateConfigRoot, (const Json::Value &root));
        MOCK_METHOD(void, parseArrayConfig, (const Json::Value &arrayValue));
        MOCK_METHOD(void, parseObjectConfig, (const Json::Value &objectValue));
        MOCK_METHOD(void, processConfigValue, (const std::string &key, const Json::Value &value));

    private:
        EasyJsonCPP *easyjson;
    };
} // namespace easyjson

#endif // EASYJSON_MOCK_H
