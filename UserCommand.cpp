#include <iostream>
#include <regex>
#include <string>
using namespace std;

class UserCommand {
private:
  regex reg;
  string input;
  bool isValidCommand(string input) { return regex_match(input, reg); }

public:
  UserCommand(regex reg) : reg(reg){};
  string waitingInput() {
    while (true) {
      getline(cin, input);

      if (input == "") {
        cout << endl;
        continue;
      }
      if (!isValidCommand(input)) {
        cout << "Wrong command format! \"" << input
             << "\" is not a valid commnad." << endl;
        continue;
      }
      break;
    }
    return input;
  }
};
