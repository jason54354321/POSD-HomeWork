#ifndef UserCommand_H
#define UserCommand_H

#include <gtest/gtest_prod.h>
#include <iostream>
#include <regex>
#include <string>
using namespace std;

class UserCommand {
private:
  regex filterRegex;
  bool isValidCommand(string input);
  virtual string waitInput();
  void displayWarningMsg(string input);

public:
  UserCommand(regex reg);

  string getUserInput();
};

#endif /* ifndef UserCommand_H */
