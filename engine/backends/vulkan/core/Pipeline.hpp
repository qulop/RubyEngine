#pragma once

#include <core/Object.hpp>

#include <math/Rect.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>


namespace Kiwi::Vulkan {
    struct VulkanPipelineCreateInfo {
        VkPipelineBindPoint pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

        std::span<VkDynamicState> dynamicStates;

        std::span<VkVertexInputBindingDescription> vertexBindingDescriptions;
        std::span<VkVertexInputAttributeDescription> vertexAttributeDescriptions;

        VkPrimitiveTopology topology;

        U32Rect viewport;
        U32Rect scissor;

        VkBool32 depthClampEnable;

        VkFrontFace frontFaceWindingOrder;
        VkCullModeFlagBits cullModeBits;


    };


    class Pipeline : public AObject {
        KIWI_CREATE_OBJECT(Pipeline);

    public:
        KIWI_NODISCARD static Pipeline Create(const VulkanPipelineCreateInfo& createInfo);

    public:
        Pipeline() = default;


    private:
        VkPipeline m_pipeline = VK_NULL_HANDLE;
        VkPipelineLayout m_layout = VK_NULL_HANDLE;

        VkPipelineBindPoint m_pipelineBindPoint;
    };
}
