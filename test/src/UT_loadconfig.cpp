#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "easyjsonmock.h"

using namespace easyjson;

// Test case to validate processMemberData method with string input
TEST_F(EasyJsonMock, ProcessMemberDataWithStringValue)
{
    // Arrange: Prepare the input parameters
    std::string member = "member1";
    std::string sectionName = "section1";
    Json::Value sectionValue = "value1";

    // Act: Call the method under test
    ASSERT_NO_THROW({
        easyjson->processMemberData(member, sectionName, sectionValue);
    });

    // Assert: Verify the expected behavior or outcome
    EXPECT_EQ(easyjson->_mainMap[member][sectionName], "value1");
}