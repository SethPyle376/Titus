//
// Created by seth on 8/26/20.
//

#include "core/testing/TestSubsystem.h"

TestSubsystem* TestSubsystem::instance = nullptr;

TestSubsystem *TestSubsystem::getInstance() {
  if (instance == nullptr) {
    instance = new TestSubsystem();
  }

  return instance;
}