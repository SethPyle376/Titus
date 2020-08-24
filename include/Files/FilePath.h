//
// Created by seth on 8/23/20.
//

#ifndef TITUS_FILEPATH_H
#define TITUS_FILEPATH_H

#include <string>

class FilePath {
private:
    std::string filePath;
public:
    FilePath(const std::string& filePath) {
      this->filePath = filePath;
    }

    std::string getFilePath() {
      // Here we'll transform the path to a standardized format?
      return filePath;
    }
};

#endif //TITUS_FILEPATH_H
