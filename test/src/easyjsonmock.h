#ifndef EASYJSON_MOCK_H
#define EASYJSON_MOCK_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <easyjson.h>

namespace easyjson
{
    class EasyJsonMock : public ::testing::Test
    {
    public:
        EasyJsonMock() : easyJson(new EasyJsonCPP()) {}

        void gmock_parseArrayObjectData(const Json::Value &rootObjects)
        {
            easyJson->parseArrayObjectData(rootObjects);
        }

        void gmock_processMemberData(const std::string &member, const std::string &key, const Json::Value &value)
        {
            easyJson->processMemberData(member, key, value);
        }

        void gmock_parseObjectMemberData(const std::string &member, const Json::Value &objectValue)
        {
            easyJson->parseObjectMemberData(member, objectValue);
        }

        // Mock methods /// NOTE: not sure why I get a linking issue when I use these.
        // MOCK_METHOD(void, loadConfiguration, ());
        // MOCK_METHOD(void, parseArrayObjectData, (const Json::Value &root));
        // MOCK_METHOD(void, validateRootObject, (const Json::Value &root));
        // MOCK_METHOD(void, parseArrayMemberData, (const std::string &member, const Json::Value &arrayValue));
        // MOCK_METHOD(void, parseObjectMemberData, (const std::string &member, const Json::Value &objectValue));
        // MOCK_METHOD(void, processMemberData, (const std::string &member, const std::string &key, const Json::Value &value));

        EasyJsonCPP *easyJson;

        ~EasyJsonMock() {}

    protected:
        void SetUp() override {}
        void TestBody() override {}
        void TearDown() override {}
    };
} // namespace easyjson

#endif // EASYJSON_MOCK_H
