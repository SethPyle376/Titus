//
// Created by seth on 9/2/20.
//

#ifndef TITUS_VULKANSHADERMODULEMANAGER_H
#define TITUS_VULKANSHADERMODULEMANAGER_H

#include "VulkanShaderModuleResource.h"

class VulkanDevice;

class VulkanShaderModuleManager {
private:
    VulkanDevice* device;
    std::map<std::string, VulkanShaderModuleResource> resourceMap;
public:
  VulkanShaderModuleManager(VulkanDevice* device);
  VulkanShaderModuleResource* loadShaderModule(const std::string& filePath);
};

#endif //TITUS_VULKANSHADERMODULEMANAGER_H
