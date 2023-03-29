#ifndef FileDataParser_H
#define FileDataParser_H
#include "Device.h"
#include "GateAND.h"
#include "GateNOT.h"
#include "GateOR.h"
#include "IPin.h"
#include "OPin.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
class FileDataParser {
private:
  vector<vector<string>> _fileData;
  int circuitAmount;
  int iPinsAmount;
  int oPinsAmount;

  vector<string> getCommandLine(int circuitNumber);

  Device *buildCircuit(int circuitNumber);

  int toZerobaseIndex(int oneBase);

public:
  FileDataParser(vector<vector<string>> fileData);

  vector<Device *> getIPins();

  vector<Device *> getCircuits();

  int getIndex(string command);

  bool isIPin(string command);
  bool isCircuit(string command);

  void analyzeCircuitsInput(vector<Device *> circuits, vector<Device *> iPins);

  vector<Device *> getOPins(vector<Device *> circuits);
};
#endif /* ifndef FileDataParser_H */
