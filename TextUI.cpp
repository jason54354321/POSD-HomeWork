#include "LogicSimulator.cpp"
#include "UserCommand.h"
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

class TextUI {
private:
  bool runningFlag = true;
  LogicSimulator logicSimulator;
  const string greetingMessage = "\n"
                                 "1. Load logic circuit file\n"
                                 "2. Simulation\n"
                                 "3. Display truth table\n"
                                 "4. Exit";
  bool isFileLoaded() { return logicSimulator.getFileloadSuccess(); }

  string getiPinLogicFromUser(int index) {
    UserCommand userCommand(regexType.simulate);
    stringstream userHint;
    userHint << "Please key in the value of input pin " << index;
    displayMessage(userHint.str());

    return userCommand.waitingInput();
  }

  void loadingFile() {
    displayMessage("Please key in a file path: ");

    UserCommand userCommand(regexType.path);
    string path;
    path = userCommand.waitingInput();
    while (!logicSimulator.load(path)) {
      path = userCommand.waitingInput();
    }

    DeviceAmount dAmount = logicSimulator.getDeviceAmount();
    stringstream ss;
    ss << "Circuit: ";
    ss << dAmount.iPinsAmount << " input pins, ";
    ss << dAmount.oPinsAmount << " output pins and ";
    ss << dAmount.circuitAmount << " gates";

    displayMessage(ss.str());
  };

  bool isLogicFormatRight(string iPinLogic) {
    int iPinLogicInt = stoi(iPinLogic);
    bool isExcessRange = iPinLogicInt > 1 || iPinLogicInt < 0;
    return isExcessRange ? false : true;
  }
  void letUserResubmit(int &loopIndex) {
    loopIndex--;
    displayMessage("Input error: Excess Range of input, Please enter 0/1");
  }

  LogicState transToLogic(string logicStr) {
    LogicState logicState;
    if (logicStr == "0") {
      return logicState = LOW;
    } else if (logicStr == "1") {
      return logicState = HIGH;
    } else {
      return logicState = UNKNOWN;
    }
  }

  void simulation() {
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
        iPinSignal = transToLogic(iPinLogicStr);
        iPinSignals.push_back(iPinSignal);
      } else {
        letUserResubmit(index);
      }
    }

    displayMessage(logicSimulator.getSimulationResult(iPinSignals));
  };
  void truthTable() {
    if (!isFileLoaded()) {
      displayMessage("Please load an lcf file first!");
      return;
    }
    displayMessage(logicSimulator.getTruthTable());
  };
  void exit() { runningFlag = false; }
  void mainLoop() {
    while (runningFlag) {
      displayMessage(greetingMessage);
      processCommand();
    }
  }

public:
  TextUI() { mainLoop(); }

  void displayMessage(string message) { cout << message << endl; }
  void processCommand() {
    UserCommand menuCommand(regexType.menu);
    string menuInput;
    menuInput = menuCommand.waitingInput();

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
};
