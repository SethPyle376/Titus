//
// Created by seth on 8/23/20.
//

#ifndef TITUS_FILEPATH_H
#define TITUS_FILEPATH_H

#include <string>
#include <regex>

#include "FileSystemType.h"

class FilePath {
private:
    FileSystemType fsType;
    std::string filePath;

    void processFilePath() {
      this->filePath = std::regex_replace(filePath, std::regex("resources:/"), "./resources/");
      this->filePath = std::regex_replace(filePath, std::regex("User:/"), "./User/");
      this->filePath = std::regex_replace(filePath, std::regex("Config:/"), "./Config/");
    }
public:
    FilePath(const std::string& filePath, FileSystemType fsType) {
      this->fsType = fsType;
      this->filePath = filePath;
      processFilePath();
    }

    std::string getFilePath() const {
      return filePath;
    }
};

#endif //TITUS_FILEPATH_H
