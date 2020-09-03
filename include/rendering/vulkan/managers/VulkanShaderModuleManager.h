//
// Created by seth on 9/2/20.
//

#ifndef TITUS_VULKANSHADERMODULEMANAGER_H
#define TITUS_VULKANSHADERMODULEMANAGER_H

#include <map>

#include "VulkanShaderModuleResource.h"

class VulkanDevice;

class VulkanShaderModuleManager {
private:
    VulkanDevice* device;
public:
  VulkanShaderModuleManager(VulkanDevice* device);
};

#endif //TITUS_VULKANSHADERMODULEMANAGER_H
