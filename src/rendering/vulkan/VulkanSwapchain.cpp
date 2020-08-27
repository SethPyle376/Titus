//
// Created by seth on 8/27/20.
//

#include "rendering/vulkan/VulkanSwapchain.h"

VulkanSwapchain::VulkanSwapchain(VkInstance instance) {
  this->instance = instance;
}

void VulkanSwapchain::initSurface(SDL_Window *window) {
  if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
    // TODO: log/error
  } else {
    // TODO: log
  }
}

VkSurfaceKHR VulkanSwapchain::getSurface() {
  return surface;
}

void VulkanSwapchain::connect(VkPhysicalDevice physicalDevice, VkDevice device) {
  this->physicalDevice = physicalDevice;
  this->device = device;
}

