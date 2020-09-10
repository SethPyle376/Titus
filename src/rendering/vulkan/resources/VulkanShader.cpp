//
// Created by seth on 9/7/20.
//


#include "rendering/vulkan/resources/VulkanShader.h"
#include "rendering/vulkan/VulkanRenderer.h"

VulkanShader::VulkanShader() {}

void VulkanShader::init(const std::string &filename) {
  shaderData = FileSystem::getInstance()->readFile(filename);

  auto* renderer = (VulkanRenderer*)RenderSubsystem::getInstance()->getRenderer();

  VkShaderModuleCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = shaderData.data.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderData.data.data());

  if (vkCreateShaderModule(renderer->getDevice()->getLogicalDevice(), &createInfo, nullptr, &(this->shaderModule)) != VK_SUCCESS) {
    // TODO: error/log
  } else {
    std::cout << "COMPILED SHADER: " << filename << std::endl;
    std::cout << "SHADER LENGTH: " << shaderData.data.size() << std::endl;
  }
}
