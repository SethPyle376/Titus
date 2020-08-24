//
// Created by seth on 8/24/20.
//

#ifndef TITUS_UNIXFILEDRIVER_H
#define TITUS_UNIXFILEDRIVER_H

#include <vector>
#include <iterator>
#include <fstream>

#include "Files/FileDriver.h"

class UnixFileDriver : public FileDriver {
public:
    void readFile(const FilePath& filePath, char*& dataPointer, int& dataSize) override {
      std::ifstream input(filePath.getFilePath(), std::ios::binary);

      std::vector<char> bytes(
              (std::istreambuf_iterator<char>(input)),
              (std::istreambuf_iterator<char>()));

      dataPointer = bytes.data();
      dataSize = bytes.size();
    }
};

#endif //TITUS_UNIXFILEDRIVER_H
