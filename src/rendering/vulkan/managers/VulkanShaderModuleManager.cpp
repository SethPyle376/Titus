//
// Created by seth on 9/2/20.
//

#include "rendering/vulkan/managers/VulkanShaderModuleManager.h"

VulkanShaderModuleManager::VulkanShaderModuleManager(VulkanDevice *device) {
  this->device = device;
}

VulkanShaderModuleResource * VulkanShaderModuleManager::loadShaderModule(const std::string& filePath) {
  auto iter = resourceMap.find(filePath);

  if (iter == resourceMap.end()) {
    resourceMap[filePath].init(device, filePath);
  } else {
    return &(resourceMap[filePath]);
  }
}