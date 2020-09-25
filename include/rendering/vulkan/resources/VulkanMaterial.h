//
// Created by seth on 9/7/20.
//

#ifndef TITUS_VULKANMATERIAL_H
#define TITUS_VULKANMATERIAL_H

#include "nlohmann/json.hpp"

#include "volk.h"
#include "spirv_reflect.h"
#include "spirv_cross.hpp"

#include "files/FileSystem.h"
#include <resources/Ref.h>
#include <resources/Resource.h>
#include "VulkanShader.h"
#include "rendering/vulkan/managers/VulkanDescriptorManager.h"

enum ShaderStage {
    Vertex = 0,
    Fragment = 1,
    Count
};

struct CombinedResourceLayout {
  DescriptorSetLayout sets[VULKAN_NUM_DESCRIPTOR_SETS] = {};
  uint32_t stagesForSets[VULKAN_NUM_DESCRIPTOR_SETS] = {};
  uint32_t stagesForBindings[VULKAN_NUM_DESCRIPTOR_SETS][VULKAN_NUM_DESCRIPTOR_BINDINGS] = {};
};


class VulkanMaterial : public Resource {
private:
    std::string name;
    Ref<VulkanShader>* shaders[ShaderStage::Count];
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    CombinedResourceLayout resourceLayout;

    std::vector<DescriptorSetLayoutData> vertLayoutData;
public:
    void init(const std::string& filename) override;
    void destroy() override;
    Ref<VulkanShader>* getShader(ShaderStage stage);

    void setResourceLayout(const CombinedResourceLayout& resourceLayout);
};

#endif //TITUS_VULKANMATERIAL_H
