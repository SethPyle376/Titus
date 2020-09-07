//
// Created by seth on 9/7/20.
//

#ifndef TITUS_VULKANMATERIAL_H
#define TITUS_VULKANMATERIAL_H

#include "nlohmann/json.hpp"

#include "files/FileSystem.h"
#include <resources/Ref.h>
#include <resources/Resource.h>
#include <vulkan/vulkan.h>
#include "VulkanShader.h"

class VulkanMaterial : public Resource {
private:
    std::string name;
    Ref<VulkanShader> vertexShader;
    Ref<VulkanShader> fragmentShader;
public:
    void init(const std::string& filename) override;
    void destroy();
};

#endif //TITUS_VULKANMATERIAL_H
