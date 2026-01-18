#pragma once

#include <core/Object.hpp>

#include <backends/vulkan/pipeline/RenderInstanceVK.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/Surface.hpp>
#include <backends/vulkan/core/QueueFamilies.hpp>



namespace Kiwi::Vulkan {
    struct PhysicalDeviceDesc {
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceMemoryProperties memoryProperties;
        u32 heapSize = 0;

        QueueFamilyIndices queueFamilyIndices;
    };


    class Device : protected AObject {
        KIWI_CREATE_OBJECT(Device)

    public:
        KIWI_NODISCARD static PhysicalDeviceDesc GetPhysicalDeviceDesc(VkPhysicalDevice device, const Surface& surface);

    public:
        KIWI_NODISCARD bool Init(VkInstance vkInstance, const Surface& surface, const Vector<const char*>& requiredLayers);

        KIWI_NODISCARD const PhysicalDeviceDesc& GetPhysicalDevice() const;
        KIWI_NODISCARD VkDevice GetDevice();


    private:
        KIWI_NODISCARD bool CreatePhysicalDevice(VkInstance vkInstance, const Surface& surface);
        KIWI_NODISCARD u32 RatePhysicalDevice(PhysicalDeviceDesc deviceDesc);

        KIWI_NODISCARD bool CreateLogicalDevice(VkInstance vkInstance, const Vector<const char*>& requiredLayers);

    private:
        PhysicalDeviceDesc m_physicalDeviceDesc = {};

        VkDevice m_vkDevice = VK_NULL_HANDLE;
        DeviceQueues m_deviceQueues = {};
    };
}
