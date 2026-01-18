#include "GraphicObjectsFactoryVK.hpp"

#include <backends/vulkan/GraphicDeviceVK.hpp>
#include <backends/vulkan/pipeline/RenderInstanceVK.hpp>



namespace Kiwi::Vulkan {
    SharedPtr<ARenderInstance> GraphicObjectsFactoryVK::CreateRenderInstance() const {
        return MakeShared<RenderInstanceVK>();
    }

    SharedPtr<AGraphicDevice> GraphicObjectsFactoryVK::CreateGraphicDevice() const {
        return MakeShared<GraphicDeviceVK>();
    }

    SharedPtr<ARenderPipeline> GraphicObjectsFactoryVK::CreateRenderPipeline(const SharedPtr<GraphicDevice> &device) const {
        return nullptr;
    }

    SharedPtr<AShaderCompiler> GraphicObjectsFactoryVK::CreateShaderCompiler() const {
        return nullptr;
    }
}
