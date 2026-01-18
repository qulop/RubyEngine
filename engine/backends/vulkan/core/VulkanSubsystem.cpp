#include "VulkanSubsystem.hpp"

#include <misc/WindowSubsystem.hpp>
#include <core/LogSubsystem.hpp>

#include <vulkan/vk_enum_string_helper.h>

#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

#include "Device.hpp"


namespace {
    const Kiwi::Vector<Kiwi::String> REQUIRED_VALIDATION_LAYERS = {
        "VK_LAYER_KHRONOS_validation"
    };

    Kiwi::Vector<VkLayerProperties> s_availableValidationLayers = {};
}


namespace Kiwi::Vulkan {
    VkBool32 DefaultDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData
    )
    {
        auto* logSubsystem = (LogSubsystem*)userData;

        logSubsystem->Log(
            ELogLevel::WARNING_LOG,
            "Vulkan Validation Layers:\n\tSeverity: {}\n\tType: {}\n\tMessage: {}",
                string_VkDebugUtilsMessageSeverityFlagsEXT(severity),
                string_VkDebugUtilsMessageTypeFlagsEXT(messageType),
                callbackData->pMessage
        );

        return VK_FALSE;
    }



    bool VulkanSubsystem::Init() {
        return Super::Init();
    }

    bool VulkanSubsystem::InitImGui() {
        auto mainWindow = GetSubsystem<WindowSubsystem>()->GetMainWindow();
        if (mainWindow->GetVendor() == EWindowVendor::GLFW) {
            ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)mainWindow->GetNativeWindowPtr(), true);
        }
        else {
            std::unreachable();
        }

        // ImGui_ImplVulkan_InitInfo initInfo = {};
        // initInfo.Instance = m_instance;
        // initInfo.PhysicalDevice = m_device->GetPhysicalDevice().physicalDevice;
        // initInfo.Device = m_device->GetDevice();
        // initInfo.QueueFamily = m_d

        return true;
    }

    Vector<String> VulkanSubsystem::GetRequiredValidationLayers() const {
        return REQUIRED_VALIDATION_LAYERS;
    }

    Vector<const char*> VulkanSubsystem::GetRequiredValidationLayersRaw() const {
        return REQUIRED_VALIDATION_LAYERS
            | std::views::transform([](const auto& s) -> const char* { return s.c_str(); })
            | std::ranges::to<Vector<const char*>>();
    }

    Vector<VkLayerProperties> VulkanSubsystem::GetAvailableValidationLayers() const {
        if (!s_availableValidationLayers.empty()) {
            return s_availableValidationLayers;
        }

        u32 availableLayersCount = 0;
        vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

        s_availableValidationLayers.resize(availableLayersCount);
        vkEnumerateInstanceLayerProperties(&availableLayersCount, s_availableValidationLayers.data());

        return s_availableValidationLayers;
    }

    Expected<void, Vector<String>> VulkanSubsystem::CheckRequiredValidationLayersForSupport() const {
        const Vector<VkLayerProperties> availableLayers = GetAvailableValidationLayers();

        Set<StringView> availableLayersNamesSet;
        for (const auto& layer : availableLayers) {
            availableLayersNamesSet.emplace(StringView{ layer.layerName });
        }

        Vector<String> unsupportedLayers;
        for (auto requiredLayer : REQUIRED_VALIDATION_LAYERS) {
            if (!availableLayersNamesSet.contains(requiredLayer)) {
                unsupportedLayers.emplace_back(requiredLayer);
            }
        }

        if (!unsupportedLayers.empty()) {
            return std::unexpected(unsupportedLayers);
        }
        return {};
    }
}
