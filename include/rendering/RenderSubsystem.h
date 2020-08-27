//
// Created by seth on 8/26/20.
//

#ifndef TITUS_RENDERSUBSYSTEM_H
#define TITUS_RENDERSUBSYSTEM_H



#include <rendering/vulkan/VulkanRenderer.h>

#include "core/Subsystem.h"
#include "RenderComponent.h"
#include "Renderer.h"

class RenderSubsystem : public Subsystem<RenderComponent> {
private:
    static RenderSubsystem* instance;
    SDL_Window* window;
    Renderer* renderer;
public:
    static RenderSubsystem* getInstance();
    RenderSubsystem();

    void initWindow();

    void update(float delta) override {}
};

#endif //TITUS_RENDERSUBSYSTEM_H
