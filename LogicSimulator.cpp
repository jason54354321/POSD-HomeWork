#include "Devices/Device.cpp"
#include "FileDataParser.cpp"
#include "Fileloader.cpp"
#include "LogicState.cpp"
#include "OutputHandler.cpp"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class LogicSimulator {
private:
  DeviceAmount deviceAmount;
  bool fileloadSuccess = false;
  vector<Device *> circuits;
  vector<Device *> iPins;
  vector<Device *> oPins;
  vector<vector<string>> fileData;

  void initIPinsLogic(vector<LogicState> logics) {
    int iPinsNumber = 0;
    for (LogicState logic : logics) {
      iPins[iPinsNumber++]->setLogicState(logic);
    }

    // test
    LogicState testLogic = iPins[0]->getLogicState();
    cout << "testLogic" << testLogic << endl;
    testLogic = iPins[1]->getLogicState();
    cout << "testLogic" << testLogic << endl;
    testLogic = iPins[2]->getLogicState();
    cout << "testLogic" << testLogic << endl;
  }

  void flushCircuitLogic() {
    for (auto circuit : circuits) {
      circuit->setLogicState(UNKNOWN);
    }
  }

  void initCircuitLogic() {
    flushCircuitLogic();

    bool calulateFlag = true;
    while (calulateFlag) {
      calulateFlag = false;
      for (Device *circuit : circuits) {
        if (circuit->calOutput() == UNKNOWN) {
          calulateFlag = true;
        }
      }
    }
  }

public:
  DeviceAmount getDeviceAmount() {
    deviceAmount.iPinsAmount = iPins.size();
    deviceAmount.circuitAmount = circuits.size();
    deviceAmount.oPinsAmount = oPins.size();

    return deviceAmount;
  }

  string getSimulationResult(vector<LogicState> iPinLogics) {
    initIPinsLogic(iPinLogics);
    initCircuitLogic();

    OutputHandler outputConverter(deviceAmount, iPins, oPins);

    stringstream output;
    output << outputConverter.getHeaderLine();
    output << outputConverter.getBodyLine();

    return output.str();
  };
  string toBinaryString(int n, int NumOfInput) {
    std::string str;
    while (n != 0) {
      str = (n % 2 == 0 ? "0" : "1") + str;
      n /= 2;
    }

    int goalDigit = NumOfInput;
    int paddingDigit = goalDigit - str.size();

    stringstream strHolder;
    strHolder << string(paddingDigit, '0') + str;

    return strHolder.str();
  }
  vector<LogicState> toIPinLogics(string binary, int numOfInput) {
    vector<LogicState> logicLine;
    for (int i = 0; i < numOfInput; i++) {
      LogicState logic = static_cast<LogicState>(binary[i] - 48);
      logicLine.push_back(logic);
    }
    return logicLine;
  }

  string getTruthTable() {
    OutputHandler outputConverter(deviceAmount, iPins, oPins);
    int numOfInput = iPins.size();
    stringstream output;

    output << outputConverter.getHeaderLine();
    for (int n = 0; n < pow(2, numOfInput); n++) {
      string binary = toBinaryString(n, numOfInput);
      vector<LogicState> iPinLogics = toIPinLogics(binary, numOfInput);
      initIPinsLogic(iPinLogics);
      initCircuitLogic();

      outputConverter.set(deviceAmount, iPins, oPins);

      output << outputConverter.getBodyLine();
    }
    /* cout << "-----------" << endl; */
    /* cout << output.str() << endl; */
    /* cout << "-----------" << endl; */
    return output.str();
  }

  bool load(string path) {
    Fileloader fileloader(path);
    if (!fileloader.load()) {
      return false;
    }

    fileData = fileloader.getFileData();
    fileloader.showFileData(fileData);
    FileDataParser fileDataParser(fileData);

    iPins = fileDataParser.getIPins();
    circuits = fileDataParser.getCircuits();

    fileDataParser.analyzeCircuitsInput(circuits, iPins);
    oPins = fileDataParser.getOPins(circuits);
    deviceAmount = getDeviceAmount();

    fileloadSuccess = true;
    return true;
  };

  int getIPinsSize() { return iPins.size(); }
  bool getFileloadSuccess() { return fileloadSuccess; }
};
