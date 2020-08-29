//
// Created by seth on 8/27/20.
//

#include "rendering/vulkan/VulkanSwapchain.h"
#include "rendering/vulkan/VulkanDevice.h"

VulkanSwapchain::VulkanSwapchain(VkInstance instance) {
  this->instance = instance;
}

void VulkanSwapchain::initSurface(SDL_Window *window) {
  if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
    // TODO: log/error
  } else {
    // TODO: log
  }
}

VkSurfaceKHR VulkanSwapchain::getSurface() {
  return surface;
}

void VulkanSwapchain::connect(VulkanDevice* device) {
  this->device = device;
}

void VulkanSwapchain::createSwapchain(bool useVSync) {
  selectColors();

  VkSwapchainKHR oldSwapchain = swapchain;

  VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
  swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

  VkSurfaceCapabilitiesKHR surfaceCapabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->getPhysicalDevice(), surface, &surfaceCapabilities);

  uint32_t presentModeCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface, &presentModeCount, nullptr);

  std::vector<VkPresentModeKHR> presentModes(presentModeCount);

  vkGetPhysicalDeviceSurfacePresentModesKHR(device->getPhysicalDevice(), surface, &presentModeCount, presentModes.data());

  VkExtent2D swapchainExtent = {};

  if (surfaceCapabilities.currentExtent.width == (uint32_t)-1) {
    swapchainExtent.width = 1080;
    swapchainExtent.height = 720;
  } else {
    swapchainExtent = surfaceCapabilities.currentExtent;
  }

  VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR;

  if (!useVSync) {
    for (size_t i = 0; i < presentModeCount; i++) {
      if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
        swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        break;
      }
      if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
        swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
      }
    }
  }

  uint32_t desiredSwapchainImagesCount = surfaceCapabilities.minImageCount + 1;

  if (surfaceCapabilities.maxImageCount > 0 && desiredSwapchainImagesCount > surfaceCapabilities.maxImageCount) {
    desiredSwapchainImagesCount = surfaceCapabilities.maxImageCount;
  }

  VkSurfaceTransformFlagsKHR preTransform;
  if (surfaceCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
    preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  } else {
    preTransform = surfaceCapabilities.currentTransform;
  }

  VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  std::vector<VkCompositeAlphaFlagBitsKHR> compositeAlphaFlags = {
          VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
          VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
          VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
          VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
  };

  for (auto &compositeAlphaFlag : compositeAlphaFlags) {
    if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlag) {
      compositeAlpha = compositeAlphaFlag;
      break;
    };
  }

  swapchainCreateInfo.pNext = nullptr;
  swapchainCreateInfo.surface = surface;
  swapchainCreateInfo.minImageCount = desiredSwapchainImagesCount;
  swapchainCreateInfo.imageFormat = colorFormat;
  swapchainCreateInfo.imageColorSpace = colorSpace;
  swapchainCreateInfo.imageExtent = swapchainExtent;
  swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swapchainCreateInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
  swapchainCreateInfo.imageArrayLayers = 1;
  swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  swapchainCreateInfo.queueFamilyIndexCount = 0;
  swapchainCreateInfo.pQueueFamilyIndices = nullptr;
  swapchainCreateInfo.presentMode = swapchainPresentMode;
  swapchainCreateInfo.oldSwapchain = oldSwapchain;
  swapchainCreateInfo.clipped = VK_TRUE;
  swapchainCreateInfo.compositeAlpha = compositeAlpha;

  if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) {
    swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
  }

  VkResult result = vkCreateSwapchainKHR(device->getLogicalDevice(), &swapchainCreateInfo, nullptr, &swapchain);

  if (result != VK_SUCCESS) {
    // TODO: error/log
  } else {
    // TODO: log
  }
}

void VulkanSwapchain::selectColors() {
  uint32_t formatCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface, &formatCount,
                                       nullptr);

  std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(device->getPhysicalDevice(), surface, &formatCount,
                                       surfaceFormats.data());

  // In this case there is no preferred format
  if ((formatCount == 1) &&
      (surfaceFormats[0].format == VK_FORMAT_UNDEFINED)) {
    colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
    colorSpace = surfaceFormats[0].colorSpace;
  } else {
    bool foundPreferred = false;
    for (auto &&surfaceFormat : surfaceFormats) {
      if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {
        colorFormat = surfaceFormat.format;
        colorSpace = surfaceFormat.colorSpace;
        foundPreferred = true;
        break;
      }
    }

    if (!foundPreferred) {
      colorFormat = surfaceFormats[0].format;
      colorSpace = surfaceFormats[0].colorSpace;
    }
  }
}