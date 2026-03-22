#pragma once

#include <renderer/pipeline/RenderPipeline.hpp>

#include <backends/vulkan/core/VulkanTypes.hpp>


namespace Kiwi::Vulkan {
    class RenderPipelineVK : public ARenderPipeline {
        KIWI_CREATE_OBJECT(ARenderPipeline)

    public:
        struct PipelineState {
            VkPipelineDynamicStateCreateInfo dynamicState;
            VkPipelineVertexInputStateCreateInfo vertexInputState;
            VkPipelineInputAssemblyStateCreateInfo inputAssemblyState;
            VkPipelineViewportStateCreateInfo viewportState;
            VkPipelineRasterizationStateCreateInfo rasterizationState;
            VkPipelineMultisampleStateCreateInfo multisamplingState;

            VkPipelineColorBlendStateCreateInfo colorBlendState;
        };

    public:
        KIWI_NODISCARD bool Init(const RenderPipelineInitInfo& initInfo) override;

    private:
        KIWI_NODISCARD bool CreatePipelineLayout(const RenderPipelineInitInfo& initInfo);

        KIWI_NODISCARD PipelineState PreparePipelineState(const RenderPipelineInitInfo& initInfo);


    private:
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
    };

}