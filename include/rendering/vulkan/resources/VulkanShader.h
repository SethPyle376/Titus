//
// Created by seth on 9/7/20.
//

#ifndef TITUS_VULKANSHADER_H
#define TITUS_VULKANSHADER_H

#include <iostream>

#include <resources/Resource.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <files/File.h>

class VulkanShader : public Resource {
public:
    VulkanShader();
    void init(const std::string& filename) override;
    void destroy() override {}
    VkShaderModule shaderModule;
    File shaderData;
};

#endif //TITUS_VULKANSHADER_H
