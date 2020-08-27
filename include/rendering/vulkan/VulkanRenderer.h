//
// Created by seth on 8/26/20.
//

#ifndef TITUS_VULKANRENDERER_H
#define TITUS_VULKANRENDERER_H

#include <vector>

#include "volk.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_vulkan.h"

#include <rendering/Renderer.h>

const std::vector<const char *> validationLayers = {
        "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;

class VulkanRenderer : public Renderer {
private:
  #ifdef NDEBUG
    const bool enableValidationLayers = false;
    std::vector<const char*> extensions;
  #else
    const bool enableValidationLayers = true;
    std::vector<const char*> extensions = {VK_EXT_DEBUG_REPORT_EXTENSION_NAME};
  #endif

  SDL_Window* window;
  VkInstance instance;

  void loadInstance();
  bool checkValidationLayerSupport();

public:
    VulkanRenderer(SDL_Window* window);
};

#endif //TITUS_VULKANRENDERER_H
