#include "GateAND.h"

int GateAND::calOutput() {
  if (!isAllIPinsSet()) {
    return UNKNOWN;
  }

  // 1 won't effect result
  int output = 1;
  for (auto iPin : iPins) {
    output &= iPin->getLogicState();
  }

  this->setLogicState(output);

  return output;
}
