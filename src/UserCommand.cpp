#include "UserCommand.h"
#include <iostream>
#include <regex>
#include <string>
#include <system_error>
using namespace std;

UserCommand::UserCommand() {}
UserCommand::UserCommand(regex reg) : reg(reg) {}

string UserCommand::waitInput() {
  string result;
  getline(cin, result);
  return result;
}

bool UserCommand::isValidCommand(string input) {
  return regex_match(input, reg);
}

void UserCommand::displayWarningMsg(string input) {
  cout << "Wrong command format! \"" << input << "\" is not a valid commnad."
       << endl;
}

string UserCommand::getUserInput() {
  string input;
  while (true) {
    input = waitInput();

    if (input == "") {
      continue;
    }
    if (!isValidCommand(input)) {
      displayWarningMsg(input);
      continue;
    }
    break;
  }
  return input;
}
