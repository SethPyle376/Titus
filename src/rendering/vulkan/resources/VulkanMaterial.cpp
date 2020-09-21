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

  void* fragmentShaderData = fragmentShader->resource->shaderData.data.data();
  int fragmentShaderSize = fragmentShader->resource->shaderData.data.size();

  SpvReflectResult vertResult = spvReflectCreateShaderModule(vertexShaderSize, vertexShaderData, &vertexModule);
  SpvReflectResult fragResult = spvReflectCreateShaderModule(fragmentShaderSize, fragmentShaderData, &fragmentModule);

  if (vertResult != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS || fragResult != SpvReflectResult::SPV_REFLECT_RESULT_SUCCESS) {
    // TODO: error/log
  }

  uint32_t vertDescriptorSetCount = 0;
  spvReflectEnumerateDescriptorSets(&vertexModule, &vertDescriptorSetCount, NULL);

  std::vector<SpvReflectDescriptorSet*> sets(vertDescriptorSetCount);
  spvReflectEnumerateDescriptorSets(&vertexModule, &vertDescriptorSetCount, sets.data());

  std::vector<DescriptorSetLayoutData> setLayouts(sets.size(), DescriptorSetLayoutData{});

  for (int i = 0; i < sets.size(); i++) {
    const SpvReflectDescriptorSet set = *(sets[i]);
    setLayouts[i].bindings.resize(set.binding_count);
    for (int j = 0; j < set.binding_count; j++) {
      const SpvReflectDescriptorBinding binding = *(set.bindings[j]);
      VkDescriptorSetLayoutBinding& layoutBinding = setLayouts[i].bindings[j];
      layoutBinding.binding = binding.binding;
      layoutBinding.descriptorType = static_cast<VkDescriptorType>(binding.descriptor_type);
      layoutBinding.descriptorCount = 1;
      for (int k = 0; k < binding.array.dims_count; k++) {
        layoutBinding.descriptorCount *= binding.array.dims[k];
      }
      layoutBinding.stageFlags = static_cast<VkShaderStageFlagBits>(vertexModule.shader_stage);
    }
    setLayouts[i].setNumber = set.set;
    setLayouts[i].createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    setLayouts[i].createInfo.bindingCount = set.binding_count;
    setLayouts[i].createInfo.pBindings = setLayouts[i].bindings.data();
  }
  return;
}

void VulkanMaterial::destroy() {
  delete vertexShader;
  delete fragmentShader;
}
