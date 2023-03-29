#ifndef GateAND_H
#define GateAND_H

#include "Device.h"

class GateAND : public Device {
protected:
public:
  int calOutput() override;
};

#endif /* ifndef GateAND_H */
