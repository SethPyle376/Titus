//
// Created by seth on 8/24/20.
//

#include "Files/FileSystem.h"

FileSystem* FileSystem::instance = nullptr;

FileSystem* FileSystem::getInstance() {
  if (instance == nullptr) {
    instance = new FileSystem();
  }

  return instance;
}

FileSystem::FileSystem() {
#ifdef __linux__
  this->fsType = FileSystemType::UNIX;
  this->driver = new UnixFileDriver();
#endif
}

File FileSystem::readFile(const std::string& filePath) {
  FilePath path(filePath, fsType);

  File newFile;

  newFile.data = driver->readFile(path);

  return newFile;
}

std::string FileSystem::readFileToString(const std::string &filepath) {
  return std::string(this->readFile(filepath).data.data());
}
