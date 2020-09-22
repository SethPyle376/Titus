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

  vertLayoutData = std::vector<DescriptorSetLayoutData>(sets.size(), DescriptorSetLayoutData{});

  for (int i = 0; i < sets.size(); i++) {
    const SpvReflectDescriptorSet set = *(sets[i]);
    vertLayoutData[i].bindings.resize(set.binding_count);
    for (int j = 0; j < set.binding_count; j++) {
      const SpvReflectDescriptorBinding binding = *(set.bindings[j]);
      VkDescriptorSetLayoutBinding& layoutBinding = vertLayoutData[i].bindings[j];
      layoutBinding.binding = binding.binding;
      layoutBinding.descriptorType = static_cast<VkDescriptorType>(binding.descriptor_type);
      layoutBinding.descriptorCount = 1;
      for (int k = 0; k < binding.array.dims_count; k++) {
        layoutBinding.descriptorCount *= binding.array.dims[k];
      }
      layoutBinding.stageFlags = static_cast<VkShaderStageFlagBits>(vertexModule.shader_stage);
    }
    vertLayoutData[i].setNumber = set.set;
    vertLayoutData[i].createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    vertLayoutData[i].createInfo.bindingCount = set.binding_count;
    vertLayoutData[i].createInfo.pBindings = vertLayoutData[i].bindings.data();
  }

  std::vector<VkDescriptorSetLayout> layouts(vertLayoutData.size(), VkDescriptorSetLayout{});

  auto* renderer = (VulkanRenderer*)RenderSubsystem::getInstance()->getRenderer();

  VkDevice device = renderer->getDevice()->getLogicalDevice();

  for (int i = 0; i < vertLayoutData.size(); i++) {
    if (vkCreateDescriptorSetLayout(device, &vertLayoutData[i].createInfo, nullptr, &layouts[i]) != VK_SUCCESS) {
      //TODO: log/error
    }
  }

  VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
  pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutCreateInfo.setLayoutCount = layouts.size();
  pipelineLayoutCreateInfo.pSetLayouts = layouts.data();

  if (vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
    std::cout << "ERROR CREATING PIPELINE LAYOUT" << std::endl;
  }
  
  return;
}

void VulkanMaterial::destroy() {
  delete vertexShader;
  delete fragmentShader;
}
