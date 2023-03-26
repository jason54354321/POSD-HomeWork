#include "Device.cpp"

class GateOR : public Device {
private:
public:
  int calOutput() override {
    if (!isAllIPinsSet()) {
      return UNKNOWN;
    }

    Device *firstIpin = iPins[0];
    int output = firstIpin->getLogicState();
    for (auto iPin : iPins) {
      cout << "iPin->name:" << iPin->name << endl;
      output |= iPin->getLogicState();
    }

    setLogicState(output);

    return output;
  }
};
