#include "StringParser.h"
#include "DeviceAmount.h"

#include <sstream>
#include <vector>

using namespace std;

DeviceAmount dAmount;
vector<Device *> iPins;
vector<Device *> oPins;

enum LineIndicator {
  FIRST,
  SECOND,
  THRID,
};

void StringParser::linePrinter(LineIndicator line, int iPinNum, int OPinNum,
                               stringstream &output) {
  for (int n = 1; n <= iPinNum; n++) {
    if (line == FIRST) {
      output << "i ";
    } else if (line == SECOND) {
      output << n << " ";
    } else if (line == THRID) {
      output << "--";
    }
  }

  line == THRID ? output << "+" : output << "| ";

  for (int n = 1; n <= OPinNum; n++) {
    if (line == FIRST) {
      output << "o ";
    } else if (line == SECOND) {
      output << n << " ";
    } else if (line == THRID) {
      output << "--";
    }
  }

  output << "\n";
}

StringParser::StringParser(DeviceAmount dAmount, vector<Device *> iPins,
                           vector<Device *> oPins)
    : dAmount(dAmount), iPins(iPins), oPins(oPins){};

void StringParser::set(DeviceAmount dAmount, vector<Device *> iPins,
                       vector<Device *> oPins) {
  this->dAmount = dAmount;
  this->iPins = iPins;
  this->oPins = oPins;
}

string StringParser::getHeaderLine() {
  stringstream output;
  linePrinter(FIRST, dAmount.iPinsAmount, dAmount.oPinsAmount, output);
  linePrinter(SECOND, dAmount.iPinsAmount, dAmount.oPinsAmount, output);
  linePrinter(THRID, dAmount.iPinsAmount, dAmount.oPinsAmount, output);

  return output.str();
}

string StringParser::getBodyLine() {
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
