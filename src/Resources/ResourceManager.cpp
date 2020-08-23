//
// Created by seth on 8/23/20.
//

#include "Resources/ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::getInstance() {
  if (instance == nullptr) {
    instance = new ResourceManager();
  }

  return instance;
}
