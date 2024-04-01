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

        void loadConfigurationMock()
        {
            easyjson->loadConfiguration();
        }

        void parseArrayObjectMock(const Json::Value &root)
        {
            easyjson->parseArrayObjectData(root);
        }

        void validateRootObjectMock(const Json::Value &root)
        {
            easyjson->validateRootObject(root);
        }

        void parseArrayMemberMock(const std::string &member, const Json::Value &arrayValue)
        {
            easyjson->parseArrayMemberData(member, arrayValue);
        }

        void parseObjectMemberMock(const std::string &member, const Json::Value &objectValue)
        {
            easyjson->parseObjectMemberData(member, objectValue);
        }

        void processMemberMock(const std::string &member, const std::string &key, const Json::Value &value)
        {
            easyjson->processMemberData(member, key, value);
        }

        // Mock methods
        MOCK_METHOD(void, validateRootObject, (const Json::Value &root));
        MOCK_METHOD(void, parseArrayObjectData, (const Json::Value &root));
        MOCK_METHOD(void, parseArrayMemberData, (const std::string &member, const Json::Value &arrayValue));
        MOCK_METHOD(void, parseObjectMemberData, (const std::string &member, const Json::Value &objectValue));
        MOCK_METHOD(void, processMemberData, (const std::string &member, const std::string &key, const Json::Value &value));

    protected:
        EasyJsonCPP *easyjson;
    };
} // namespace easyjson

#endif // EASYJSON_MOCK_H
