#ifndef LogicSimulator_H
#define LogicSimulator_H
#include "Device.h"
#include "FileDataParser.h"
#include "Fileloader.h"
#include "LogicState.h"
#include "StringParser.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class LogicSimulator {
private:
  FRIEND_TEST(TestToBinaryString, Convert0);
  FRIEND_TEST(TestToBinaryString, Convert2);
  FRIEND_TEST(TestToBinaryString, Convert5);

  DeviceAmount deviceAmount;
  bool isFileloaded = false;
  vector<Device *> circuits;
  vector<Device *> iPins;
  vector<Device *> oPins;
  vector<vector<string>> fileData;

  void initIPinsLogic(vector<LogicState> logics);

  void flushCircuitLogic();

  void initCircuitLogic();
  string toBinaryString(int n, int NumOfInput);
  vector<LogicState> toIPinLogics(string binary, int numOfInput);

public:
  void freePointer();

  DeviceAmount getDeviceAmount();

  vector<LogicState> getSimulationResult(vector<LogicState> iPinLogics);
  string getHeaderLine();
  string getTruthTable();
  string getBodyLine();

  bool load(string path);

  int getIPinsSize();
  vector<Device *> getIPins();
  vector<Device *> getOPins();
  bool getFileloadSuccess();
};
#endif /* ifndef LogicSimulator */
