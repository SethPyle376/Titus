//
// Created by seth on 8/26/20.
//

#ifndef TITUS_VULKANDEVICE_H
#define TITUS_VULKANDEVICE_H

#include <vector>
#include <map>

#include "volk.h"
#include "VulkanSwapchain.h"
#include "VulkanUtils.h"
#include "utils/Hasher.h"

const std::vector<const char *> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class VulkanMaterial;
class VulkanPipelineLayout;
class CombinedResourceLayout;

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

    std::map<uint64_t, VulkanPipelineLayout*> pipelineLayouts;

    void pickPhysicalDevice();
    void initLogicalDevice();

    VulkanPipelineLayout* requestPipelineLayout(const CombinedResourceLayout& resourceLayout);
public:
    VulkanDevice(VkInstance instance, VulkanSwapchain* swapchain, VkQueueFlags requestedQueueFlags);

    VkPhysicalDevice getPhysicalDevice() { return physicalDevice; }
    VkDevice getLogicalDevice() { return logicalDevice; }

    void bakeMaterial(VulkanMaterial* material);
};

#endif //TITUS_VULKANDEVICE_H
