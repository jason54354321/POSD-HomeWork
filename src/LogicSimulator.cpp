#include "LogicSimulator.h"
#include "LogicState.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void LogicSimulator::initIPinsLogic(vector<LogicState> logics) {
  int iPinsNumber = 0;
  for (LogicState logic : logics) {
    iPins[iPinsNumber++]->setLogicState(logic);
  }
}

void LogicSimulator::flushCircuitLogic() {
  for (auto circuit : circuits) {
    circuit->setLogicState(UNKNOWN);
  }
}

void LogicSimulator::initCircuitLogic() {
  flushCircuitLogic();

  bool running = true;
  while (running) {
    running = false;
    for (Device *circuit : circuits) {
      if (circuit->calOutput() == UNKNOWN) {
        running = true;
      }
    }
  }
}

void LogicSimulator::freePointer() {
  if (iPins.size() == 0 && circuits.size() == 0) {
    return;
  }
  cout << "---------" << endl;
  for (auto iPin : iPins) {
    delete iPin;
  }
  for (auto circuit : circuits) {
    delete circuit;
  }
  cout << "---------" << endl;
  // Doesn't need to free OPins since all the OPin's pins contain in circuits
}

DeviceAmount LogicSimulator::getDeviceAmount() {
  deviceAmount.iPinsAmount = iPins.size();
  deviceAmount.circuitAmount = circuits.size();
  deviceAmount.oPinsAmount = oPins.size();

  return deviceAmount;
}

vector<LogicState>
LogicSimulator::getSimulationResult(vector<LogicState> iPinLogics) {
  initIPinsLogic(iPinLogics);
  initCircuitLogic();

  vector<LogicState> result;
  for (Device *oPin : oPins) {
    result.push_back(oPin->getLogicState());
  }
  return result;
};

string LogicSimulator::getHeaderLine() {
  StringParser outputConverter(deviceAmount, iPins, oPins);
  stringstream output;
  output << outputConverter.getHeaderLine();

  return output.str();
}

string LogicSimulator::getBodyLine() {
  StringParser outputConverter(deviceAmount, iPins, oPins);
  stringstream output;
  output << outputConverter.getBodyLine();

  return output.str();
}

string LogicSimulator::toBinaryString(int n, int goalDigit) {
  std::string str;
  while (n != 0) {
    str = (n % 2 == 0 ? "0" : "1") + str;
    n /= 2;
  }

  int paddingDigit = goalDigit - str.size();

  stringstream strHolder;
  strHolder << string(paddingDigit, '0') + str;

  return strHolder.str();
}

vector<LogicState> LogicSimulator::toIPinLogics(string binary, int numOfInput) {
  vector<LogicState> logicLine;
  for (int i = 0; i < numOfInput; i++) {
    LogicState logic = static_cast<LogicState>(binary[i] - 48);
    logicLine.push_back(logic);
  }
  return logicLine;
}

string LogicSimulator::getTruthTable() {
  int numOfInput = iPins.size();
  stringstream output;

  output << getHeaderLine();
  for (int n = 0; n < pow(2, numOfInput); n++) {
    string binary = toBinaryString(n, numOfInput);
    vector<LogicState> iPinLogics = toIPinLogics(binary, numOfInput);
    initIPinsLogic(iPinLogics);
    initCircuitLogic();

    output << getBodyLine();
  }
  return output.str();
}

bool LogicSimulator::load(string path) {
  Fileloader fileloader(path);
  if (!fileloader.load()) {
    return false;
  }

  fileData = fileloader.getFileData();
  FileDataParser fileDataParser(fileData);

  iPins = fileDataParser.createIPins();
  circuits = fileDataParser.createCircuits();
  fileDataParser.analyzeCircuitsInput(circuits, iPins);
  oPins = fileDataParser.createOPins(circuits, iPins);

  deviceAmount = getDeviceAmount();
  isFileloaded = true;

  return true;
};

int LogicSimulator::getIPinsSize() { return iPins.size(); }
vector<Device *> LogicSimulator::getIPins() { return iPins; }
vector<Device *> LogicSimulator::getOPins() { return oPins; }
bool LogicSimulator::getFileloadSuccess() { return isFileloaded; }
