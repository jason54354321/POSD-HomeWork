#include "Device.h"
#include "LogicState.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool Device::isAllIPinsSet() {
  for (auto iPin : iPins) {
    if (iPin->getLogicState() == UNKNOWN) {
      return false;
    }
  }
  return true;
}

Device::~Device() {
  cout << "device:" << name << " has been deconstruct" << endl;
}

void Device::addInputPin(Device *device) { iPins.push_back(device); }

int Device::getIPinsSize() { return iPins.size(); }
Device *Device::getIPin(int index) { return iPins[index]; }

void Device::setLogicState(LogicState logic) { logicState = logic; }
void Device::setLogicState(int logic) {
  if (logic == 1) {
    logicState = HIGH;
  } else if (logic == 0) {
    logicState = LOW;
  }
}

LogicState Device::getLogicState() { return logicState; }

vector<Device *> Device::getAllIPins() { return iPins; }

int Device::calOutput() { return -1; };
