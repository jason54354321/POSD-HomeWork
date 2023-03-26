#include "devices/Device.cpp"
#include "devices/GateAND.cpp"
#include "devices/GateNOT.cpp"
#include "devices/GateOR.cpp"
#include "devices/IPin.cpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define iPinLine fileData[0][0]
#define circuitLine fileData[1][0]

using namespace std;
class FileDataParser {
private:
  vector<vector<string>> _fileData;
  int circuitAmount;
  int iPinsAmount;
  int oPinsAmount;

  vector<string> getCircuitCommand(int circuitNumber) {
    const int firstCircuitCommandLine = 2;
    vector<string> circuitCommand =
        _fileData[circuitNumber + firstCircuitCommandLine];
    return circuitCommand;
  }

  Device *buildCircuit(int circuitNumber) {
    vector<string> circuitCommand = getCircuitCommand(circuitNumber);
    cout << "gate" << circuitNumber << ":";

    const int gateTypeIndex = 0;
    int gateType = stoi(circuitCommand[gateTypeIndex]);
    cout << " type:" << gateType << endl;

    Device *circuit;
    switch (gateType) {
    case 1:
      circuit = new GateAND();
      break;
    case 2:
      circuit = new GateOR();
      break;
    case 3:
      circuit = new GateNOT();
      break;
    default:
      throw runtime_error("gateType Error!!");
      break;
    }

    return circuit;
  };

  int toZerobaseIndex(int oneBase) { return oneBase - 1; }

public:
  FileDataParser(vector<vector<string>> fileData) : _fileData(fileData) {
    iPinsAmount = stoi(iPinLine);
    circuitAmount = stoi(circuitLine);
    cout << "----------" << endl;
  }

  vector<Device *> getIPins() {
    vector<Device *> iPins;

    for (int i = 0; i < iPinsAmount; i++) {
      Device *iPin = new IPin();
      iPin->name = "iPin" + to_string(iPins.size() + 1);
      iPins.push_back(iPin);
    }

    return iPins;
  };

  vector<Device *> getCircuits() {
    vector<Device *> circuits;

    for (int circuitNumber = 0; circuitNumber < circuitAmount;
         circuitNumber++) {
      Device *circuit = buildCircuit(circuitNumber);
      circuit->name = "circuit" + to_string(circuits.size() + 1);
      circuits.push_back(circuit);
    }
    return circuits;
  };

  int getIndex(string command) {
    int index;
    index = stoi(command);
    index = abs(index);
    index = toZerobaseIndex(index);
    return index;
  }

  bool isIPinInput(string command) {
    float commandFloat;
    commandFloat = stof(command);

    return commandFloat < 0;
  }
  bool isCircuitInput(string command) {
    float commandFloat;
    commandFloat = stof(command);

    return commandFloat > 0;
  }

  void analyzeCircuitsInput(vector<Device *> circuits, vector<Device *> iPins) {
    int circuitNumber = 0;
    for (auto circuit : circuits) {
      vector<string> circuitCommand;
      string command;
      int index;
      int iPinIndex = 1;

      circuitCommand = getCircuitCommand(circuitNumber++);

      while (command != "0") {
        command = circuitCommand[iPinIndex++];
        index = getIndex(command);

        if (isIPinInput(command)) {
          cout << "circuit:" << circuitNumber;
          cout << "->addiPin:" << index << endl;
          circuit->addInputPin(iPins[index]);
        } else if (isCircuitInput(command)) {
          cout << "circuit:" << circuitNumber;
          cout << "->addCircuit:" << index << endl;
          circuit->addInputPin(circuits[index]);

          // It couldn't be the final output pin since
          // circuit only got One output pin.
          circuits[index]->isOutputPin = false;
        }
      }
    }
  }

  vector<Device *> getOPins(vector<Device *> circuits) {
    vector<Device *> OPins;
    for (auto circuit : circuits) {
      if (circuit->isOutputPin) {
        OPins.push_back(circuit);
      }
    }

    return OPins;
  }
};
