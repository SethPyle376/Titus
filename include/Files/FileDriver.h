//
// Created by seth on 8/23/20.
//

#ifndef TITUS_FILEDRIVER_H
#define TITUS_FILEDRIVER_H

#include "FilePath.h"

/*
 * Interface to handle reading files on different operating systems as well as different file strategies
 * I.e. standard file system vs. compressed zip files or whatever
 * FileSystem will contain a FileDriver based on config
 */
class FileDriver {
public:
    virtual void readFile(const FilePath& filePath, char*& dataPointer, int& dataSize) = 0;
};

#endif //TITUS_FILEDRIVER_H
