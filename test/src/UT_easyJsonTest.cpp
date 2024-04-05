#include "easyjsonmock.h"

using namespace easyjson;

TEST(EasyJsonMock, parseArrayObjectDataPassed)
{
    Json::Value object;
    Json::Value arrayMember(Json::arrayValue);
    Json::Value rootObjects(Json::arrayValue);

    arrayMember.append("8080");
    arrayMember.append("example.com");
    arrayMember.append("192.168.1.1");
    object["server"] = arrayMember;

    Json::Value objectMember; 
    objectMember["key"] = "value";
    object["objectMember"] = objectMember;

    rootObjects.append(object); 

    EasyJsonMock mock;

    ASSERT_NO_THROW(mock.gmock_parseArrayObjectData(rootObjects));
}

TEST(EasyJsonMock, parseArrayObjectDataFailed)
{

    try
    {
        Json::Value arrayObj;

        Json::Value arrayValue(Json::arrayValue);

        Json::Value objectValue;
        objectValue["data1"] = "data2";
        arrayValue.append(objectValue);

        arrayObj["array"] = arrayValue;
        EasyJsonMock mock;
        // mock.parseArrayObjectDataMock(arrayObj);
        mock.gmock_parseArrayObjectData(arrayObj);
    }
    catch (const std::runtime_error &e)
    {
        std::string error("Invalid format for object in configuration file.");
        EXPECT_EQ(e.what(), error);
    }
}

TEST(EasyJsonMock, processMemberDataPassed)
{
    std::string member = "member1";
    std::string key = "section1";
    Json::Value value;
    value["pie"] = 3.14;

    try
    {
        EasyJsonMock *mock = new EasyJsonMock();
        mock->gmock_processMemberData(member, key, value);
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

        mock->gmock_parseObjectMemberData(member, objectValue);
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
    objectValue["pie"] = 3;
    std::string member = "member";

    EasyJsonMock mock;
    EasyJsonCPP ease;

    mock.gmock_parseObjectMemberData(member, objectValue);

    EXPECT_TRUE(ease._mainMap.empty());
}