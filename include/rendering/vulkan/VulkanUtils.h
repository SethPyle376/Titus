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

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

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

#endif //TITUS_VULKANUTILS_H
