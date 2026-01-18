#pragma once

#include <renderer/pipeline/RenderInstance.hpp>

#include <vulkan/vulkan.h>



namespace Kiwi::Vulkan {
    class RenderInstanceVK : public ARenderInstance {
        KIWI_CREATE_OBJECT(RenderInstanceVK)

    public:
        using Super = ARenderInstance;

    public:
        RenderInstanceVK() = default;

    public:
        KIWI_NODISCARD bool Init() override;

        KIWI_NODISCARD EGraphicAPI GetUsedAPI() const override;

        KIWI_NODISCARD bool SetupDebugLayerCallback(const PFN_DebugCallback& debugCallback) override;

        void Destroy() override;

        VkInstance GetVulkanInstance() const;

        ~RenderInstanceVK() override = default;

    private:
        KIWI_NODISCARD bool CreateInstance();
        KIWI_NODISCARD bool CreateDebugMessenger();

    private:
        VkInstance m_vkInstance = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT m_vkDebugMessenger = VK_NULL_HANDLE;
    };
}
