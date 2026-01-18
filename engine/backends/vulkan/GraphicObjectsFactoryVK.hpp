#pragma once

#include <renderer/IGraphicObjectsFactory.hpp>


namespace Kiwi::Vulkan {
    class GraphicObjectsFactoryVK : public IGraphicObjectsFactory {
    public:
        KIWI_NODISCARD SharedPtr<ARenderInstance> CreateRenderInstance() const override;

        KIWI_NODISCARD SharedPtr<AGraphicDevice> CreateGraphicDevice() const override;

        KIWI_NODISCARD SharedPtr<ARenderPipeline> CreateRenderPipeline(const SharedPtr<GraphicDevice>& device) const override;

        KIWI_NODISCARD SharedPtr<AShaderCompiler> CreateShaderCompiler() const override;

        ~GraphicObjectsFactoryVK() override = default;
    };
}