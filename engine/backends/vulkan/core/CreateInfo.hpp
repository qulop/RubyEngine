#pragma once

#include <common/Definitions.hpp>

#include <common/meta/Concepts.hpp>

#include <vulkan/vulkan.h>


namespace Kiwi::Vulkan::CreateInfo {
    template<typename T>
    KIWI_NODISCARD T ZeroInit(VkStructureType type) {
        T createInfo = {};
        createInfo.sType = type;
        createInfo.pNext = nullptr;

        return createInfo;
    }


    inline VkDebugUtilsMessengerCreateInfoEXT ForDebugMessenger(PFN_vkDebugUtilsMessengerCallbackEXT callback) {
        auto severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        auto msgType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;


        VkDebugUtilsMessengerCreateInfoEXT c = { .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
        c.pNext = nullptr;
        c.messageSeverity = severity;
        c.messageType = msgType;
        c.pfnUserCallback = callback;
        c.pUserData = nullptr;

        return c;
    }
}

namespace Kiwi::Vulkan::CreateInfo::Pipeline {
    inline VkPipelineInputAssemblyStateCreateInfo ForInputAssembly(VkPrimitiveTopology topology, VkBool32 primitiveRestartEnable = VK_FALSE) {
        VkPipelineInputAssemblyStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.topology = topology;
        c.primitiveRestartEnable = primitiveRestartEnable;

        return c;
    }


    inline VkPipelineDynamicStateCreateInfo ForDynamicState(std::span<const VkDynamicState> dynamicState) {
        VkPipelineDynamicStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.dynamicStateCount = dynamicState.size();
        c.pDynamicStates = dynamicState.data();

        return c;
    }

    inline VkPipelineVertexInputStateCreateInfo ForVertexInput() {
        VkPipelineVertexInputStateCreateInfo c = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        };
        c.pNext = nullptr;
        c.vertexAttributeDescriptionCount = 0;
        c.pVertexAttributeDescriptions = nullptr;
        c.vertexBindingDescriptionCount = 0;
        c.pVertexBindingDescriptions = nullptr;

        return c;
    }


    inline VkPipelineRasterizationStateCreateInfo ForRasterizer(VkPolygonMode polygonMode) {
        VkPipelineRasterizationStateCreateInfo c = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO
        };
        c.depthClampEnable = VK_FALSE;
        c.rasterizerDiscardEnable = VK_FALSE;
        c.polygonMode = polygonMode;
        c.lineWidth = 1.0f;
        c.cullMode = VK_CULL_MODE_BACK_BIT;
        c.frontFace = VK_FRONT_FACE_CLOCKWISE;
        c.depthBiasEnable = VK_FALSE;
        c.depthBiasConstantFactor = 0.0f;
        c.depthBiasClamp = 0.0f;
        c.depthBiasSlopeFactor = 0.0f;

        return c;
    }


    inline VkPipelineMultisampleStateCreateInfo ForDisabledMSAA() {
        VkPipelineMultisampleStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.sampleShadingEnable = VK_FALSE;
        c.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        c.minSampleShading = 1.f;
        c.pSampleMask = nullptr;
        c.alphaToCoverageEnable = VK_FALSE;
        c.alphaToOneEnable = VK_FALSE;

        return c;
    }

    inline VkPipelineViewportStateCreateInfo ForDynamicViewport(u32 viewportsCount, u32 scissorCount) {
        VkPipelineViewportStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.viewportCount = 1;
        c.scissorCount = 1;

        return c;
    }

    inline VkPipelineColorBlendStateCreateInfo ForDefaultColorBlend(const VkPipelineColorBlendAttachmentState& colorBlendAttachment) {
        VkPipelineColorBlendStateCreateInfo c = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO
        };
        c.pNext = nullptr;
        c.logicOpEnable = VK_FALSE;
        c.logicOp = VK_LOGIC_OP_COPY;
        c.attachmentCount = 1;
        c.pAttachments = &colorBlendAttachment;
        c.blendConstants[0] = 0.0f;
        c.blendConstants[1] = 0.0f;
        c.blendConstants[2] = 0.0f;
        c.blendConstants[3] = 0.0f;

        return c;
    }
}