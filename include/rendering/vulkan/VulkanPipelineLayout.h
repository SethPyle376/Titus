//
// Created by seth on 9/26/20.
//

#ifndef TITUS_VULKANPIPELINELAYOUT_H
#define TITUS_VULKANPIPELINELAYOUT_H

#include <cstdint>
#include <rendering/vulkan/resources/VulkanMaterial.h>

class CombinedResourceLayout;

class VulkanPipelineLayout
{
public:
    VulkanPipelineLayout(uint64_t hash, const CombinedResourceLayout& resourceLayout);
private:
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    uint64_t hash;
    CombinedResourceLayout resourceLayout;
};

#endif //TITUS_VULKANPIPELINELAYOUT_H
