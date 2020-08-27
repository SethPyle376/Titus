//
// Created by seth on 8/26/20.
//

#include "rendering/vulkan/VulkanDevice.h"

VulkanDevice::VulkanDevice(VkInstance instance, VulkanSwapchain* swapchain) {
  this->instance = instance;
  this->swapchain = swapchain;
  pickPhysicalDevice();
}

void VulkanDevice::pickPhysicalDevice() {
  uint32_t deviceCount = 0;

  vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    // TODO: error/log no devices
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device, swapchain->getSurface(), deviceExtensions)) {
      physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    // TODO: error/log
  } else {
    // TODO: log
  }
}
