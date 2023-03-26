#include "Device.cpp"

class GateNOT : public Device {
private:
public:
  int calOutput() override {
    if (!isAllIPinsSet()) {
      return UNKNOWN;
    }

    Device *firstIpin = iPins[0];
    int output = firstIpin->getLogicState();
    output = !output;

    this->setLogicState(output);

    return output;
  }
};
