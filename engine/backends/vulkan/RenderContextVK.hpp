#pragma once

#include <renderer/IRenderContext.hpp>


namespace Kiwi::Vulkan {
    class RenderPipelineVK;


    class RenderContextVK : public IRenderContext {
        KIWI_CREATE_OBJECT(RenderContextVK, IRenderContext)

    public:
        RenderContextVK() = default;

        KIWI_NODISCARD bool Init() override;
        KIWI_NODISCARD bool SetupDebugLayerCallback(const PFN_DebugCallback& debugCallback) override { return true; }


        KIWI_NODISCARD EGraphicAPI GetUsedAPI() const override;

        KIWI_NODISCARD ARenderPipeline* GetPipeline() override;

        ~RenderContextVK() override = default;

    private:
        RenderPipelineVK* m_pipeline = nullptr;
    };
}