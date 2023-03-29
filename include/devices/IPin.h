#ifndef IPin_H
#define IPin_H

#include "Device.h"
#include <gtest/gtest_prod.h>
class IPin : public Device {
private:
  FRIEND_TEST(IPinTest, SetterGetter);

public:
  int calOutput() override;
};

#endif /* ifndef IPin_H */
