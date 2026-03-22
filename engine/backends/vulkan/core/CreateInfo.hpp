#pragma once

#include <utility/Definitions.hpp>

#include <types/Concepts.hpp>

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


    inline VkPipelineDynamicStateCreateInfo ForDynamicState(std::span<VkDynamicState> dynamicState) {
        VkPipelineDynamicStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.dynamicStateCount = dynamicState.size();
        c.pDynamicStates = dynamicState.data();

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

    inline VkPipelineViewportStateCreateInfo ForViewport(const VkViewport* viewport, const VkRect2D* scissors) {
        VkPipelineViewportStateCreateInfo c = { .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
        c.pNext = nullptr;
        c.viewportCount = 1;
        c.pViewports = viewport;
        c.scissorCount = 1;
        c.pScissors = scissors;

        return c;
    }
}