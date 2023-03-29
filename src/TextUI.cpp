#include "TextUI.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct {
  regex menu = regex("\\d");
  regex path = regex(".*\\.lcf");
  regex simulate = regex("\\d{1}");
} regexType;

TextUI::TextUI(){};

bool TextUI::isFileLoaded() { return logicSimulator.getFileloadSuccess(); }

string TextUI::getiPinLogicFromUser(int index) {
  UserCommand userCommand(regexType.simulate);
  string userHint =
      "Please key in the value of input pin " + to_string(index + 1);
  displayMessage(userHint);

  return userCommand.getUserInput();
}

void TextUI::showDeviceAmount() {
  DeviceAmount dAmount = logicSimulator.getDeviceAmount();
  stringstream ss;
  ss << "Circuit: ";
  ss << dAmount.iPinsAmount << " input pins, ";
  ss << dAmount.oPinsAmount << " output pins and ";
  ss << dAmount.circuitAmount << " gates";

  displayMessage(ss.str());
}

void TextUI::loadingFile() {
  logicSimulator.freePointer();
  displayMessage("Please key in a file path: ");

  UserCommand userCommand(regexType.path);
  string path = userCommand.getUserInput();

  while (!logicSimulator.load(path)) {
    path = userCommand.getUserInput();
  }

  showDeviceAmount();
};

bool TextUI::isLogicFormatRight(string iPinLogic) {
  int iPinLogicInt = stoi(iPinLogic);
  bool isExcessRange = iPinLogicInt > 1 || iPinLogicInt < 0;
  return isExcessRange ? false : true;
}
void TextUI::letUserResubmit(int &loopIndex) {
  loopIndex--;
  displayMessage("Input error: Excess Range of input, Please enter 0/1");
}

void TextUI::simulation() {
  if (!isFileLoaded()) {
    displayMessage("Please load an lcf file first!");
    return;
  }

  LogicState iPinSignal;
  vector<LogicState> iPinSignals;

  int iPinsSize = logicSimulator.getIPinsSize();
  for (int index = 0; index < iPinsSize; index++) {
    string iPinLogicStr = getiPinLogicFromUser(index);

    if (isLogicFormatRight(iPinLogicStr)) {
      iPinSignal = static_cast<LogicState>(stoi(iPinLogicStr));
      iPinSignals.push_back(iPinSignal);
    } else {
      letUserResubmit(index);
    }
  }

  logicSimulator.getSimulationResult(iPinSignals);

  stringstream result;
  result << logicSimulator.getHeaderLine();
  result << logicSimulator.getBodyLine();
  displayMessage(result.str());
};

void TextUI::truthTable() {
  if (!isFileLoaded()) {
    displayMessage("Please load an lcf file first!");
    return;
  }
  displayMessage(logicSimulator.getTruthTable());
};

void TextUI::exit() {
  logicSimulator.freePointer();
  runningFlag = false;
}

void TextUI::displayMessage(string message) { cout << message << endl; }

void TextUI::mainLoop() {
  while (runningFlag) {
    displayMessage(greetingMessage);
    processCommand();
  }
}

void TextUI::processCommand() {
  UserCommand menuCommand(regexType.menu);
  string menuInput;
  menuInput = menuCommand.getUserInput();

  int action = stoi(menuInput);
  switch (action) {
  case 1:
    loadingFile();
    break;
  case 2:
    simulation();
    break;
  case 3:
    truthTable();
    break;
  case 4:
    exit();
    break;
  default:
    cout << "No such comannd";
  }
}
