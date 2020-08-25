//
// Created by seth on 8/23/20.
//

#include <resources/TestResource.h>

void TestResource::init(std::string filename) {
  this->path = filename;
  std::cout << "LOADING TEST RESOURCE" << std::endl;
}

void TestResource::destroy() {
  std::cout << "DESTROYING TEST RESOURCE";
}

