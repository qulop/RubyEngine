#pragma once

#include <types/TypeTraits.hpp>

#include <math/Rect.hpp>


namespace Ruby {
    RUBY_FORWARD_DECLARATIONS(
        RUBY_INTERFACE IGraphicObjectsFactory;

        RUBY_ABSTRACT class ARenderInstance;
        RUBY_ABSTRACT class ARenderPipeline;
        RUBY_ABSTRACT class AShaderCompiler;

        class GraphicDevice;
    )


    class Renderer {
    public:
        RUBY_NODISCARD bool Init();

        void SetViewport(const IRect& viewport) const;

    private:
        SharedPtr<IGraphicObjectsFactory> m_factory;

        SharedPtr<ARenderInstance> m_instance;
        SharedPtr<ARenderPipeline> m_renderPipeline;
        SharedPtr<AShaderCompiler> m_shaderCompiler;

        SharedPtr<GraphicDevice> m_graphicDevice;
    };
}
