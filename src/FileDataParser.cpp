#include "FileDataParser.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define iPinLine fileData[0][0]
#define circuitLine fileData[1][0]

using namespace std;

vector<string> FileDataParser::getCommandLine(int circuitNumber) {
  const int firstCircuitCommandLine = 2;
  vector<string> circuitCommand =
      _fileData[circuitNumber + firstCircuitCommandLine];
  return circuitCommand;
}

Device *FileDataParser::buildCircuit(int circuitNumber) {
  vector<string> commandLine = getCommandLine(circuitNumber);

  const int gateTypeIndex = 0;
  int gateType = stoi(commandLine[gateTypeIndex]);

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
    throw runtime_error("gateType Error!!, Input file contains wrong data");
    break;
  }

  return circuit;
};

int FileDataParser::toZerobaseIndex(int oneBase) { return oneBase - 1; }

FileDataParser::FileDataParser(vector<vector<string>> fileData)
    : _fileData(fileData) {
  iPinsAmount = stoi(iPinLine);
  circuitAmount = stoi(circuitLine);
}

vector<Device *> FileDataParser::getIPins() {
  vector<Device *> iPins;

  for (int i = 0; i < iPinsAmount; i++) {
    Device *iPin = new IPin();
    iPin->name = "iPin" + to_string(iPins.size() + 1);
    iPins.push_back(iPin);
  }

  return iPins;
};

vector<Device *> FileDataParser::getCircuits() {
  vector<Device *> circuits;

  for (int circuitNumber = 0; circuitNumber < circuitAmount; circuitNumber++) {
    Device *circuit = buildCircuit(circuitNumber);
    circuit->name = "circuit" + to_string(circuits.size() + 1);
    circuits.push_back(circuit);
  }
  return circuits;
};

int FileDataParser::getIndex(string command) {
  int index;
  index = stoi(command);
  index = abs(index);
  index = toZerobaseIndex(index);
  return index;
}

bool FileDataParser::isIPin(string command) {
  float commandFloat;
  commandFloat = stof(command);

  return commandFloat < 0;
}
bool FileDataParser::isCircuit(string command) {
  float commandFloat;
  commandFloat = stof(command);

  return commandFloat > 0;
}

void FileDataParser::analyzeCircuitsInput(vector<Device *> circuits,
                                          vector<Device *> iPins) {
  int circuitNumber = 0;
  for (auto circuit : circuits) {
    vector<string> commandLine;
    string command;
    int index;
    int iPinIndex = 1;

    commandLine = getCommandLine(circuitNumber++);

    while (command != "0") {
      command = commandLine[iPinIndex++];
      index = getIndex(command);

      if (isIPin(command)) {
        circuit->addInputPin(iPins[index]);
      } else if (isCircuit(command)) {
        circuit->addInputPin(circuits[index]);

        // It couldn't be the final output pin since
        // circuit only got one output pin.
        circuits[index]->isOutputPin = false;
      }
    }
  }
}

vector<Device *> FileDataParser::getOPins(vector<Device *> circuits) {
  vector<Device *> OPins;
  for (auto circuit : circuits) {
    if (circuit->isOutputPin) {
      OPins.push_back(circuit);
    }
  }

  return OPins;
}
