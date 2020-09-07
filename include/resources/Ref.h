//
// Created by seth on 8/23/20.
//

#ifndef TITUS_REF_H
#define TITUS_REF_H

#include <string>

#include "resources/ResourceManager.h"

class ResourceManager;

template<class T>
class Ref {
friend class ResourceManager;
private:
    std::string filename;
public:
    T* resource;

    Ref() = default;
    Ref(const std::string& filename, T* resource);
    ~Ref();
};

template<class T>
Ref<T>::Ref(const std::string& filename, T* resource) {
  this->resource = resource;
  this->filename = filename;
}

template<class T>
Ref<T>::~Ref() {
  ResourceManager::getInstance()->deleteReference(this->filename);
}

#endif //TITUS_REF_H
