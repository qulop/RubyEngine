#include "RenderContextVK.hpp"

#include <core/EngineConfig.hpp>

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/Device.hpp>



namespace Kiwi::Vulkan {
    bool RenderContextVK::Init() {
        RegisterSubsystem<VulkanSubsystem>();
        auto vulkanSubsystem = GetSubsystem<VulkanSubsystem>();


        KIWI_CTX_LOG(INFO, "Trying to initialize VulkanSubsystem...");
        if (!vulkanSubsystem->Init()) {
            return false;
        }

        KIWI_CTX_LOG(INFO, "Creating Vulkan instance and debug messenger(debug messenger enabled = {}",
            EngineConfig::ENABLE_DEBUG_CAPABILITIES
        );
        if (!vulkanSubsystem->CreateInstance() || !vulkanSubsystem->CreateDebugMessenger()) {
            return false;
        }

        KIWI_CTX_LOG(INFO, "Creating a surface...");
        if (!vulkanSubsystem->CreateSurface()) {
            return false;
        }

        // Vulkan physical and logical device creation
        if (!vulkanSubsystem->CreateVulkanDevice()) {
            return false;
        }

        if (!vulkanSubsystem->CreateSwapChain()) {
            return false;
        }

        return true;
    }

    EGraphicAPI RenderContextVK::GetUsedAPI() const {
        return EGraphicAPI::Vulkan;
    }
}
