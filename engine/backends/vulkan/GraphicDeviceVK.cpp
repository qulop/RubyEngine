#include "GraphicDeviceVK.hpp"

#include <backends/vulkan/RenderContextVK.hpp>
#include <backends/vulkan/core/Device.hpp>


namespace Kiwi::Vulkan {
    bool GraphicDeviceVK::Init() {
        if (!Super::Init()) {
            return false;
        }

        return true;
    }
}
