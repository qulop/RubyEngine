#include "Device.hpp"

#include <backends/vulkan/core/CreateInfo.hpp>

#include <misc/WindowSubsystem.hpp>

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
    PhysicalDeviceDesc Device::GetPhysicalDeviceDesc(VkPhysicalDevice device, const Surface& surface) {
        PhysicalDeviceDesc desc;
        desc.physicalDevice = device;

        vkGetPhysicalDeviceProperties(device, &desc.properties);
        vkGetPhysicalDeviceFeatures(device, &desc.features);
        vkGetPhysicalDeviceMemoryProperties(device, &desc.memoryProperties);

        for (i32 i = 0; i < desc.memoryProperties.memoryHeapCount; i++) {
            VkMemoryHeap heap = desc.memoryProperties.memoryHeaps[i];

            if (heap.flags & VK_MEMORY_HEAP_DEVICE_LOCAL_BIT) {
                desc.heapSize += heap.size;
            }

            desc.heapSize += desc.memoryProperties.memoryHeaps[i].size;
        }

        desc.queueFamilyIndices = QueueFamilyIndices::Find(device, surface);

        return desc;
    }


    bool Device::Init(VkInstance vkInstance, const Surface& surface, const Vector<const char*>& requiredLayers) {
        KIWI_CTX_LOG(INFO, "The Vulkan devices creation has began...");


        return CreatePhysicalDevice(vkInstance, surface) && CreateLogicalDevice(vkInstance, requiredLayers);
    }

    const PhysicalDeviceDesc& Device::GetPhysicalDevice() const {
        return m_physicalDeviceDesc;
    }

    VkDevice Device::GetDevice() {
        return m_vkDevice;
    }

    bool Device::CreatePhysicalDevice(VkInstance vkInstance, const Surface& surface) {
        u32 count = 0 ;
        vkEnumeratePhysicalDevices(vkInstance, &count, nullptr);

        Vector<VkPhysicalDevice> physicalDevices(count);
        vkEnumeratePhysicalDevices(vkInstance, &count, physicalDevices.data());

        std::multimap<u32, PhysicalDeviceDesc> candidates;
        for (auto device : physicalDevices) {
            PhysicalDeviceDesc deviceDesc = GetPhysicalDeviceDesc(device, surface);
            if (!deviceDesc.queueFamilyIndices.AllIndicesComplete()) {
                continue;
            }

            u32 deviceRate = RatePhysicalDevice(deviceDesc);

            candidates.insert(std::make_pair(deviceRate, deviceDesc));
        }

        if (candidates.empty()) {
            KIWI_CTX_LOG(CRITICAL, "Failed to find any suitable physical device");
            return false;
        }


        m_physicalDeviceDesc = candidates.rbegin()->second;
        KIWI_CTX_LOG(INFO, "Selected physical device: name = {}, vendorID = {}, heap size(total) = {}",
            m_physicalDeviceDesc.properties.deviceName,
            m_physicalDeviceDesc.properties.vendorID,
            m_physicalDeviceDesc.heapSize
        );

        return true;
    }

    u32 Device::RatePhysicalDevice(PhysicalDeviceDesc deviceDesc) {
        u32 rate = 0;

        rate += BasicCast::To<u32>(GetVkPhysicalDeviceTypeGrade(deviceDesc.properties.deviceType));

        rate += deviceDesc.properties.limits.maxImageDimension2D;

        rate += deviceDesc.features.multiViewport;
        rate *= deviceDesc.features.geometryShader;

        return rate;
    }

    bool Device::CreateLogicalDevice(VkInstance vkInstance, const Vector<const char*>& requiredLayers) {
        constexpr float queuePriority = 1.0f;

        Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

        std::set<i32> uniqueFamilyIndices = m_physicalDeviceDesc.queueFamilyIndices.GetUniqueIndices();
        for (auto& idx : uniqueFamilyIndices) {
            queueCreateInfos.push_back(DeviceQueues::GetCreateInfo(idx, &queuePriority));
        }

        auto createInfo = GetBasicCreateInfo<VkDeviceCreateInfo>(VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &m_physicalDeviceDesc.features;
        createInfo.enabledExtensionCount = 0;

        if (ARenderInstance::ENABLE_DEBUG_CAPABILITIES) {
            createInfo.ppEnabledLayerNames = requiredLayers.data();
            createInfo.enabledLayerCount = requiredLayers.size();
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
