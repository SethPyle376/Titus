//
// Created by seth on 8/23/20.
//

#ifndef TITUS_FILESYSTEM_H
#define TITUS_FILESYSTEM_H

#include "FileDriver.h"

#include "Drivers/UnixFileDriver.h"
#include "File.h"

class FileSystem {
private:
    FileDriver* driver;
    FileSystemType fsType;
    static FileSystem* instance;
public:
  FileSystem();

  File readFile(std::string filePath);

  static FileSystem* getInstance();
};

#endif //TITUS_FILESYSTEM_H
