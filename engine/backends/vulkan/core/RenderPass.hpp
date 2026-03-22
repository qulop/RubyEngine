#pragma once

#include <core/Object.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>



namespace Kiwi::Vulkan {
    class Device;


    struct RenderPassCreateInfo {
        SharedPtr<Device> device;

        std::span<VkAttachmentDescription> attachments;

        std::span<VkSubpassDescription> subpasses;
    };


    struct RenderPass : public AObject {
        KIWI_CREATE_OBJECT(RenderPass)

    public:
        VkRenderPass renderPass = VK_NULL_HANDLE;

    public:
        KIWI_NODISCARD static Result<RenderPass, EGeneralError> Create(const RenderPassCreateInfo& createInfo);



    private:

    };
}