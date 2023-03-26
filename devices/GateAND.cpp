#include "Device.cpp"

class GateAND : public Device {
private:
public:
  int calOutput() override {
    if (!isAllIPinsSet()) {
      return UNKNOWN;
    }

    Device *firstIpin = iPins[0];
    int output = firstIpin->getLogicState();
    for (auto iPin : iPins) {
      output &= iPin->getLogicState();
    }

    this->setLogicState(output);

    return output;
  }
};
