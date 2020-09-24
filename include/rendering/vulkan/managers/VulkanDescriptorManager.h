//
// Created by seth on 9/23/20.
//

#ifndef TITUS_VULKANDESCRIPTORMANAGER_H
#define TITUS_VULKANDESCRIPTORMANAGER_H

#include <vector>
#include <map>
#include "volk.h"

struct DescriptorSetLayout {
    uint32_t uniform_buffer_mask = 0;
};

struct DescriptorSetLayoutData {
    uint32_t setNumber;
    VkDescriptorSetLayoutCreateInfo createInfo;
    std::vector<VkDescriptorSetLayoutBinding> bindings;
};

struct DescriptorSetPool {
    VkDescriptorPool pool;
    std::vector<VkDescriptorSet> sets;
};

struct PerFrameData {
    DescriptorSetPool setPool;
};

class DescriptorSetAllocator {
private:
    std::vector<PerFrameData> data;
public:

};

class DescriptorManager {
private:
    std::map<uint32_t, DescriptorSetAllocator> allocators;

    uint32_t hashLayoutData(const DescriptorSetLayoutData& data);
public:
    void registerLayout(const DescriptorSetLayoutData& data);
};

#endif //TITUS_VULKANDESCRIPTORMANAGER_H
