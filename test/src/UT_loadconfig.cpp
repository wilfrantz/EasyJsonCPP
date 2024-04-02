#include "easyjsonmock.h"

using namespace easyjson;

TEST(EasyJsonMock, processMemberDataPass)
{
    std::string member = "member1";
    std::string key = "section1";
    Json::Value value = "value1";

    EasyJsonMock *mock;
    mock->processMemberDataMock(member, key, value);
}