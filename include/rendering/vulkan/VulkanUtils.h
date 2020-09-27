//
// Created by seth on 8/27/20.
//

#ifndef TITUS_VULKANUTILS_H
#define TITUS_VULKANUTILS_H

#include <vector>
#include <optional>
#include <set>
#include <string>

#include "volk.h"

#define VULKAN_NUM_DESCRIPTOR_SETS 8
#define VULKAN_NUM_DESCRIPTOR_BINDINGS 16

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> computeFamily;
    std::optional<uint32_t> transferFamily;

    bool isComplete() {
      return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

bool isDeviceSuitable(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, std::vector<const char*> deviceExtensions);
bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char *> deviceExtensions);
QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR vkSurface);
SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
uint32_t getQueueFamilyIndex(VkQueueFlagBits queueFlags, std::vector<VkQueueFamilyProperties> queueFamilyProperties);

#endif //TITUS_VULKANUTILS_H
