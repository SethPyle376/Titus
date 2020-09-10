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

  SpvReflectShaderModule vertexModule;
  SpvReflectShaderModule fragmentModule;

  void* vertexShaderData = vertexShader->resource->shaderData.data.data();
  int vertexShaderSize = vertexShader->resource->shaderData.data.size();

  SpvReflectResult result = spvReflectCreateShaderModule(vertexShaderSize, vertexShaderData, &vertexModule);

  if (result != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS) {
    // TODO: error/log
  }
}

void VulkanMaterial::destroy() {
  delete vertexShader;
  delete fragmentShader;
}
