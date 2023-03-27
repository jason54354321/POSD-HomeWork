#ifndef DEVICE_H
#define DEVICE_H
#include "../LogicState.cpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Device {
protected:
  vector<Device *> iPins;
  LogicState logicState = UNKNOWN;

  bool isAllIPinsSet();

public:
  string name;
  bool isOutputPin = true;

  void addInputPin(Device *device) { iPins.push_back(device); }

  int getIPinsSize() { return iPins.size(); }
  Device *getIPin(int index) { return iPins[index]; }

  void setLogicState(LogicState logic) { logicState = logic; }
  void setLogicState(int logic);

  LogicState getLogicState() { return logicState; }

  vector<Device *> getAllIPins() { return iPins; }

  virtual int calOutput() { return -1; };
};

bool Device::isAllIPinsSet() {
  for (auto iPin : iPins) {
    if (iPin->getLogicState() == UNKNOWN) {
      cout << "SomeIpin is UNKNOWN";
      return false;
    }
  }
  return true;
}

void Device::setLogicState(int logic) {
  if (logic == 1) {
    logicState = HIGH;
  } else if (logic == 0) {
    logicState = LOW;
  }
}

#endif
