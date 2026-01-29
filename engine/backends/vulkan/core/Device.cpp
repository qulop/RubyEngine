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

        // Getting device properties - we need only devices that supports Vulkan 1.3
        vkGetPhysicalDeviceProperties(physicalDevice, &desc.properties);

        // Getting memory properties
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &desc.memoryProperties);

        // Chain our features from 1.1 to 1.3 together and querying features support
        if (desc.properties.apiVersion >= VK_API_VERSION_1_2) {
            desc.features1_1.pNext = &desc.features1_2;
        }
        else {
            desc.features1_1.pNext = nullptr;
        }

        if (desc.properties.apiVersion >= VK_API_VERSION_1_3) {
            desc.features1_2.pNext = &desc.features1_3;
            desc.features1_3.pNext = nullptr;
        }

        VkPhysicalDeviceFeatures2 physicalDeviceExtendedFeatures = {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
            .pNext = &desc.features1_1
        };
        vkGetPhysicalDeviceFeatures2(physicalDevice, &physicalDeviceExtendedFeatures);

        desc.features = physicalDeviceExtendedFeatures.features;

        // Calculating the total heap size
        for (i32 i = 0; i < desc.memoryProperties.memoryHeapCount; i++) {
            VkMemoryHeap heap = desc.memoryProperties.memoryHeaps[i];

            if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                desc.heapSize += heap.size;
            }

            desc.heapSize += desc.memoryProperties.memoryHeaps[i].size;
        }

        // Finding queue family indices
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
            // Querying a physical device description(VkPhysicalDevice itself, it's properties, features, and so on.
            // Check the `PhysicalDeviceDesc` structure definition for more details) and swapchain support details
            // (it's capabilities, present modes and formats)
            auto deviceDesc = PhysicalDeviceDesc::Query(device, surface);
            auto swapChainSupportDetails = PhysicalDeviceSwapChainSupportDetails::Query(device, surface);

            if (deviceDesc.properties.apiVersion < VK_API_VERSION_1_3) {
                KIWI_CTX_LOG(DEBUG, "A Physical device has been skipped, because it doesn't support Vulkan 1.3 - {}",
                    deviceDesc.properties.deviceName
                );
                continue;
            }

            const bool allIndicesComplete = deviceDesc.queueFamilyIndices.AllIndicesComplete();
            const bool extensionsSupported = CheckDeviceExtensionSupport(device);
            const bool requiredFeaturesSupported = CheckRequiredFeaturesSupport(deviceDesc);
            const bool swapChainCanBeCreated = !swapChainSupportDetails.presentModes.empty() && !swapChainSupportDetails.surfaceFormats.empty();

            const bool deviceSatisfying = allIndicesComplete && extensionsSupported && requiredFeaturesSupported && swapChainCanBeCreated;
            if (!deviceSatisfying) {
                KIWI_CTX_LOG(DEBUG, "A Physical device has been skipped, because it don't satisfying with some requirements: deviceName = {}; allIndicesComplete = {}; extensionsSupported = {}; requiredFeaturesSupported = {}; swapChainCanBeCreated = {}.",
                    deviceDesc.properties.deviceName, allIndicesComplete,
                    extensionsSupported, requiredFeaturesSupported, swapChainCanBeCreated
                );

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

    bool Device::CreateLogicalDevice(VkInstance vkInstance, std::span<const char* const> requiredValidationLayers) {
        constexpr float queuePriority = 1.0f;

        Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        Set<i32> uniqueFamilyIndices = m_physicalDeviceDesc.queueFamilyIndices.GetUniqueIndices();
        for (auto& idx : uniqueFamilyIndices) {
            queueCreateInfos.push_back(DeviceQueues::GetCreateInfo(idx, &queuePriority));
        }


        m_physicalDeviceDesc.features1_1.pNext = &m_physicalDeviceDesc.features1_2;
        m_physicalDeviceDesc.features1_2.pNext = &m_physicalDeviceDesc.features1_3;
        m_physicalDeviceDesc.features1_3.pNext = nullptr;


        VkDeviceCreateInfo deviceCreateInfo = { .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };
        deviceCreateInfo.pNext = &m_physicalDeviceDesc.features1_1;
        deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
        deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
        deviceCreateInfo.pEnabledFeatures = &m_physicalDeviceDesc.features;
        deviceCreateInfo.ppEnabledExtensionNames = VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.data();
        deviceCreateInfo.enabledExtensionCount = VulkanSubsystem::REQUIRED_DEVICE_EXTENSIONS.size();

        if (EngineConfig::ENABLE_DEBUG_CAPABILITIES) {
            deviceCreateInfo.ppEnabledLayerNames = requiredValidationLayers.data();
            deviceCreateInfo.enabledLayerCount = requiredValidationLayers.size();
        }
        else {
            deviceCreateInfo.ppEnabledLayerNames = nullptr;
            deviceCreateInfo.enabledLayerCount = 0;
        }


        if (auto r = vkCreateDevice(m_physicalDeviceDesc.physicalDevice, &deviceCreateInfo, nullptr, &m_vkDevice); r != VK_SUCCESS) {
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

    u64 Device::RatePhysicalDevice(const PhysicalDeviceDesc& deviceDesc) const {
        const auto& deviceProperties = deviceDesc.properties;
        const auto& deviceFeatures = deviceDesc.features;

        u64 rate = CastTo<u64>(GetVkPhysicalDeviceTypeGrade(deviceProperties.deviceType));

        rate += deviceProperties.limits.maxImageDimension2D + deviceProperties.limits.maxViewports;
        rate += (deviceProperties.limits.maxFramebufferWidth * deviceProperties.limits.maxFramebufferHeight);

        rate += deviceFeatures.multiViewport + deviceFeatures.geometryShader;

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

    bool Device::CheckRequiredFeaturesSupport(const PhysicalDeviceDesc& desc) const {
        return  CheckRequiredFeaturesSupportFromVulkan1_2(desc.features1_2) &&
                CheckRequiredFeaturesSupportFromVulkan1_3(desc.features1_3);
    }

    bool Device::CheckRequiredFeaturesSupportFromVulkan1_2(const VkPhysicalDeviceVulkan12Features& ftr1_2) const {
        return std::ranges::all_of(VulkanSubsystem::REQUIRED_DEVICE_VULKAN_1_2_FEATURES,
            [&ftr1_2](const auto& m) { return ftr1_2.*m == VK_TRUE; }
        );
    }

    bool Device::CheckRequiredFeaturesSupportFromVulkan1_3(const VkPhysicalDeviceVulkan13Features &ftr1_3) const {
        return std::ranges::all_of(VulkanSubsystem::REQUIRED_DEVICE_VULKAN_1_3_FEATURES,
            [&ftr1_3](const auto& m) { return ftr1_3.*m == VK_TRUE; }
        );
    }
}
