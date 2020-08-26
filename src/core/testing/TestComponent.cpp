//
// Created by seth on 8/26/20.
//

#include "core/testing/TestComponent.h"
#include "core/testing/TestSubsystem.h"

TestComponent::TestComponent() {
  TestSubsystem::getInstance()->registerComponent(this);
}

TestComponent::~TestComponent() {
  TestSubsystem::getInstance()->unregisterComponent(this);
}