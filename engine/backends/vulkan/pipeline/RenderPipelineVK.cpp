#include "RenderPipelineVK.hpp"

#include <backends/vulkan/core/VulkanTypes.hpp>
#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>
#include <backends/vulkan/core/Device.hpp>
#include <backends/vulkan/memory/Allocator.hpp>

#include <misc/WindowSubsystem.hpp>

#include <vulkan/vk_enum_string_helper.h>


namespace Kiwi::Vulkan {
    bool RenderPipelineVK::Init(const RenderPipelineInitInfo& initInfo) {
        if (!ARenderPipeline::Init(initInfo)) {
            return false;
        }

        PipelineState pipelineState = PreparePipelineState(initInfo);

    }



    bool RenderPipelineVK::CreatePipelineLayout(const RenderPipelineInitInfo& initInfo) {
        SharedPtr<VulkanSubsystem> vulkanSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vulkanSubsystem);

        VkPipelineLayoutCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        c.pNext = nullptr;
        c.pushConstantRangeCount = 0;
        c.pPushConstantRanges = nullptr;
        c.setLayoutCount = 0;
        c.pSetLayouts = nullptr;

        auto r = vkCreatePipelineLayout(vulkanSubsystem->device->GetDevice(), &c, nullptr, &m_pipelineLayout);
        if (r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create pipeline layout: {}", string_VkResult((r)));
        }

        return r == VK_SUCCESS;
    }

    RenderPipelineVK::PipelineState RenderPipelineVK::PreparePipelineState(const RenderPipelineInitInfo& initInfo) {
        SharedPtr<VulkanSubsystem> vkSubsystem = GetSubsystem<VulkanSubsystem>();
        SharedPtr<WindowSubsystem> wndSubsystem = GetSubsystem<WindowSubsystem>();
        KIWI_ENSURE(vkSubsystem && wndSubsystem);

        PipelineState state;


        state.dynamicState = CreateInfo::Pipeline::ForDynamicState(
            VulkanSubsystem::DEFAULT_DYNAMIC_STATE
        );

        state.vertexInputState = CreateInfo::Pipeline::ForVertexInput();

        state.inputAssemblyState = CreateInfo::Pipeline::ForInputAssembly(
            VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, VK_FALSE
        );

        state.viewportState = CreateInfo::Pipeline::ForDynamicViewport(
            /*viewportsCount=*/1, /*scissorCount=*/1
        );

        state.rasterizationState = CreateInfo::Pipeline::ForRasterizer(VK_POLYGON_MODE_FILL);
        state.multisamplingState = CreateInfo::Pipeline::ForDisabledMSAA();


        VkPipelineColorBlendAttachmentState colorBlendAttachmentState;
        colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachmentState.blendEnable = VK_FALSE;
        colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

        state.colorBlendState = CreateInfo::Pipeline::ForDefaultColorBlend(colorBlendAttachmentState);

        return state;
    }
}
