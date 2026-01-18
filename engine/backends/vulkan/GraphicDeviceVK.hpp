#pragma once

#include <backends/vulkan/core/VulkanSubsystem.hpp>

#include <renderer/GraphicDevice.hpp>


namespace Kiwi::Vulkan {
    KIWI_FORWARD_DECLARATIONS(
        class GraphicObjectsFactoryVK
    );


    class GraphicDeviceVK final : public AGraphicDevice {
        KIWI_CREATE_OBJECT(GraphicDeviceVK)

    private:
        using Super = AGraphicDevice;

    public:
        KIWI_NODISCARD bool Init(SharedPtr<ARenderInstance> renderInstance) override;

    private:
        friend class GraphicObjectsFactoryVK;

        VkPhysicalDevice m_vkPhysicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties m_vkPhysicalDeviceProperties = {};

        String m_vendorName;

        VkDevice m_vkDevice = VK_NULL_HANDLE;
    };
}