//
// Created by seth on 9/26/20.
//

#include "rendering/vulkan/VulkanPipelineLayout.h"

VulkanPipelineLayout::VulkanPipelineLayout(uint64_t hash, const CombinedResourceLayout &resourceLayout) {
  this->hash = hash;
  this->resourceLayout = resourceLayout;
  // Get descriptor set allocators for each set
  // get layout for each set
  // create pipelinelayout from set layouts
}
