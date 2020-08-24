//
// Created by seth on 8/23/20.
//

#ifndef TITUS_RESOURCEMANAGER_H
#define TITUS_RESOURCEMANAGER_H

#include <map>
#include <string>
#include <iostream>

#include "Resources/Resource.h"
#include "Resources/TestResource.h"

template<class T>
class Ref;

class ResourceManager {
private:
  static ResourceManager *instance;
  std::map<std::string, Resource*> resourceRegistry;
  std::map<std::string, int> resourceRefMap;

public:
    static ResourceManager* getInstance();

  template<class T>
  Ref<T> getResource(const std::string& filename) {
    auto it = resourceRegistry.find(filename);

    // TODO: need to handle cases where Resource isn't base of T

    resourceRefMap[filename]++;

    if (it == resourceRegistry.end()) {
      Resource* resourceBase = new T();
      resourceBase->init(filename);
      T* castedResource =  dynamic_cast<T*>(resourceBase);
      resourceRegistry[filename] = castedResource;
      return Ref<T>(filename, castedResource);
    }

    T* resource = dynamic_cast<T*>(it->second);
    return Ref<T>(filename, resource);
  }

  void deleteReference(const std::string& filename) {
    resourceRefMap[filename]--;

    if (resourceRefMap[filename] <= 0) {
      delete resourceRegistry[filename];
      resourceRegistry.erase(filename);
      resourceRefMap.erase(filename);
    }
  }

};

#endif //TITUS_RESOURCEMANAGER_H
