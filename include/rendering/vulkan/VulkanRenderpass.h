//
// Created by seth on 9/21/20.
//

#ifndef TITUS_VULKANRENDERPASS_H
#define TITUS_VULKANRENDERPASS_H

#include "volk.h"

class VulkanDevice;

class VulkanRenderpass {
private:
    VulkanDevice* device;
    VkRenderPass renderPass;
public:
    VulkanRenderpass(VulkanDevice* device, VkFormat swapchainImageFormat);
};

#endif //TITUS_VULKANRENDERPASS_H
