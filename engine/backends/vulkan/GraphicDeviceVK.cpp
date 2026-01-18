#include "GraphicDeviceVK.hpp"

#include <backends/vulkan/pipeline/RenderInstanceVK.hpp>
#include <backends/vulkan/core/Device.hpp>


namespace Kiwi::Vulkan {
    bool GraphicDeviceVK::Init(SharedPtr<ARenderInstance> renderInstance) {
        if (!Super::Init(renderInstance)) {
            return false;
        }

        SharedPtr<RenderInstanceVK> renderInstanceVk = std::dynamic_pointer_cast<RenderInstanceVK>(renderInstance);
        KIWI_ASSERT_BASIC(renderInstanceVk != nullptr);

        Device device;
        // TODO
        // KIWI_IGNORE_RETURN(device.Init(renderInstanceVk->GetVulkanInstance()));


        return true;
    }
}
