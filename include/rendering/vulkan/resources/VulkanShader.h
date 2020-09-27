//
// Created by seth on 9/7/20.
//

#ifndef TITUS_VULKANSHADER_H
#define TITUS_VULKANSHADER_H

#include <iostream>

#include "spirv_cross.hpp"

#include <resources/Resource.h>
#include <vector>
#include <files/File.h>
#include <rendering/vulkan/managers/VulkanDescriptorManager.h>
#include "files/FileSystem.h"
#include "rendering/RenderSubsystem.h"
#include "rendering/vulkan/VulkanUtils.h"

struct ShaderResourceLayout {
    uint32_t pushConstantSize = 0;
    DescriptorSetLayout sets[VULKAN_NUM_DESCRIPTOR_SETS];
};

class VulkanShader : public Resource {
public:
    VulkanShader();
    void init(const std::string& filename) override;
    void destroy() override {
      std::cout << "SHADER DESTROY WAS CALLED" << std::endl;
    }
    const ShaderResourceLayout &getLayout() const {
      return layout;
    }

    VkShaderModule shaderModule;
    File shaderData;

private:
    void processLayout();
    ShaderResourceLayout layout;
};

#endif //TITUS_VULKANSHADER_H
