//
// Created by seth on 8/26/20.
//

#include "rendering/vulkan/VulkanRenderer.h"

VulkanRenderer::VulkanRenderer(SDL_Window* window) {
  this->window = window;
  volkInitialize();
  loadInstance();
  volkLoadInstance(this->instance);
  swapchain = new VulkanSwapchain(instance);
  swapchain->initSurface(window);
  device = new VulkanDevice(instance, swapchain, VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT | VK_QUEUE_COMPUTE_BIT);
  swapchain->connect(device);
  swapchain->createSwapchain();
}

void VulkanRenderer::loadInstance() {
  if (enableValidationLayers) {
    if (!checkValidationLayerSupport()) {
      // TODO: error/log validation layer problem here
    }
  }

  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "TITUS";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "TITUS";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  unsigned int extensionCount;
  if (!SDL_Vulkan_GetInstanceExtensions(this->window, &extensionCount, nullptr)) {
    // TODO: error/log
  }

  size_t additionalCount = extensions.size();
  extensions.resize(additionalCount + extensionCount);

  if (!SDL_Vulkan_GetInstanceExtensions(this->window, &extensionCount, extensions.data() + additionalCount)) {
    // TODO: error/log
  }

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  if (enableValidationLayers) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

  if (result != VK_SUCCESS) {
    // TODO: error/log
  } else {
    // TODO: log
  }
}

bool VulkanRenderer::checkValidationLayerSupport() {
  return false;
}
