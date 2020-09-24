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
  processLayout();
}

void VulkanShader::processLayout() {
  layout = ShaderResourceLayout{};
  spirv_cross::Compiler compiler((uint32_t*)shaderData.data.data(), shaderData.data.size() / sizeof(uint32_t));
  auto resources = compiler.get_shader_resources();

  for (auto &buffer : resources.uniform_buffers) {
    auto set = compiler.get_decoration(buffer.id, spv::DecorationDescriptorSet);
    auto binding = compiler.get_decoration(buffer.id, spv::DecorationBinding);
    layout.sets[set].uniform_buffer_mask |= 1u << binding;
  }

  if (!resources.push_constant_buffers.empty()) {
    layout.pushConstantSize = compiler.get_declared_struct_size(compiler.get_type(resources.push_constant_buffers.front().base_type_id));
  }

  return;
}