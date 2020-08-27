//
// Created by seth on 8/27/20.
//

#ifndef TITUS_VULKANSWAPCHAIN_H
#define TITUS_VULKANSWAPCHAIN_H

#include "SDL2/SDL_video.h"
#include "SDL2/SDL_vulkan.h"
#include "volk.h"

class VulkanSwapchain {
private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkSwapchainKHR swapchain;
    VkSurfaceKHR surface;

public:
    VulkanSwapchain(VkInstance instance);
    void initSurface(SDL_Window* window);
    void connect(VkPhysicalDevice physicalDevice, VkDevice device);
    VkSurfaceKHR getSurface();
};

#endif //TITUS_VULKANSWAPCHAIN_H
