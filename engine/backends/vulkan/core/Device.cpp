#include "Device.hpp"

#include <backends/vulkan/core/CreateInfo.hpp>

#include <core/EngineConfig.hpp>
#include <misc/WindowSubsystem.hpp>
#include <types/CString.hpp>

#include <vulkan/vk_enum_string_helper.h>

#include <map>



namespace {
    enum class PhysicalDeviceTypeGrades : Kiwi::u32 {
        OTHER_TYPE = 0,
        CPU_TYPE = 1,
        INTEGRATED_TYPE = 2,
        VIRTUAL_TYPE = 3,
        DISCRETE_TYPE = 4,
    };


    PhysicalDeviceTypeGrades GetVkPhysicalDeviceTypeGrade(VkPhysicalDeviceType type) {
        switch (type) {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return PhysicalDeviceTypeGrades::OTHER_TYPE;
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return PhysicalDeviceTypeGrades::INTEGRATED_TYPE;
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return PhysicalDeviceTypeGrades::DISCRETE_TYPE;
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return PhysicalDeviceTypeGrades::VIRTUAL_TYPE;
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return PhysicalDeviceTypeGrades::CPU_TYPE;
        default:
            return PhysicalDeviceTypeGrades::OTHER_TYPE;
        }
    }
}


namespace Kiwi::Vulkan {
    PhysicalDeviceDesc PhysicalDeviceDesc::Query(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        PhysicalDeviceDesc desc;
        desc.physicalDevice = physicalDevice;

        vkGetPhysicalDeviceProperties(physicalDevice, &desc.properties);
        vkGetPhysicalDeviceFeatures(physicalDevice, &desc.features);
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &desc.memoryProperties);

        for (i32 i = 0; i < desc.memoryProperties.memoryHeapCount; i++) {
            VkMemoryHeap heap = desc.memoryProperties.memoryHeaps[i];

            if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                desc.heapSize += heap.size;
            }

