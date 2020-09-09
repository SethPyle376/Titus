//
// Created by seth on 8/26/20.
//

#ifndef TITUS_RENDERSUBSYSTEM_H
#define TITUS_RENDERSUBSYSTEM_H

#include <iostream>

#include <rendering/vulkan/VulkanRenderer.h>
#include <rendering/UiComponent.h>

#include "core/Subsystem.h"
#include "RenderComponent.h"
#include "Renderer.h"

class RenderSubsystem : public Subsystem<RenderComponent>, public Subsystem<UiComponent> {
    friend Subsystem<RenderComponent>;
private:
    static RenderSubsystem* instance;
    SDL_Window* window;
    Renderer* renderer;
public:
    static RenderSubsystem* getInstance();
    RenderSubsystem();

    void initWindow();

    void update(float delta) override;

    void onComponentRegistered(RenderComponent *component) override {
      std::cout << "RENDER COMPOMENT REGISTERED WITH RENDER SUBSYSTEM" << std::endl;
    }

    void onComponentRegistered(UiComponent *component) override {
      std::cout << "UI COMPONENT REGISTERED WITH RENDER SUBSYSTEM" << std::endl;
    }

    void onComponentUnregistered(RenderComponent *component) override {
      std::cout << "RENDER COMPOMENT UNREGISTERED WITH RENDER SUBSYSTEM" << std::endl;
    }

    void onComponentUnregistered(UiComponent *component) override {
      std::cout << "RENDER COMPONENT UNREGISTERED WITH RENDER SUBSYSTEM" << std::endl;
    }

    Renderer* getRenderer() {
      return renderer;
    }
};

#endif //TITUS_RENDERSUBSYSTEM_H
