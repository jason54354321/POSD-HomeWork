#ifndef OUTPUTCONVERTER_H
#define OUTPUTCONVERTER_H
#include "DeviceAmount.cpp"
#include "devices/Device.cpp"
#include <sstream>
#include <vector>

using namespace std;

class OutputHandler {
private:
  DeviceAmount deviceAmount;
  vector<Device *> iPins;
  vector<Device *> oPins;

public:
  OutputHandler(DeviceAmount dAmount, vector<Device *> iPins,
                vector<Device *> oPins)
      : deviceAmount(dAmount), iPins(iPins), oPins(oPins){};

  void set(DeviceAmount dAmount, vector<Device *> iPins,
           vector<Device *> oPins) {
    this->deviceAmount = dAmount;
    this->iPins = iPins;
    this->oPins = oPins;
  }

  string getHeaderLine() {
    stringstream output;
    output << "i i i | o";
    output << endl;
    for (int n = 1; n <= deviceAmount.iPinsAmount; n++) {
      output << n << " ";
    }
    output << "| ";
    for (int n = 1; n <= deviceAmount.oPinsAmount; n++) {
      output << n << " ";
    }
    output << endl;
    output << "------+--";
    output << endl;

    return output.str();
  }

  string getBodyLine() {
    stringstream output;
    for (auto iPin : iPins) {
      output << iPin->getLogicState() << " ";
    }
    output << "| ";
    for (auto oPin : oPins) {
      output << oPin->getLogicState() << " ";
    }
    output << endl;

    return output.str();
  }
};

#endif /*  */
