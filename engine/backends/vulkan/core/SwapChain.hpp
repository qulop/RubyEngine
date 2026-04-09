#pragma once

#include <core/Object.hpp>

#include <backends/vulkan/core/VulkanTypes.hpp>

#include <common/types/Result.hpp>



namespace Kiwi::Vulkan {
    struct PhysicalDeviceSwapChainSupportDetails;
    class Device;


    class SwapChain : public AObject {
        KIWI_CREATE_OBJECT(SwapChain, AObject)

    public:
        SwapChain() = default;

        KIWI_NODISCARD bool Init(TypeTags::UseVulkanSubsystemForInit);
        KIWI_NODISCARD bool Init(SharedPtr<Device> device, VkSurfaceKHR surface);

        KIWI_NODISCARD VkSwapchainKHR GetSwapChain() const;

        ~SwapChain() override;

    private:
        void PrepareSwapChainProps(const PhysicalDeviceSwapChainSupportDetails& supportDetails);

        KIWI_NODISCARD bool CreateSwapChain(VkSurfaceKHR surface);
        KIWI_NODISCARD Result<VkImageView, VkResult> CreateViewFromImage(VkImage image) const;

    private:
        SharedPtr<Device> m_parentDevice;

        VkSurfaceFormatKHR m_surfaceFormat = {};
        VkPresentModeKHR m_presentMode = {};
        VkExtent2D m_swapChainImageExtent2D = {};
        u32 m_imageCount = 0;

        VkSwapchainKHR m_swapChain = VK_NULL_HANDLE;

        Vector<VkImage> m_images;
        Vector<VkImageView> m_imageViews;
    };
}