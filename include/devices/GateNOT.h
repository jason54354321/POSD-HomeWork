#ifndef GateNOT_H
#define GateNOT_H

#include "Device.h"

class GateNOT : public Device {
public:
  int calOutput() override;
};

#endif
