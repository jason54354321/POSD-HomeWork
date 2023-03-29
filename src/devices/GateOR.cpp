#include "GateOR.h"

int GateOR::calOutput() {
  if (!isAllIPinsSet()) {
    return UNKNOWN;
  }

  // 0 won't effect result
  int output = 0;
  for (auto iPin : iPins) {
    output |= iPin->getLogicState();
  }

  this->setLogicState(output);

  return output;
}
