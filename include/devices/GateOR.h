#ifndef GateOR_H
#define GateOR_H

#include "Device.h"

class GateOR : public Device {
public:
  int calOutput() override;
};

#endif /* ifndef GateOR */
