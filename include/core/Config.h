//
// Created by seth on 9/9/20.
//

#ifndef TITUS_CONFIG_H
#define TITUS_CONFIG_H

#include "nlohmann/json.hpp"

#include "files/FileSystem.h"

class Config {
public:
    static void load(const std::string& filename);
    static nlohmann::json globalConfig;
};

#endif //TITUS_CONFIG_H
