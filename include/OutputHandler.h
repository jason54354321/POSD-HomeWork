#ifndef OUTPUTCONVERTER_H
#define OUTPUTCONVERTER_H
#include "Device.h"
#include "DeviceAmount.h"
#include <sstream>
#include <vector>

using namespace std;

class OutputHandler {
private:
  DeviceAmount dAmount;
  vector<Device *> iPins;
  vector<Device *> oPins;

  enum LineIndicator {
    FIRST,
    SECOND,
    THRID,
  };

  void linePrinter(LineIndicator line, int iPinNum, int OPinNum,
                   stringstream &output);

public:
  OutputHandler(DeviceAmount dAmount, vector<Device *> iPins,
                vector<Device *> oPins);

  void set(DeviceAmount dAmount, vector<Device *> iPins,
           vector<Device *> oPins);

  string getHeaderLine();

  string getBodyLine();
};

#endif /*  */
