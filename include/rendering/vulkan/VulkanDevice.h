//
// Created by seth on 8/26/20.
//

#ifndef TITUS_VULKANDEVICE_H
#define TITUS_VULKANDEVICE_H

#include "volk.h"

class VulkanDevice {
private:
    VkInstance instance;
    VkPhysicalDevice physicalDevice;
    VkDevice logicalDevice;
public:
    VulkanDevice(VkInstance instance);
};

#endif //TITUS_VULKANDEVICE_H
