//
// Created by seth on 8/23/20.
//

#ifndef TITUS_TESTRESOURCE_H
#define TITUS_TESTRESOURCE_H

#include <iostream>

#include "resources/Resource.h"

class TestResource : public Resource {
public:
    ~TestResource() override {
      std::cout << "DELETING TEST RESOURCE" << std::endl;
    }
    void init(const std::string& filename) override;
    void destroy() override;
};

#endif //TITUS_TESTRESOURCE_H
