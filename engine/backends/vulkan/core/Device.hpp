#pragma once

#include <core/Object.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/QueueFamilies.hpp>



namespace Kiwi::Vulkan {
    struct PhysicalDeviceDesc {
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        VkPhysicalDeviceProperties properties;

        VkPhysicalDeviceFeatures features;
        VkPhysicalDeviceVulkan11Features features1_1 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };
        VkPhysicalDeviceVulkan12Features features1_2 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
        VkPhysicalDeviceVulkan13Features features1_3 = { .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };

        VkPhysicalDeviceMemoryProperties memoryProperties;
        u32 heapSize = 0;

        QueueFamilyIndices queueFamilyIndices;


        KIWI_NODISCARD static PhysicalDeviceDesc Query(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

        void ConnectFeatures();
    };

    struct PhysicalDeviceSwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        Vector<VkSurfaceFormatKHR> surfaceFormats;
        Vector<VkPresentModeKHR> presentModes;


        KIWI_NODISCARD static PhysicalDeviceSwapChainSupportDetails Query(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    };


    class Device : protected AObject {
        KIWI_CREATE_OBJECT(Device)

    public:
        struct InitInfo {
            VkInstance instance = VK_NULL_HANDLE;
            VkSurfaceKHR surface = VK_NULL_HANDLE;
            std::span<const char* const> requiredValidationLayers;
        };

    public:
        KIWI_NODISCARD bool Init(TypeTags::UseVulkanSubsystemForInit);
        KIWI_NODISCARD bool Init(InitInfo deviceInitInfo);

        KIWI_NODISCARD const PhysicalDeviceDesc& GetPhysicalDevice() const;
        KIWI_NODISCARD VkDevice GetDevice();

        KIWI_NODISCARD const PhysicalDeviceSwapChainSupportDetails& GetSwapChainSupportDetails() const;

        ~Device() override;

    private:
        KIWI_NODISCARD bool CreatePhysicalDevice(VkInstance vkInstance, VkSurfaceKHR surface);
        KIWI_NODISCARD u64 RatePhysicalDevice(const PhysicalDeviceDesc& deviceDesc) const;

        KIWI_NODISCARD bool CheckDeviceExtensionSupport(VkPhysicalDevice device) const;

        KIWI_NODISCARD bool CheckRequiredFeaturesSupport(const PhysicalDeviceDesc& desc) const;
        KIWI_NODISCARD bool CheckRequiredFeaturesSupportFromVulkan1_2(const VkPhysicalDeviceVulkan12Features& ftr1_2) const;
        KIWI_NODISCARD bool CheckRequiredFeaturesSupportFromVulkan1_3(const VkPhysicalDeviceVulkan13Features& ftr1_3) const;

        KIWI_NODISCARD bool CreateLogicalDevice(VkInstance vkInstance, std::span<const char* const> requiredValidationLayers);

    private:
        PhysicalDeviceDesc m_physicalDeviceDesc = {};

        VkDevice m_vkDevice = VK_NULL_HANDLE;
        DeviceQueues m_deviceQueues = {};

        PhysicalDeviceSwapChainSupportDetails m_swapChainSupportDetails = {};
    };
}
