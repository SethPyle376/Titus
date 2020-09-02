//
// Created by seth on 9/2/20.
//

#include "rendering/vulkan/managers/VulkanShaderModuleResource.h"

void VulkanShaderModuleResource::init(VulkanDevice* device, const std::string& filename) {
  File shaderFile = FileSystem::getInstance()->readFile(filename);

  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = shaderFile.data.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderFile.data.data());

  if (vkCreateShaderModule(device->getLogicalDevice(), &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    // todo: error/log
  }
}