#include "Fileloader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

void Fileloader::makeFileData(ifstream &file) {
  string lineCommand;
  vector<string> dataArray;

  while (getline(file, lineCommand)) {
    dataArray = spaceSeperator(lineCommand);
    fileData.push_back(dataArray);
  }
}

vector<string> Fileloader::spaceSeperator(string command) {
  vector<string> dataArray;
  stringstream ss(command);
  const char seperator = ' ';
  string data;

  while (getline(ss, data, seperator)) {
    dataArray.push_back(data);
  }
  return dataArray;
}

Fileloader::Fileloader(string path) : path(path) {}

bool Fileloader::load() {
  ifstream file(path);
  if (file.fail()) {
    cout << "File not Found or file format error!!" << endl;
    return false;
  }

  makeFileData(file);

  file.close();
  return true;
}

vector<vector<string>> Fileloader::getFileData() { return fileData; }
