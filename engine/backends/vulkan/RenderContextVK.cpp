#include "RenderContextVK.hpp"

#include <core/EngineConfig.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/Device.hpp>

#include <backends/vulkan/pipeline/RenderPipelineVK.hpp>


namespace Kiwi::Vulkan {
    bool RenderContextVK::Init() {
        RegisterSubsystem<VulkanSubsystem>();

        auto vulkanSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vulkanSubsystem);

        if (!vulkanSubsystem->Init()) {
            return false;
        }

        m_pipeline = KIWI_NOTHROW_NEW RenderPipelineVK();
        return m_pipeline != nullptr;
    }

    EGraphicAPI RenderContextVK::GetUsedAPI() const {
        return EGraphicAPI::Vulkan;
    }

    ARenderPipeline* RenderContextVK::GetPipeline() {
        return m_pipeline;
    }
}
