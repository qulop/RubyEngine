#pragma once

#include <renderer/pipeline/RenderPipeline.hpp>


namespace Ruby::OpenGL {
    class RenderPipelineGL : public ARenderPipeline {
    public:
        using Super = ARenderPipeline;

    public:
        explicit RenderPipelineGL(const SharedPtr<GraphicDevice>& device) :
            Super(device)
        {}

        RUBY_NODISCARD bool Init() override;

        RUBY_NODISCARD String GetRendererDeviceVendor() const override;
        RUBY_NODISCARD String GetRendererDeviceName() const override;

        void ClearBuffers(EClearBuffers buffersToClear = EClearBuffers::ALL) override;
        void ClearColor(const Color& color) override;
        void ClearColor(const Vec4& color) override;
        void ClearColor(f32 r, f32 g, f32 b, f32 a) override;

        void SetViewport(const IRect& viewport) override;


        ~RenderPipelineGL() override = default;
    };
}