#pragma once

#include <core/Object.hpp>

#include <vulkan/vulkan.h>


namespace Kiwi::Vulkan {
    KIWI_FORWARD_DECLARATIONS(
        class Device;
        class Surface;

    )


    class VulkanSubsystem : public ASubsystem {
        KIWI_CREATE_OBJECT(VulkanSubsystem)

    public:
        using Super = ASubsystem;

    public:
        static constexpr u32 VULKAN_API_VERSION = VK_API_VERSION_1_0;

    public:
        KIWI_NODISCARD bool Init() override;
        KIWI_NODISCARD bool InitImGui();


        KIWI_NODISCARD Vector<String> GetRequiredValidationLayers() const;
        KIWI_NODISCARD Vector<const char*> GetRequiredValidationLayersRaw() const;

        KIWI_NODISCARD Vector<VkLayerProperties> GetAvailableValidationLayers() const;

        KIWI_NODISCARD Expected<void, Vector<String>> CheckRequiredValidationLayersForSupport() const;


    private:
        VkInstance m_instance = VK_NULL_HANDLE;

        SharedPtr<Device> m_device;
        SharedPtr<Surface> m_surface;
    };
}