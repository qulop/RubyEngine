#define VMA_IMPLEMENTATION
#include "Allocator.hpp"

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <vulkan/vk_enum_string_helper.h>

#include "backends/vulkan/core/Device.hpp"


namespace Kiwi::Vulkan {
    bool VulkanAllocator::Init(TypeTags::UseVulkanSubsystemForInit) {
        auto vkSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vkSubsystem);

        return Init(vkSubsystem->instance, vkSubsystem->device);
    }

    bool VulkanAllocator::Init(VkInstance instance, SharedPtr<Device> device) {
        KIWI_CTX_LOG(INFO, "Creating a VMA allocator...");


        VmaVulkanFunctions vulkanFunctions = GetVulkanFunctions();

        VmaAllocatorCreateInfo allocatorCreateInfo{};
        allocatorCreateInfo.instance = instance;
        allocatorCreateInfo.device = device->GetDevice();
        allocatorCreateInfo.physicalDevice = device->GetPhysicalDevice().physicalDevice;
        allocatorCreateInfo.pVulkanFunctions = &vulkanFunctions;

        if (auto r = vmaCreateAllocator(&allocatorCreateInfo, &m_allocator); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create a VMA allocator: {}", string_VkResult(r));
            return false;
        }

        return true;
    }

    VmaAllocator VulkanAllocator::GetVmaAllocator() const {
        return m_allocator;
    }

    VmaVulkanFunctions VulkanAllocator::GetVulkanFunctions() const {
        VmaVulkanFunctions vulkanFunctions = {};
        vulkanFunctions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
        vulkanFunctions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;
        vulkanFunctions.vkFreeMemory = vkFreeMemory;
        vulkanFunctions.vkMapMemory = vkMapMemory;
        vulkanFunctions.vkUnmapMemory = vkUnmapMemory;
        vulkanFunctions.vkCreateBuffer = vkCreateBuffer;
        vulkanFunctions.vkDestroyBuffer = vkDestroyBuffer;
        vulkanFunctions.vkCreateImage = vkCreateImage;

        return vulkanFunctions;
    }
}
