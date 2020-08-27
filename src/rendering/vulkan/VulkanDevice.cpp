//
// Created by seth on 8/26/20.
//

#include "rendering/vulkan/VulkanDevice.h"

VulkanDevice::VulkanDevice(VkInstance instance, VulkanSwapchain* swapchain, VkQueueFlags requestedQueueFlags) {
  this->instance = instance;
  this->swapchain = swapchain;
  this->requestedQueueFlags = requestedQueueFlags;
  pickPhysicalDevice();

  vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
  vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

  uint32_t queueFamilyCount;
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
  queueFamilyProperties.resize(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

  initLogicalDevice();
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
      this->physicalDevice = device;
      break;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    // TODO: error/log
  } else {
    // TODO: log
  }
}

void VulkanDevice::initLogicalDevice() {
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};

  const float defaultQueuePriority(0.0f);

  if (requestedQueueFlags & VK_QUEUE_GRAPHICS_BIT) {
    queueFamilyIndices.graphicsFamily = getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT, queueFamilyProperties);
    VkDeviceQueueCreateInfo queueInfo{};
    queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
    queueInfo.queueCount = 1;
    queueInfo.pQueuePriorities = &defaultQueuePriority;
    queueCreateInfos.push_back(queueInfo);
  } else {
    queueFamilyIndices.graphicsFamily = VK_NULL_HANDLE;
  }

  if (requestedQueueFlags & VK_QUEUE_COMPUTE_BIT) {
    queueFamilyIndices.computeFamily = getQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT, queueFamilyProperties);
    if (queueFamilyIndices.computeFamily.value() != queueFamilyIndices.graphicsFamily.value()) {
      VkDeviceQueueCreateInfo queueInfo{};
      queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueInfo.queueFamilyIndex = queueFamilyIndices.computeFamily.value();
      queueInfo.queueCount = 1;
      queueInfo.pQueuePriorities = &defaultQueuePriority;
      queueCreateInfos.push_back(queueInfo);
    }
  } else {
    queueFamilyIndices.computeFamily = queueFamilyIndices.graphicsFamily;
  }

  if (requestedQueueFlags & VK_QUEUE_TRANSFER_BIT) {
    queueFamilyIndices.transferFamily = getQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT, queueFamilyProperties);
    if ((queueFamilyIndices.transferFamily != queueFamilyIndices.graphicsFamily) &&
        (queueFamilyIndices.transferFamily != queueFamilyIndices.computeFamily)) {
      VkDeviceQueueCreateInfo queueInfo{};
      queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueInfo.queueFamilyIndex = queueFamilyIndices.transferFamily.value();
      queueInfo.queueCount = 1;
      queueInfo.pQueuePriorities = &defaultQueuePriority;
      queueCreateInfos.push_back(queueInfo);
    }
  } else {
    // Else we use the same queue
    queueFamilyIndices.transferFamily = queueFamilyIndices.graphicsFamily;
  }

  VkDeviceCreateInfo deviceCreateInfo = {};
  deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
  deviceCreateInfo.pEnabledFeatures = {};

  deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
  deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

  VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &logicalDevice);

  if (result != VK_SUCCESS) {
    // TODO: error/log
  } else {
    // TODO: log
  }
}
