#include "RenderPipelineVK.hpp"

#include <backends/vulkan/core/VulkanTypes.hpp>
#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>

#include <misc/WindowSubsystem.hpp>

#include "backends/vulkan/memory/Allocator.hpp"


namespace Kiwi::Vulkan {
    bool RenderPipelineVK::Init(const RenderPipelineInitInfo& initInfo) {
        if (!ARenderPipeline::Init(initInfo)) {
            return false;
        }



    }

    bool RenderPipelineVK::InitVulkanPipeline(const RenderPipelineInitInfo& initInfo) {
        auto vkSubsystem = GetSubsystem<VulkanSubsystem>();
        auto wndSubsystem = GetSubsystem<WindowSubsystem>();
        KIWI_ENSURE(vkSubsystem && wndSubsystem);


        // VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = CreateInfo::Pipeline::ForDynamicState(
        //     std::span> {VulkanSubsystem::DEFAULT_DYNAMIC_STATE.data(), VulkanSubsystem::DEFAULT_DYNAMIC_STATE.size() }
        // );


        VkPipelineVertexInputStateCreateInfo vertexInputCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO
        };
        vertexInputCreateInfo.vertexAttributeDescriptionCount = 0;
        vertexInputCreateInfo.pVertexAttributeDescriptions = nullptr;
        vertexInputCreateInfo.vertexBindingDescriptionCount = 0;
        vertexInputCreateInfo.pVertexBindingDescriptions = nullptr;


        VkPipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO
        };
        inputAssemblyCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssemblyCreateInfo.primitiveRestartEnable = VK_FALSE;
    }
}
