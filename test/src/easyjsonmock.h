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
        EasyJsonMock() : easy(new EasyJsonCPP()) {}

        // Mock methods
        // MOCK_METHOD(void, loadConfiguration, ());
        // MOCK_METHOD(void, parseArrayObjectData, (const Json::Value &root));
        // MOCK_METHOD(void, validateRootObject, (const Json::Value &root));
        // MOCK_METHOD(void, parseArrayMemberData, (const std::string &member, const Json::Value &arrayValue));
        // MOCK_METHOD(void, parseObjectMemberData, (const std::string &member, const Json::Value &objectValue));
        MOCK_METHOD(void, processMemberData, (const std::string &member, const std::string &key, const Json::Value &value));

        ~EasyJsonMock() { delete easy; }

    protected:
        EasyJsonCPP *easy;

        void SetUp() override {}
        void TearDown() override {}
    };
} // namespace easyjson

#endif // EASYJSON_MOCK_H
