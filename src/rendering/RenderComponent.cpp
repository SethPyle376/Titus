//
// Created by seth on 9/3/20.
//

#include "rendering/RenderComponent.h"
#include "rendering/RenderSubsystem.h"

RenderComponent::RenderComponent() {
  RenderSubsystem::getInstance()->Subsystem<RenderComponent>::registerComponent(this);
}

RenderComponent::~RenderComponent() noexcept {
  RenderSubsystem::getInstance()->Subsystem<RenderComponent>::unregisterComponent(this);
}