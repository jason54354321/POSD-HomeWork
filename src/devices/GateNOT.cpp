#include "GateNOT.h"

int GateNOT::calOutput() {
  if (!isAllIPinsSet()) {
    return UNKNOWN;
  }

  int output = iPins[0]->getLogicState();
  output = !output;

  this->setLogicState(output);

  return output;
}
