#pragma once

#include <core/Object.hpp>

#include <vulkan/vulkan.h>


namespace Kiwi::Vulkan {
    class VulkanCore : public AObject {
        KIWI_CREATE_OBJECT(VulkanCore)

    public:
        KIWI_NODISCARD static constexpr u32 VULKAN_API_VERSION = VK_API_VERSION_1_0;

    public:
        VulkanCore() = default;

    public:
        KIWI_NODISCARD Vector<String> GetRequiredValidationLayers() const;


        ~VulkanCore() override = default;
    };
}