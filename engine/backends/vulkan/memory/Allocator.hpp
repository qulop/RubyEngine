#pragma once

#include <core/Object.hpp>

#include <backends/vulkan/core/VulkanTypes.hpp>

#include <vk_mem_alloc.h>


namespace Kiwi::Vulkan {
    class VulkanAllocator : public AObject {
        KIWI_CREATE_OBJECT(VulkanAllocator, AObject);

    public:
        VulkanAllocator() = default;

    public:
        KIWI_NODISCARD bool Init(TypeTags::UseVulkanSubsystemForInit);
        KIWI_NODISCARD bool Init(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);

        KIWI_NODISCARD VmaAllocator GetVmaAllocator() const;

        KIWI_NODISCARD VmaVulkanFunctions GetVulkanFunctions() const;

        ~VulkanAllocator() override;

    private:
        VmaAllocator m_allocator = VK_NULL_HANDLE;
    };
}