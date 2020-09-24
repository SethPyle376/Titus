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


class VulkanMaterial : public Resource {
private:
    std::string name;
    Ref<VulkanShader>* vertexShader;
    Ref<VulkanShader>* fragmentShader;
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;

    std::vector<DescriptorSetLayoutData> vertLayoutData;
public:
    void init(const std::string& filename) override;
    void destroy() override;
};

#endif //TITUS_VULKANMATERIAL_H
