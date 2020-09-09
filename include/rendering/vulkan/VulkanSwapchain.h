//
// Created by seth on 8/27/20.
//

#ifndef TITUS_VULKANSWAPCHAIN_H
#define TITUS_VULKANSWAPCHAIN_H

#include <vector>

#include "SDL2/SDL_video.h"
#include "SDL2/SDL_vulkan.h"
#include "volk.h"

class VulkanDevice;

class VulkanSwapchain {
private:
    VkInstance instance;
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    VkSurfaceKHR surface;

    SDL_Window* window;

    VulkanDevice* device;

    VkFormat colorFormat;
    VkColorSpaceKHR colorSpace;

    VkExtent2D swapchainExtent;

    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> swapchainImageViews;

    void selectColors();
    void createImageViews();
public:
    VulkanSwapchain(VkInstance instance);
    ~VulkanSwapchain();
    void initSurface(SDL_Window* window);
    void connect(VulkanDevice* device);
    VkSurfaceKHR getSurface();
    void createSwapchain(bool useVSync = false);
};

#endif //TITUS_VULKANSWAPCHAIN_H
