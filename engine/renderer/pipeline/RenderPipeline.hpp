 #pragma once

#include <core/Object.hpp>

#include <common/Definitions.hpp>

#include <graphics/Color.hpp>

#include <math/Rect.hpp>


namespace Kiwi {
    KIWI_FORWARD_DECLARATIONS(
        KIWI_INTERFACE IGraphicObjectsFactory;

        class GraphicDevice;
    )


    enum class EClearBuffers {
        COLOR_BUFFER = KIWI_BIT(0),
        DEPTH_BUFFER = KIWI_BIT(1),
        STENCIL_BUFFER = KIWI_BIT(2),

        ALL = COLOR_BUFFER | DEPTH_BUFFER | STENCIL_BUFFER
    };


    struct RenderPipelineInitInfo {
        U32Rect viewport;
        U32Rect scissor;
        u16 msaaSamplesCount = 4;
    };


    KIWI_ABSTRACT class ARenderPipeline : public AObject {
        KIWI_CREATE_OBJECT(ARenderPipeline);

    public:
        ARenderPipeline() = default;

    public:
        KIWI_NODISCARD virtual bool Init(const RenderPipelineInitInfo& initInfo) {
            m_viewport = initInfo.viewport;
            m_scissor = initInfo.scissor;

            return true;
        }

        virtual void SetViewport(const U32Rect& viewport) { m_viewport = viewport; }
        virtual void SetScissor(const U32Rect& scissor) { m_scissor = scissor; }



        ~ARenderPipeline() override = default;

    protected:
        U32Rect m_viewport;
        U32Rect m_scissor;
    };
}
