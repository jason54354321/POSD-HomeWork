#ifndef DEVICE_H
#define DEVICE_H
#include "LogicState.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Device {
protected:
  vector<Device *> iPins;
  LogicState logic = UNKNOWN;

  bool isAllIPinsSet();

public:
  string name;
  bool isOutputPin = true;

  ~Device();

  void addInputPin(Device *device);

  int getIPinsSize();
  Device *getIPin(int index);

  void setLogicState(LogicState logic);
  void setLogicState(int logic);

  LogicState getLogicState();

  vector<Device *> getAllIPins();

  virtual int calOutput();
};

#endif
