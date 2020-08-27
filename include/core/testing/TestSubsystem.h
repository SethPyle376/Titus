//
// Created by seth on 8/25/20.
//

#ifndef TITUS_TESTSUBSYSTEM_H
#define TITUS_TESTSUBSYSTEM_H

#include <iostream>
#include "core/Subsystem.h"
#include "TestComponent.h"

class TestSubsystem : public Subsystem<TestComponent> {
private:
    static TestSubsystem* instance;
public:
    static TestSubsystem* getInstance();

    void update(float delta) override {
      for (TestComponent* component : this->components) {
        std::cout << component->testString << std::endl;
      }
    }
};



#endif //TITUS_TESTSUBSYSTEM_H
