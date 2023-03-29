#include "Device.h"
#include "GateAND.h"
#include "GateNOT.h"
#include "GateOR.h"
#include "IPin.h"
#include "LogicState.h"
#include "OPin.h"
#include <gtest/gtest.h>

TEST(IPinTest, SetterGetter) {
  // Arrange
  IPin *ipin = new IPin();

  // Act
  ipin->setLogicState(HIGH);
  LogicState result1 = ipin->getLogicState();
  ipin->setLogicState(LOW);
  LogicState result2 = ipin->getLogicState();
  ipin->setLogicState(UNKNOWN);
  LogicState result3 = ipin->getLogicState();

  // Assert
  EXPECT_EQ(result1, HIGH);
  EXPECT_EQ(result2, LOW);
  EXPECT_EQ(result3, UNKNOWN);
}

TEST(OPinTest, SetterGetter) {
  // Arrange
  OPin *oPin = new OPin();

  // Act
  oPin->setLogicState(HIGH);
  LogicState result1 = oPin->getLogicState();
  oPin->setLogicState(LOW);
  LogicState result2 = oPin->getLogicState();
  oPin->setLogicState(UNKNOWN);
  LogicState result3 = oPin->getLogicState();

  // Assert
  EXPECT_EQ(result1, HIGH);
  EXPECT_EQ(result2, LOW);
  EXPECT_EQ(result3, UNKNOWN);
}

// Fixture
struct GateORTest : public testing::Test {
  GateOR *gateOR = new GateOR();
  IPin *LowPin = new IPin();
  IPin *HighPin = new IPin();

  void SetUp() override {
    LowPin->setLogicState(LOW);
    HighPin->setLogicState(HIGH);
  }
  void TearDown() override {
    delete gateOR;
    delete LowPin;
    delete HighPin;
  }
};

TEST_F(GateORTest, CalOutputLOW) {
  // Arrange
  gateOR->addInputPin(LowPin);

  // Act
  int result = gateOR->calOutput();

  // Assert
  EXPECT_EQ(result, LOW);
}

TEST_F(GateORTest, CalOutputHIGH) {
  // Arrange
  gateOR->addInputPin(HighPin);

  // Act
  int result = gateOR->calOutput();

  // Assert
  EXPECT_EQ(result, HIGH);
}
TEST_F(GateORTest, CalOutputBOTH) {
  // Arrange
  gateOR->addInputPin(HighPin);
  gateOR->addInputPin(LowPin);
  // Act
  int result = gateOR->calOutput();

  // Assert
  EXPECT_EQ(result, HIGH);
}

// Fixture
struct GateANDTest : public testing::Test {
  GateAND *gateAND = new GateAND();
  IPin *LowPin = new IPin();
  IPin *HighPin = new IPin();

  void SetUp() override {
    LowPin->setLogicState(LOW);
    HighPin->setLogicState(HIGH);
  }
  void TearDown() override {
    delete gateAND;
    delete LowPin;
    delete HighPin;
  }
};

TEST_F(GateANDTest, CalOutputLOW) {
  // Arrange
  gateAND->addInputPin(LowPin);

  // Act
  int result = gateAND->calOutput();

  // Assert
  EXPECT_EQ(result, LOW);
}

TEST_F(GateANDTest, CalOutputHIGH) {
  // Arrange
  gateAND->addInputPin(HighPin);
  // Act
  int result = gateAND->calOutput();

  // Assert
  EXPECT_EQ(result, HIGH);
}
TEST_F(GateANDTest, CalOutputBOTH) {
  // Arrange
  gateAND->addInputPin(HighPin);
  gateAND->addInputPin(LowPin);

  // Act
  int result = gateAND->calOutput();

  // Assert
  EXPECT_EQ(result, LOW);
}

// Fixture
struct GateNOTTest : public testing::Test {
  GateNOT *gateNOT = new GateNOT();
  IPin *LowPin = new IPin();
  IPin *HighPin = new IPin();

  void SetUp() override {
    LowPin->setLogicState(LOW);
    HighPin->setLogicState(HIGH);
  }
  void TearDown() override {
    delete gateNOT;
    delete LowPin;
    delete HighPin;
  }
};

TEST_F(GateNOTTest, CalOutputLOW) {
  // Arrange
  gateNOT->addInputPin(LowPin);

  // Act
  int result = gateNOT->calOutput();

  // Assert
  EXPECT_EQ(result, HIGH);
}

TEST_F(GateNOTTest, CalOutputHIGH) {
  // Arrange
  gateNOT->addInputPin(HighPin);
  // Act
  int result = gateNOT->calOutput();

  // Assert
  EXPECT_EQ(result, LOW);
}
