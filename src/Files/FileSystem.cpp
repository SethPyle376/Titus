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

File FileSystem::readFile(std::string filePath) {
  FilePath path(filePath, fsType);

  File newFile{nullptr, 0};

  driver->readFile(path, newFile.data, newFile.dataSize);

  return newFile;
}