//
// Created by seth on 8/27/20.
//

#include "rendering/vulkan/VulkanUtils.h"

bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR vkSurface,
                      std::vector<const char *> deviceExtensions) {
  // TODO: MAKE PHYSICAL DEVICE PICKING MORE ROBUST
  VkPhysicalDeviceProperties deviceProperties;
  vkGetPhysicalDeviceProperties(device, &deviceProperties);

  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  // TODO: CONSIDER CACHING QUEUE FAMILIES
  QueueFamilyIndices indices = findQueueFamilies(device, vkSurface);

  bool extensionsSupported =
          checkDeviceExtensionSupport(device, deviceExtensions);

  bool swapChainAdequate = false;
  if (extensionsSupported) {
    SwapchainSupportDetails swapChainSupport =
            querySwapchainSupport(device, vkSurface);
    swapChainAdequate = !swapChainSupport.formats.empty() &&
                        !swapChainSupport.presentModes.empty();
  }

  bool deviceType =
          (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
           deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
  bool indicesComplete = indices.isComplete();
  // return deviceFeatures.geometryShader &&
  //         extensionsSupported &&
  //             swapChainAdequate &&
  //                 deviceType &&
  //                     indicesComplete;
  return extensionsSupported;
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device,
                                 std::vector<const char *> deviceExtensions) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       nullptr);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceExtensions.begin(),
                                           deviceExtensions.end());

  for (const auto &extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  return requiredExtensions.empty();
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device,
                                     VkSurfaceKHR vkSurface) {
  QueueFamilyIndices indices;

  uint32_t queueFamilyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount,
                                           queueFamilies.data());

  int i = 0;
  for (const auto &queueFamily : queueFamilies) {
    if (queueFamily.queueCount > 0 &&
        queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }

    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vkSurface, &presentSupport);

    if (queueFamily.queueCount > 0 && presentSupport) {
      indices.presentFamily = i;
    }

    if (indices.isComplete()) {
      break;
    }

    i++;
  }

  return indices;
}


SwapchainSupportDetails querySwapchainSupport(VkPhysicalDevice device,
                                              VkSurfaceKHR surface) {
  SwapchainSupportDetails details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface,
                                            &details.capabilities);

  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

  if (formatCount != 0) {
    details.formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount,
                                         details.formats.data());
  }

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount,
                                            nullptr);

  if (presentModeCount != 0) {
    details.presentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
            device, surface, &presentModeCount, details.presentModes.data());
  }

  return details;
}


uint32_t getQueueFamilyIndex(VkQueueFlagBits queueFlags, std::vector<VkQueueFamilyProperties> queueFamilyProperties) {
  if (queueFlags & VK_QUEUE_COMPUTE_BIT) {
    for (uint32_t i = 0;
         i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
      if ((queueFamilyProperties[i].queueFlags & queueFlags) &&
          ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ==
           0)) {
        return i;
        break;
      }
    }
  }

  if (queueFlags & VK_QUEUE_TRANSFER_BIT) {
    for (uint32_t i = 0;
         i < static_cast<uint32_t>(queueFamilyProperties.size()); i++) {
      if ((queueFamilyProperties[i].queueFlags & queueFlags) &&
          ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) ==
           0) &&
          ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0)) {
        return i;
        break;
      }
    }
  }

  for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilyProperties.size());
       i++) {
    if (queueFamilyProperties[i].queueFlags & queueFlags) {
      return i;
      break;
    }
  }
  return 0;
}
