#pragma once

#include <common/meta/TypeTraits.hpp>
#include <common/Errors.hpp>

#include <backends/vulkan/core/VulkanTypes.hpp>


namespace Kiwi::Vulkan {
    struct QueueFamilyIndices {
        i32 presentationQueueIndex = KIWI_VK_UNDEFINED_ID;
        i32 graphicQueueIndex = KIWI_VK_UNDEFINED_ID;

    public:
        // Will return found queue families(even is they aren't complete)
        KIWI_NODISCARD static QueueFamilyIndices Find(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

    public:
        KIWI_NODISCARD std::set<i32> GetUniqueIndices() const;
        KIWI_NODISCARD std::array<i32, 2> AsArray() const;

        KIWI_NODISCARD bool AllIndicesComplete() const;
    };


    struct DeviceQueues {
        VkQueue presentationQueue = VK_NULL_HANDLE;
        VkQueue graphicQueue = VK_NULL_HANDLE;

    public:
        VkDeviceQueueCreateInfo static GetCreateInfo(i32 idx, const float* priority);

        KIWI_NODISCARD static Opt<DeviceQueues> Create(VkDevice device, QueueFamilyIndices indices);

    public:
        KIWI_NODISCARD bool IsValid() const;
    };
}