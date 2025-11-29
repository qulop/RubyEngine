 #pragma once

#include <utility/Definitions.hpp>
#include <graphics/Color.hpp>
#include <math/Rect.hpp>


namespace Ruby {
    RUBY_FORWARD_DECLARATIONS(
        RUBY_INTERFACE IGraphicObjectsFactory;

        class GraphicDevice;
    )


    enum class EClearBuffers {
        COLOR_BUFFER = RUBY_BIT(0),
        DEPTH_BUFFER = RUBY_BIT(1),
        STENCIL_BUFFER = RUBY_BIT(2),

        ALL = COLOR_BUFFER | DEPTH_BUFFER | STENCIL_BUFFER
    };


    RUBY_ABSTRACT class ARenderPipeline {
    public:
        explicit ARenderPipeline(const SharedPtr<GraphicDevice>& device);

    public:
        RUBY_NODISCARD virtual bool Init();

        RUBY_NODISCARD virtual String GetRendererDeviceVendor() const = 0;
        RUBY_NODISCARD virtual String GetRendererDeviceName() const = 0;

        virtual void SetViewport(const IRect& viewport);

        virtual void ClearBuffers(EClearBuffers buffersToClear = EClearBuffers::ALL) = 0;
        virtual void ClearColor(const Color& color) = 0;
        virtual void ClearColor(const Vec4& color) = 0;
        virtual void ClearColor(f32 r, f32 g, f32 b, f32 a) = 0;


        virtual ~ARenderPipeline() = default;

    protected:
        RUBY_NODISCARD bool InitBuffers();

    protected:
        SharedPtr<GraphicDevice> m_graphicDevice;

        IRect m_viewport;
    };
}
