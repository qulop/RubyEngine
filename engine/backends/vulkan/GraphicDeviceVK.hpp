#pragma once

#include <backends/vulkan/core/VulkanSubsystem.hpp>

#include <renderer/GraphicDevice.hpp>


namespace Kiwi::Vulkan {
    KIWI_FORWARD_DECLARATIONS(
        class GraphicObjectsFactoryVK;

        class Device;
        class Surface;
    );


    class GraphicDeviceVK final : public AGraphicDevice {
        KIWI_CREATE_OBJECT(GraphicDeviceVK)

    private:
        using Super = AGraphicDevice;

    public:
        KIWI_NODISCARD bool Init() override;

    private:
        friend class GraphicObjectsFactoryVK;

        SharedPtr<Device> m_vulkanDevice;

        SharedPtr<Surface> m_surface;
    };
}