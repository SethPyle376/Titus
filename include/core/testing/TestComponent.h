//
// Created by seth on 8/25/20.
//

#ifndef TITUS_TESTCOMPONENT_H
#define TITUS_TESTCOMPONENT_H

#include <string>
#include <core/Component.h>

class TestComponent : public Component {
public:
    TestComponent();
    ~TestComponent();
    std::string testString = "Hello world!";
};

#endif //TITUS_TESTCOMPONENT_H
