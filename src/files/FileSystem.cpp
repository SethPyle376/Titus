//
// Created by seth on 8/24/20.
//

#include "files/FileSystem.h"

FileSystem* FileSystem::instance = nullptr;

FileSystem* FileSystem::getInstance() {
  if (instance == nullptr) {
    instance = new FileSystem();
  }

  return instance;
}

FileSystem::FileSystem() {
  this->fsType = FileSystemType::UNIX;
  this->driver = new UnixFileDriver();
}

File FileSystem::readFile(const std::string& filePath) {
  FilePath path(filePath, fsType);

  File newFile;

  newFile.data = driver->readFile(path);

  return newFile;
}

std::string FileSystem::readFileToString(const std::string &filepath) {
  std::vector<char> data = this->readFile(filepath).data;
  std::string dataString(data.data(), data.size());
  return dataString;
}
