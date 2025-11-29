#pragma once

#include <renderer/IGraphicObjectsFactory.hpp>


namespace Ruby::OpenGL {
    class GraphicObjectsFactoryGL : public IGraphicObjectsFactory {
    public:
        RUBY_NODISCARD SharedPtr<ARenderInstance> CreateRenderInstance() const override;

        RUBY_NODISCARD SharedPtr<ARenderPipeline> CreateRenderPipeline(const SharedPtr<GraphicDevice>& device) const override;

        RUBY_NODISCARD SharedPtr<AShaderCompiler> CreateShaderCompiler() const override;

        ~GraphicObjectsFactoryGL() override = default;
    };
}