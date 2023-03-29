#include "LogicSimulator.h"
#include "LogicState.h"
#include <gtest/gtest.h>
#include <vector>

TEST(TestLoad, SampleFile1) {
  // Arrange
  string path = "123.lcf";
  // Act
  LogicSimulator logicSimulator;

  // ASSERT
  EXPECT_TRUE(logicSimulator.load(path));
}

TEST(TestLoad, SampleFile2) {
  // Arrange
  string path = "asd.lcf";
  // Act
  LogicSimulator logicSimulator;

  // ASSERT
  EXPECT_TRUE(logicSimulator.load(path));
}

TEST(TestLoad, MissingFile) {
  // Arrange
  string path = "987.lcf";
  // Act
  LogicSimulator logicSimulator;

  // ASSERT
  EXPECT_FALSE(logicSimulator.load(path));
}

// firxture
struct TestSimulationResult : testing::Test {
  LogicSimulator logicSimulator;
  string path = "123.lcf";
  vector<LogicState> iPinLogics;
  vector<LogicState> oPins;
  LogicState result;

  void SetUp() override { logicSimulator.load(path); }
  void TearDown() override {}
};

TEST_F(TestSimulationResult, InputPin000) {
  // Arrange
  iPinLogics.push_back(LOW);
  iPinLogics.push_back(LOW);
  iPinLogics.push_back(LOW);

  // Act
  oPins = logicSimulator.getSimulationResult(iPinLogics);
  result = oPins[0];

  // ASSERT
  EXPECT_EQ(result, LOW);
}

TEST_F(TestSimulationResult, InputPin010) {
  // Arrange
  iPinLogics.push_back(LOW);
  iPinLogics.push_back(HIGH);
  iPinLogics.push_back(LOW);

  // Act
  oPins = logicSimulator.getSimulationResult(iPinLogics);
  result = oPins[0];

  // ASSERT
  EXPECT_EQ(result, LOW);
}

TEST_F(TestSimulationResult, InputPin100) {
  // Arrange
  iPinLogics.push_back(HIGH);
  iPinLogics.push_back(LOW);
  iPinLogics.push_back(LOW);

  // Act
  oPins = logicSimulator.getSimulationResult(iPinLogics);
  result = oPins[0];

  // ASSERT
  EXPECT_EQ(result, HIGH);
}

struct TestToBinaryString : testing::Test {
  LogicSimulator logicSimulator;
  int number;
  int howManyDigit = 3;
  string result;
};

TEST_F(TestToBinaryString, Convert0) {
  // Arrange
  number = 0;

  // Act
  result = logicSimulator.toBinaryString(number, howManyDigit);

  // ASSERT
  EXPECT_EQ(result, "000");
}
TEST_F(TestToBinaryString, Convert2) {
  // Arrange
  number = 2;

  // Act
  result = logicSimulator.toBinaryString(number, howManyDigit);

  // ASSERT
  EXPECT_EQ(result, "010");
}

TEST_F(TestToBinaryString, Convert5) {
  // Arrange
  number = 5;

  // Act
  result = logicSimulator.toBinaryString(number, howManyDigit);

  // ASSERT
  EXPECT_EQ(result, "101");
}

TEST(TestGetTruthTable, normal) {
  // Arrange

  LogicSimulator logicSimulator;
  string path = "123.lcf";
  string expectString;
  string result;
  expectString = "i i i | o \n"
                 "1 2 3 | 1 \n"
                 "------+--\n"
                 "0 0 0 | 0 \n"
                 "0 0 1 | 0 \n"
                 "0 1 0 | 0 \n"
                 "0 1 1 | 0 \n"
                 "1 0 0 | 1 \n"
                 "1 0 1 | 1 \n"
                 "1 1 0 | 0 \n"
                 "1 1 1 | 0 \n";

  // Act
  logicSimulator.load(path);
  result = logicSimulator.getTruthTable();

  // ASSERT
  EXPECT_EQ(result, expectString);
}
