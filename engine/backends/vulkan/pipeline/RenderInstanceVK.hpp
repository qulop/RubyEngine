#pragma once

#include <renderer/pipeline/RenderInstance.hpp>

#include <backends/vulkan/core/VulkanCore.hpp>

#include <vulkan/vulkan.h>



namespace Kiwi::Vulkan {
    class RenderInstanceVK : public ARenderInstance {
        KIWI_CREATE_OBJECT(RenderInstanceVK)

    public:
        RenderInstanceVK() = default;

    public:
        KIWI_NODISCARD bool Init() override;

        KIWI_NODISCARD EGraphicAPI GetUsedAPI() const override;

        ~RenderInstanceVK() override = default;

    private:
        SharedPtr<VulkanCore> m_vkCore;

        VkInstance m_vkInstance = VK_NULL_HANDLE;
    };
}
