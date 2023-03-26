#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
class Fileloader {
private:
  string path;
  vector<vector<string>> fileData;

  void makeFileData(ifstream &file) {
    string lineCommand;
    vector<string> dataArray;

    while (getline(file, lineCommand)) {
      dataArray = spaceSeperator(lineCommand);
      fileData.push_back(dataArray);
    }
  }

  vector<string> spaceSeperator(string command) {
    vector<string> dataArray;
    stringstream ss(command);
    const char seperator = ' ';
    string data;

    while (getline(ss, data, seperator)) {
      dataArray.push_back(data);
    }
    return dataArray;
  }

public:
  Fileloader(string path) : path(path) {}

  bool load() {
    ifstream file(path);
    if (file.fail()) {
      cout << "File not Found or file format error!!" << endl;
      return false;
    }

    makeFileData(file);

    file.close();
    return true;
  }

  void showFileData(vector<vector<string>> fileData) {
    for (int i = 0; i < fileData.size(); i++) {
      for (int j = 0; j < fileData[i].size(); j++) {
        cout << i << "," << j << ":" << fileData[i][j] << endl;
      }
    }
  }

  vector<vector<string>> getFileData() { return fileData; }
};
