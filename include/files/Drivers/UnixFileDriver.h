//
// Created by seth on 8/24/20.
//

#ifndef TITUS_UNIXFILEDRIVER_H
#define TITUS_UNIXFILEDRIVER_H

#include <vector>
#include <iterator>
#include <fstream>

#include "files/FileDriver.h"

class UnixFileDriver : public FileDriver {
public:
    std::vector<char> readFile(const FilePath& filePath) override {
      std::ifstream input(filePath.getFilePath(), std::ios::binary);

      std::vector<char> data(
              (std::istreambuf_iterator<char>(input)),
              (std::istreambuf_iterator<char>()));

      input.close();

      return data;
    }
};

#endif //TITUS_UNIXFILEDRIVER_H
