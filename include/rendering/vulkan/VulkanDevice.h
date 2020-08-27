//
// Created by seth on 8/26/20.
//

#ifndef TITUS_VULKANDEVICE_H
#define TITUS_VULKANDEVICE_H

#include <vector>

#include "volk.h"
#include "VulkanSwapchain.h"
#include "VulkanUtils.h"

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class VulkanDevice {
private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;

    VulkanSwapchain* swapchain;

    void pickPhysicalDevice();
public:
    VulkanDevice(VkInstance instance, VulkanSwapchain* swapchain);
};

#endif //TITUS_VULKANDEVICE_H
