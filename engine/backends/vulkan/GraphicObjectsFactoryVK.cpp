#include "GraphicObjectsFactoryVK.hpp"

#include <backends/vulkan/RenderContextVK.hpp>
#include <backends/vulkan/GraphicDeviceVK.hpp>



namespace Kiwi::Vulkan {
    SharedPtr<AGraphicDevice> GraphicObjectsFactoryVK::CreateGraphicDevice() const {
        return MakeShared<GraphicDeviceVK>();
    }

    SharedPtr<ARenderPipeline> GraphicObjectsFactoryVK::CreateRenderPipeline() const {
        return nullptr;
    }

    SharedPtr<AShaderCompiler> GraphicObjectsFactoryVK::CreateShaderCompiler() const {
        return nullptr;
    }
}
