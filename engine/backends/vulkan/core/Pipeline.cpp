#include "Pipeline.hpp"

#include <backends/vulkan/core/CreateInfo.hpp>
#include <backends/vulkan/core/VulkanTypes.hpp>


namespace Kiwi::Vulkan {
    Pipeline Pipeline::Create(const VulkanPipelineCreateInfo& createInfo) {
        // VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = CreateInfo::Pipeline::ForDynamicState(createInfo.dynamicStates);
        //
        // VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = CreateInfo::Pipeline::ForInputAssembly(createInfo.topology);
        //
        //
        // const auto viewport = Cast<U32Rect>::ToVkViewport(createInfo.viewport);
        // const auto scissor = Cast<U32Rect>::ToVkRect2D(createInfo.scissor);
        // VkPipelineViewportStateCreateInfo viewportStateCreateInfo = CreateInfo::Pipeline::ForViewport(
        //     &viewport, &scissor
        // );
    }
}
