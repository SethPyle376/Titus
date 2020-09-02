//
// Created by seth on 9/2/20.
//

#ifndef TITUS_VULKANSHADERMODULERESOURCE_H
#define TITUS_VULKANSHADERMODULERESOURCE_H

#include <rendering/vulkan/VulkanDevice.h>
#include "files/FileSystem.h"
#include "volk.h"

class VulkanShaderModuleResource {
public:
    void init(VulkanDevice* device, const std::string& filename);
    VkShaderModule shaderModule;
};

#endif //TITUS_VULKANSHADERMODULERESOURCE_H
