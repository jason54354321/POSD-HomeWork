#ifndef TEXTUI_H
#define TEXTUI_H
#include "LogicSimulator.h"
#include "UserCommand.h"
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class TextUI {
private:
  FRIEND_TEST(Mytest, Normal);
  bool runningFlag = true;
  LogicSimulator logicSimulator;
  const string greetingMessage = "\n"
                                 "1. Load logic circuit file\n"
                                 "2. Simulation\n"
                                 "3. Display truth table\n"
                                 "4. Exit";
  bool isFileLoaded();

  string getiPinLogicFromUser(int index);

  void showDeviceAmount();

  void loadingFile();

  bool isLogicFormatRight(string iPinLogic);
  void letUserResubmit(int &loopIndex);

  void simulation();
  void truthTable();
  void exit();
  void displayMessage(string message);

public:
  TextUI();
  void mainLoop();
  void processCommand();
};
#endif
