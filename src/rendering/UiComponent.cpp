//
// Created by seth on 9/3/20.
//

#include "rendering/UiComponent.h"
#include "rendering/RenderSubsystem.h"

UiComponent::UiComponent() {
  RenderSubsystem::getInstance()->Subsystem<UiComponent>::registerComponent(this);
}

UiComponent::~UiComponent() noexcept {
  RenderSubsystem::getInstance()->Subsystem<UiComponent>::unregisterComponent(this);
}