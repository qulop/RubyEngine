#pragma once

#include <types/TypeTraits.hpp>

#include <core/Object.hpp>

#include <math/Rect.hpp>


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_INTERFACE IGraphicObjectsFactory;

        KIWI_INTERFACE IRenderContext;
        KIWI_ABSTRACT class ARenderPipeline;
        KIWI_ABSTRACT class AShaderCompiler;

        KIWI_ABSTRACT class AGraphicDevice;
    )


    class Renderer : public AObject {
        KIWI_CREATE_OBJECT(Renderer);

    public:
        KIWI_NODISCARD bool Init();

        void SetViewport(const I32Rect& viewport) const;

        ~Renderer() override = default;

    private:
        SharedPtr<IGraphicObjectsFactory> m_factory;

        SharedPtr<IRenderContext> m_renderContext;
    };
}
