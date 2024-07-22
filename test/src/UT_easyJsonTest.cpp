#include "easyjsonmock.h"

using namespace easyjson;

TEST_F(EasyJsonMock, parseArrayObjectDataPassed)
{
    std::string jsonString = R"([{
        "server" : {
            "port" : "8080",
            "domain" : "example.com",
            "address" : "192.168.1.1"
        }
    }])";

    Json::Value objects(Json::arrayValue);
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();

    // Parse the JSON string into the Json::Value object
    std::string errors;
    bool parsingSuccessful = reader->parse(jsonString.c_str(), jsonString.c_str() + jsonString.length(), &objects, &errors);
    delete reader;

    // Check if parsing was successful
    if (!parsingSuccessful)
    {
        throw std::runtime_error("Failed to parse JSON.");
    }

    EasyJsonMock mock;
    ASSERT_NO_THROW(mock.gmock_parseArrayObjectData(objects));
}

TEST_F(EasyJsonMock, parseArrayObjectDataFailed)
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
        mock.gmock_parseArrayObjectData(arrayObj);
    }
    catch (const std::runtime_error &e)
    {
        std::string error("Invalid format for object in configuration file.");
        ASSERT_EQ(e.what(), error);
    }
}

TEST_F(EasyJsonMock, processMemberDataPassed)
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
        ASSERT_EQ(e.what(), error);
    }
}

TEST_F(EasyJsonMock, parseObjectMemberDataFailed)
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
        std::string error("Invalid format for object in configuration file.");
        ASSERT_EQ(e.what(), error);
    }
}

TEST_F(EasyJsonMock, parseObjectMemberDataPassed)
{
    Json::Value objectValue;
    objectValue["pie"] = 3;
    std::string member = "member";

    EasyJsonMock mock;
    EasyJsonCPP ease;

    mock.gmock_parseObjectMemberData(member, objectValue);

    ASSERT_TRUE(ease._mainMap.empty());
}
