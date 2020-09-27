//
// Created by seth on 9/7/20.
//

#include "rendering/vulkan/resources/VulkanMaterial.h"
#include "rendering/vulkan/VulkanPipelineLayout.h"

void VulkanMaterial::init(const std::string &filename) {
  std::string materialFile = FileSystem::getInstance()->readFileToString(filename);

  auto json = nlohmann::json::parse(materialFile);

  this->name = json["name"].get<std::string>();
  this->shaders[ShaderStage::Vertex] = ResourceManager::getInstance()->getResource<VulkanShader>(json["vertexShader"].get<std::string>());
  this->shaders[ShaderStage::Fragment] = ResourceManager::getInstance()->getResource<VulkanShader>(json["fragmentShader"].get<std::string>());

  VulkanRenderer* renderer = (VulkanRenderer*)RenderSubsystem::getInstance()->getRenderer();
  renderer->getDevice()->bakeMaterial(this);
  return;
}

void VulkanMaterial::destroy() {
  for (int i = 0; i < ShaderStage::Count; i++) {
    if (shaders[i])
      delete shaders[i];
  }
}

Ref<VulkanShader> *VulkanMaterial::getShader(ShaderStage stage) {
  return shaders[stage];
}

void VulkanMaterial::setPipelineLayout(VulkanPipelineLayout *pipelineLayout) {
  this->pipelineLayout = pipelineLayout;
}

