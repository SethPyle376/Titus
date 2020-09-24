//
// Created by seth on 9/7/20.
//

#include "rendering/vulkan/resources/VulkanMaterial.h"

void VulkanMaterial::init(const std::string &filename) {
  std::string materialFile = FileSystem::getInstance()->readFileToString(filename);

  auto json = nlohmann::json::parse(materialFile);

  this->name = json["name"].get<std::string>();
  this->vertexShader = ResourceManager::getInstance()->getResource<VulkanShader>(json["vertexShader"].get<std::string>());
  this->fragmentShader = ResourceManager::getInstance()->getResource<VulkanShader>(json["fragmentShader"].get<std::string>());

  void* vertexShaderData = vertexShader->resource->shaderData.data.data();
  int vertexShaderSize = vertexShader->resource->shaderData.data.size();

  void* fragmentShaderData = fragmentShader->resource->shaderData.data.data();
  int fragmentShaderSize = fragmentShader->resource->shaderData.data.size();

  spirv_cross::Compiler compiler((uint32_t*)vertexShaderData, vertexShaderSize / sizeof(uint32_t));
  auto resources = compiler.get_shader_resources();

  for (auto &buffer : resources.uniform_buffers) {
    auto set = compiler.get_decoration(buffer.id, spv::DecorationDescriptorSet);
    auto binding = compiler.get_decoration(buffer.id, spv::DecorationBinding);

  }

  return;
}

void VulkanMaterial::destroy() {
  delete vertexShader;
  delete fragmentShader;
}
