#include "easyjsonmock.h"

using namespace easyjson;

TEST(EasyJsonMock, processMemberDataPassed)
{
    std::string member = "member1";
    std::string key = "section1";
    Json::Value value;
    value["pie"] = 3.14;

    try
    {
        EasyJsonMock *mock = new EasyJsonMock();
        mock->processMemberDataMock(member, key, value);
        delete mock;
    }
    catch (const std::runtime_error &e)
    {
        std::string error("Invalid format for object value in configuration file.");
        EXPECT_EQ(e.what(), error);
    }
}

TEST(EasyJsonMock, parseObjectMemberDataFailed)
{

    try
    {
        std::string member = "member";
        Json::Value objectValue("3.14");
        EasyJsonMock *mock;

        mock->parseObjectMemberDataMock(member, objectValue);
        delete mock;
    }
    catch (const std::runtime_error &e)
    {
        // ("Invalid format for object value in configuration file.")
        std::string error("Invalid format for object in configuration file.");
        EXPECT_EQ(e.what(), error);
    }
}

TEST(EasyJsonMock, parseObjectMemberDataPassed)
{
        Json::Value objectValue;
        objectValue["pie"] = 3.14;
        std::string member = "member";
        const std::string key = "dumbKey";

        EasyJsonMock mock;

        // Mock the call to processMemberData
        // EXPECT_CALL(mock, processMemberData(member, key, objectValue))
        //     .Times(1);

        mock.parseObjectMemberDataMock(member, objectValue);
}