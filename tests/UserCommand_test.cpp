#include "UserCommand.h"
#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <regex>

class MockUserCommand : UserCommand {
public:
  FRIEND_TEST(UserInputTest, regex);
  MockUserCommand(regex reg) : UserCommand(reg){};
  MOCK_METHOD(string, waitInput, ());
};

using testing::Return;

TEST(UserInputTest, regex) {
  // Arrange
  MockUserCommand userCommand(regex("\\d"));
  EXPECT_CALL(userCommand, waitInput())
      .WillOnce(Return(""))
      .WillOnce(Return(" "))
      .WillOnce(Return("?"))
      .WillOnce(Return("20"))
      .WillOnce(Return("12"))
      .WillOnce(Return("-12"))
      .WillOnce(Return("8"));

  // Act
  string result;
  result = userCommand.getUserInput();

  // Assert
  EXPECT_EQ(result, "8");
}
