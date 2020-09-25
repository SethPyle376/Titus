//
// Created by seth on 8/26/20.
//

#ifndef TITUS_VULKANDEVICE_H
#define TITUS_VULKANDEVICE_H

#include <vector>

#include "volk.h"
#include "VulkanSwapchain.h"
#include "VulkanUtils.h"
#include "managers/VulkanShaderModuleManager.h"

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class VulkanMaterial;

class VulkanDevice {
private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;

    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;


    QueueFamilyIndices queueFamilyIndices;
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;

    VkQueueFlags requestedQueueFlags;

    VulkanSwapchain* swapchain;

    void pickPhysicalDevice();
    void initLogicalDevice();
public:
    VulkanDevice(VkInstance instance, VulkanSwapchain* swapchain, VkQueueFlags requestedQueueFlags);

    VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }
    VkDevice getLogicalDevice() { return logicalDevice; }

    void bakeMaterial(VulkanMaterial* material);
};

#endif //TITUS_VULKANDEVICE_H
