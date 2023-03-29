#ifndef Fileloader_H
#define Fileloader_H

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

  void makeFileData(ifstream &file);

  vector<string> spaceSeperator(string command);

public:
  Fileloader(string path);

  bool load();

  vector<vector<string>> getFileData();
};

#endif /* ifndef Fileloader_H */