            desc.heapSize += desc.memoryProperties.memoryHeaps[i].size;
        }

        desc.queueFamilyIndices = QueueFamilyIndices::Find(physicalDevice, surface);

        return desc;
    }

    PhysicalDeviceSwapChainSupportDetails PhysicalDeviceSwapChainSupportDetails::Query(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
        PhysicalDeviceSwapChainSupportDetails details;


        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.surfaceCapabilities);

        details.surfaceFormats = EnumerateVulkanArray<VkSurfaceFormatKHR>(
            [&](u32* c, VkSurfaceFormatKHR* a) { return vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, c, a); }
        );

        details.presentModes = EnumerateVulkanArray<VkPresentModeKHR>(
            [&](u32* c, VkPresentModeKHR* a) { return vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, c, a); }
        );

        return details;
    }



    bool Device::Init(TypeTags::UseVulkanSubsystemForInit) {
        KIWI_CTX_LOG(INFO, "Starting a device creation(both VkPhysicalDevice and VkDevice)...");

        auto vulkanSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vulkanSubsystem);


        InitInfo deviceInitInfo {
            .instance = vulkanSubsystem->instance,
            .surface = vulkanSubsystem->surface,
            .requiredValidationLayers = std::span{ VulkanSubsystem::REQUIRED_VALIDATION_LAYERS }
        };

        return Init(deviceInitInfo);
    }

    bool Device::Init(InitInfo deviceInitInfo) {
        auto& [instance, surface, requiredValidationLayers] = deviceInitInfo;

        return  CreatePhysicalDevice(instance, surface) &&
                CreateLogicalDevice(instance, requiredValidationLayers);
    }

    const PhysicalDeviceDesc& Device::GetPhysicalDevice() const {
        return m_physicalDeviceDesc;
    }

    VkDevice Device::GetDevice() {
        return m_vkDevice;
    }

    const PhysicalDeviceSwapChainSupportDetails& Device::GetSwapChainSupportDetails() const {
        return m_swapChainSupportDetails;
    }

    Device::~Device() {
        vkDestroyDevice(m_vkDevice, nullptr);
    }


    bool Device::CreatePhysicalDevice(VkInstance vkInstance, VkSurfaceKHR surface) {
        using ScoredPhysicalDevice = std::pair<PhysicalDeviceDesc, PhysicalDeviceSwapChainSupportDetails>;

        Vector<VkPhysicalDevice> physicalDevices = EnumerateVulkanArray<VkPhysicalDevice>(
            [&](u32* c, VkPhysicalDevice* a) { return vkEnumeratePhysicalDevices(vkInstance, c, a); }
        );

        std::multimap<u64, ScoredPhysicalDevice> candidates;
        for (auto device : physicalDevices) {
            auto deviceDesc = PhysicalDeviceDesc::Query(device, surface);
            auto swapChainSupportDetails = PhysicalDeviceSwapChainSupportDetails::Query(device, surface);


            const bool allIndicesComplete = deviceDesc.queueFamilyIndices.AllIndicesComplete();
            const bool extensionsSupported = CheckDeviceExtensionSupport(device);
            const bool swapChainCanBeCreated = !swapChainSupportDetails.presentModes.empty() && !swapChainSupportDetails.surfaceFormats.empty();

            if (!allIndicesComplete || !extensionsSupported || !swapChainCanBeCreated) {
                continue;
            }

            ScoredPhysicalDevice scoredPhysicalDevice = std::make_pair(deviceDesc, swapChainSupportDetails);
            candidates.emplace(RatePhysicalDevice(deviceDesc), scoredPhysicalDevice);
        }

        if (candidates.empty()) {
            KIWI_CTX_LOG(CRITICAL, "Failed to find any suitable physical device");
            return false;
        }


        std::tie(m_physicalDeviceDesc, m_swapChainSupportDetails) = candidates.rbegin()->second;
        KIWI_CTX_LOG(INFO, "Selected physical device: name = {}, vendorID = {}, heap size(total) = {}",
            m_physicalDeviceDesc.properties.deviceName,
            m_physicalDeviceDesc.properties.vendorID,
            m_physicalDeviceDesc.heapSize
        );

        return true;
    }

    u64 Device::RatePhysicalDevice(const PhysicalDeviceDesc& deviceDesc) const {
        const auto& deviceProperties = deviceDesc.properties;
        const auto& deviceFeatures = deviceDesc.features;


        u64 rate = CastTo<u64>(GetVkPhysicalDeviceTypeGrade(deviceProperties.deviceType));


        rate += deviceProperties.limits.maxImageDimension2D;
        rate += (deviceProperties.limits.maxFramebufferWidth * deviceProperties.limits.maxFramebufferHeight);
        rate += deviceProperties.limits.maxViewports;

        rate += deviceFeatures.multiViewport;
        rate *= deviceFeatures.geometryShader;

        return rate;
    }

    bool Device::CheckDeviceExtensionSupport(VkPhysicalDevice device) const {
        Vector<VkExtensionProperties> availableExt = EnumerateVulkanArray<VkExtensionProperties>(
            [&](u32* c, VkExtensionProperties* a) { return vkEnumerateDeviceExtensionProperties(device, nullptr, c, a); }
        );

        Set<const char*> requiredExt(VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.begin(), VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.end());
        for (const VkExtensionProperties& availSingleExt : availableExt) {
            auto it = std::ranges::find_if(requiredExt, [&](const char* ext) {
                return CString::StrCmpBool(availSingleExt.extensionName, ext);
            });

            if (it != requiredExt.end()) {
                requiredExt.erase(it);
            }
        }

        return requiredExt.empty();
    }

    bool Device::CreateLogicalDevice(VkInstance vkInstance, std::span<const char* const> requiredValidationLayers) {
        constexpr float queuePriority = 1.0f;

        Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        Set<i32> uniqueFamilyIndices = m_physicalDeviceDesc.queueFamilyIndices.GetUniqueIndices();
        for (auto& idx : uniqueFamilyIndices) {
            queueCreateInfos.push_back(DeviceQueues::GetCreateInfo(idx, &queuePriority));
        }

        auto createInfo = GetBasicCreateInfo<VkDeviceCreateInfo>(VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &m_physicalDeviceDesc.features;
        createInfo.ppEnabledExtensionNames = VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.data();
        createInfo.enabledExtensionCount = VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.size();

        if (EngineConfig::ENABLE_DEBUG_CAPABILITIES) {
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
            createInfo.enabledLayerCount = requiredValidationLayers.size();
        }
        else {
            createInfo.ppEnabledLayerNames = nullptr;
            createInfo.enabledLayerCount = 0;
        }


        if (auto r = vkCreateDevice(m_physicalDeviceDesc.physicalDevice, &createInfo, nullptr, &m_vkDevice); r != VK_SUCCESS) {
            KIWI_CTX_LOG(CRITICAL, "Failed to create a logical device -- {}",
                string_VkResult(r)
            );
            return false;
        }

        m_deviceQueues = DeviceQueues::Create(m_vkDevice, m_physicalDeviceDesc.queueFamilyIndices)
            .value_or(DeviceQueues{});
        if (!m_deviceQueues.IsValid()) {
            KIWI_CTX_LOG(CRITICAL, "Failed to create logical device queues");
            return false;
        }

        return true;
    }
}
