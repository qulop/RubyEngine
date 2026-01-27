#pragma once

#include <core/Object.hpp>

#include <vulkan/vulkan.h>


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_ABSTRACT class AWindow;
    )
}


namespace Kiwi::Vulkan {
    KIWI_FORWARD_DECLARATIONS(
        class Device;
        class SwapChain;
    )

    Expected<VkSurfaceKHR, VkResult> CreateWindowSurface(VkInstance instance, SharedPtr<AWindow> wnd);


    class VulkanSubsystem : public ASubsystem {
        KIWI_CREATE_OBJECT(VulkanSubsystem)

    public:
        using Super = ASubsystem;

    public:
        static constexpr u32 VULKAN_API_VERSION = VK_API_VERSION_1_3;

        static constexpr std::array<const char*, 1> REQUIRED_VALIDATION_LAYERS = {
            "VK_LAYER_KHRONOS_validation"
        };

        static constexpr auto REQUIRED_DEVICE_EXTENSIONS = std::array {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

    public:
        KIWI_NODISCARD bool Init() override;
        KIWI_NODISCARD bool InitImGui();

        KIWI_NODISCARD bool CreateInstance();
        KIWI_NODISCARD bool CreateDebugMessenger();

        KIWI_NODISCARD bool CreateSurface();

        KIWI_NODISCARD bool CreateVulkanDevice();

        KIWI_NODISCARD bool CreateSwapChain();


        KIWI_NODISCARD static Vector<VkLayerProperties> GetAvailableValidationLayers();

        KIWI_NODISCARD static Status<Vector<String>> CheckRequiredValidationLayersForSupport();

        void DeInit() override;

    public:
        VkInstance instance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;

        VkSurfaceKHR surface = VK_NULL_HANDLE;

        SharedPtr<Device> device;

        SharedPtr<SwapChain> swapChain;
    };
}
