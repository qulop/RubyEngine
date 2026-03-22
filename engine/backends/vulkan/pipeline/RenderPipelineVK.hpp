#pragma once

#include <renderer/pipeline/RenderPipeline.hpp>


namespace Kiwi::Vulkan {
    class RenderPipelineVK : public ARenderPipeline {
        KIWI_CREATE_OBJECT(ARenderPipeline)

    public:
        KIWI_NODISCARD bool Init(const RenderPipelineInitInfo& initInfo) override;

    private:
        KIWI_NODISCARD bool InitVulkanPipeline(const RenderPipelineInitInfo& initInfo);

    };

}