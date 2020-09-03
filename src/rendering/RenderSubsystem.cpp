//
// Created by seth on 8/26/20.
//

#include "rendering/RenderSubsystem.h"

RenderSubsystem* RenderSubsystem::instance = nullptr;

RenderSubsystem* RenderSubsystem::getInstance() {
  if (instance == nullptr) {
    instance = new RenderSubsystem();
  }

  return instance;
}

RenderSubsystem::RenderSubsystem() {
  initWindow();
  renderer = new VulkanRenderer(window);
}

void RenderSubsystem::initWindow() {
  uint32_t windowFlags = SDL_WINDOW_VULKAN;
  window = SDL_CreateWindow("TITUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            1080, 720, windowFlags);
}

void RenderSubsystem::update(float delta) {
  for (auto component : this->Subsystem<RenderComponent>::components) {
    std::cout << "FOUND RENDER COMPONENT" << std::endl;
  }

  for (auto component : this->Subsystem<UiComponent>::components) {
    std::cout << "FOUND UI COMPONENT" << std::endl;
  }
}
