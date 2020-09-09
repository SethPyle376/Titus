//
// Created by seth on 9/9/20.
//

#include "core/Config.h"

nlohmann::json Config::globalConfig = nlohmann::json();

void Config::load(const std::string &filename) {
  std::string configContents = FileSystem::getInstance()->readFileToString(filename);

  globalConfig = nlohmann::json::parse(configContents);
}
