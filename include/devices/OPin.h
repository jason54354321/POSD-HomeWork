#ifndef OPin_H
#define OPin_H
#include "Device.h"

class OPin : public Device {
public:
  int calOutput() override;
};

#endif /* ifndef OPin_H */
