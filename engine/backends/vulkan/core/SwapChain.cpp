#include "SwapChain.hpp"

#include <misc/WindowSubsystem.hpp>
#include <math/Rect.hpp>

#include <backends/vulkan/core/Device.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>

#include <vulkan/vk_enum_string_helper.h>


namespace Kiwi::Vulkan {
    bool SwapChain::Init(TypeTags::UseVulkanSubsystemForInit) {
        auto vkSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vkSubsystem);

        return Init(
            vkSubsystem->device,
            vkSubsystem->surface
        );
    }

    bool SwapChain::Init(SharedPtr<Device> device, VkSurfaceKHR surface) {
        KIWI_CTX_LOG(INFO, "Starting a swapchain creation...");

        m_parentDevice = device;
        PrepareSwapChainProps(device->GetSwapChainSupportDetails());

        if (!CreateSwapChain(surface)) {
            return false;
        }

        m_imageViews.resize(m_images.size());
        for (size_t i = 0; i < m_images.size(); i++) {
            auto resImageView = CreateViewFromImage(m_images[i]);
            if (!resImageView) {
                KIWI_CTX_LOG(ERROR, "Failed to create an image view from VkImage: {}",
                    *resImageView.error().desc
                );
                return false;
            }

            m_imageViews[i] = *resImageView;
        }

        return true;
    }

    VkSwapchainKHR SwapChain::GetSwapChain() const {
        return m_swapChain;
    }

    SwapChain::~SwapChain() {
        VkDevice device = m_parentDevice->GetDevice();
        for (VkImageView& imgView : m_imageViews) {
            vkDestroyImageView(device, imgView, nullptr);
        }

        vkDestroySwapchainKHR(device, m_swapChain, nullptr);
    }


    void SwapChain::PrepareSwapChainProps(const PhysicalDeviceSwapChainSupportDetails& supportDetails) {
        const auto& [surfaceCapabilities, surfaceFormats, presentModes] = supportDetails;

        // Picking a surface format
        auto selectedFormatIt = std::ranges::find_if(surfaceFormats, [](const VkSurfaceFormatKHR& format) {
            return format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        });

        if (selectedFormatIt != surfaceFormats.end()) {
            m_surfaceFormat = *selectedFormatIt;
        }
        else {
            m_surfaceFormat = surfaceFormats.front();
        }


        // Picking a present mode(FIFO by default if some other more suitable didn't find)
        auto selectedPresentModeIt = std::ranges::find_if(presentModes, [](const VkPresentModeKHR& presentMode) {
            return presentMode == VK_PRESENT_MODE_MAILBOX_KHR;
        });

        if (selectedPresentModeIt != presentModes.end()) {
            m_presentMode = *selectedPresentModeIt;
        }
        else {
            m_presentMode = VK_PRESENT_MODE_FIFO_KHR;
        }


        // Picking swap extent
        if (surfaceCapabilities.currentExtent.width != std::numeric_limits<u32>::max()) {
            m_swapChainImageExtent2D = surfaceCapabilities.currentExtent;
        }
        else {
            U32Rect framebufferSizes = GetSubsystem<WindowSubsystem>()
                ->GetMainWindow()
                ->GetFramebufferSizes();

            m_swapChainImageExtent2D = {
                framebufferSizes.Width(),
                framebufferSizes.Height(),
            };
            m_swapChainImageExtent2D.width = std::clamp(
                m_swapChainImageExtent2D.width,
                surfaceCapabilities.minImageExtent.width,
                surfaceCapabilities.maxImageExtent.width
            );

            m_swapChainImageExtent2D.height = std::clamp(
                m_swapChainImageExtent2D.height,
                surfaceCapabilities.minImageExtent.height,
                surfaceCapabilities.maxImageExtent.height
            );
        }


        // Choose the image count
        const u32 maxImageCountInSwapChain = surfaceCapabilities.maxImageCount;

        m_imageCount = surfaceCapabilities.minImageCount + 1;
        if (maxImageCountInSwapChain > 0 && m_imageCount > maxImageCountInSwapChain) {
            m_imageCount = maxImageCountInSwapChain;
        }
    }

    bool SwapChain::CreateSwapChain(VkSurfaceKHR surface) {
        KIWI_ENSURE(m_parentDevice);

        const auto& queueIndices = m_parentDevice->GetPhysicalDevice().queueFamilyIndices;
        const auto& swapChainDeviceSupportDetails = m_parentDevice->GetSwapChainSupportDetails();

        auto createInfo = CreateInfo::ZeroInit<VkSwapchainCreateInfoKHR>(VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR);
        createInfo.surface = surface;
        createInfo.minImageCount = m_imageCount;
        createInfo.imageFormat = m_surfaceFormat.format;
        createInfo.imageColorSpace = m_surfaceFormat.colorSpace;
        createInfo.imageExtent = m_swapChainImageExtent2D;
        createInfo.presentMode = m_presentMode;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        createInfo.preTransform = swapChainDeviceSupportDetails.surfaceCapabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (queueIndices.graphicQueueIndex != queueIndices.presentationQueueIndex) {
            auto queueIdxArray = queueIndices.AsArray();

            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = queueIdxArray.size();
            createInfo.pQueueFamilyIndices = (const u32*)(queueIdxArray.data());
        }
        else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            createInfo.queueFamilyIndexCount = 0;
            createInfo.pQueueFamilyIndices = nullptr;
        }

        if (auto r = vkCreateSwapchainKHR(m_parentDevice->GetDevice(), &createInfo, nullptr, &m_swapChain); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create a swapchain: {}", string_VkResult(r));
            return false;
        }

        m_images = EnumerateVulkanArray<VkImage>(
            [&](u32* c, VkImage* img) {
                return vkGetSwapchainImagesKHR(m_parentDevice->GetDevice(), m_swapChain, c, img);
            }
        );

        return true;
    }

    Result<VkImageView, VkResult> SwapChain::CreateViewFromImage(VkImage image) const {
        VkComponentMapping defaultComponents = {
            .r = VK_COMPONENT_SWIZZLE_IDENTITY,
            .g = VK_COMPONENT_SWIZZLE_IDENTITY,
            .b = VK_COMPONENT_SWIZZLE_IDENTITY,
            .a = VK_COMPONENT_SWIZZLE_IDENTITY
        };

        VkImageSubresourceRange defaultSubresourceRange = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .baseMipLevel = 0,
            .levelCount = 1,
            .baseArrayLayer = 0,
            .layerCount = 1
        };

        auto createInfo = CreateInfo::ZeroInit<VkImageViewCreateInfo>(VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO);
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = m_surfaceFormat.format;
        createInfo.components = defaultComponents;
        createInfo.subresourceRange = defaultSubresourceRange;

        VkImageView view = VK_NULL_HANDLE;
        if (auto r = vkCreateImageView(m_parentDevice->GetDevice(), &createInfo, nullptr, &view); r != VK_SUCCESS) {
            return Unexpected(Error{
                .kind = r,
                .desc = string_VkResult(r)
            });
        }

        return view;
    }
}
