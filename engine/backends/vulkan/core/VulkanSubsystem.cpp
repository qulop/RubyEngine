#include "VulkanSubsystem.hpp"

#include <types/String.hpp>
#include <misc/WindowSubsystem.hpp>
#include <core/LogSubsystem.hpp>
#include <core/EngineConfig.hpp>

#include <backends/vulkan/core/Device.hpp>
#include <backends/vulkan/core/SwapChain.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>
#include <backends/vulkan/memory/Allocator.hpp>

#include <vulkan/vk_enum_string_helper.h>

#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>



namespace {
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
        if (!Super::Init()) {
            return false;
        }

        KIWI_CTX_LOG(INFO, "Creating a Vulkan instance and debug messenger(debug messenger enabled = {})",
            EngineConfig::ENABLE_DEBUG_CAPABILITIES
        );
        if (!CreateInstance() || !CreateDebugMessenger()) {
            return false;
        }

        KIWI_CTX_LOG(INFO, "Creating a surface...");
        if (!CreateSurface() || !CreateVulkanDevice()) {
            return false;
        }

        return CreateSwapChain();
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

    bool VulkanSubsystem::CreateInstance() {
        if constexpr (EngineConfig::ENABLE_DEBUG_CAPABILITIES) {
            auto checkRes = CheckRequiredValidationLayersForSupport();
            if (!checkRes) {
                KIWI_CTX_LOG(ERROR, "These layers aren't supported, but required: ( {} )",
                    StringUtils::Join(checkRes.error(), /*sep = */ ',')
                );
                return false;
            }
        }

        constexpr const char* engineName = EngineConfig::ENGINE_NAME.data();
        constexpr u32 engineVersionFlags = EngineConfig::ENGINE_VERSION.GetFlags();

        auto appInfo = CreateInfo::ZeroInit<VkApplicationInfo>(VK_STRUCTURE_TYPE_APPLICATION_INFO);
        appInfo.pApplicationName = engineName;
        appInfo.applicationVersion = engineVersionFlags;
        appInfo.pEngineName = engineName;
        appInfo.engineVersion = engineVersionFlags;
        appInfo.apiVersion = VULKAN_API_VERSION;

        const SharedPtr<WindowSubsystem> windowSubsystem = GetSubsystem<WindowSubsystem>();

        Vector<const char*> extensions = windowSubsystem->GetMainWindow()->GetVulkanExtensions();
        if constexpr (EngineConfig::ENABLE_DEBUG_CAPABILITIES) {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
        instanceCreateInfo.enabledExtensionCount = extensions.size();


        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
        if constexpr (EngineConfig::ENABLE_DEBUG_CAPABILITIES) {
            debugMessengerCreateInfo = CreateInfo::ForDebugMessenger(DefaultDebugCallback);
            debugMessengerCreateInfo.pUserData = GetSubsystem<LogSubsystem>().get();

            instanceCreateInfo.ppEnabledLayerNames = VulkanSubsystem::REQUIRED_VALIDATION_LAYERS.data();
            instanceCreateInfo.enabledLayerCount = VulkanSubsystem::REQUIRED_VALIDATION_LAYERS.size();
            instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerCreateInfo;
        }
        else {
            instanceCreateInfo.ppEnabledLayerNames = nullptr;
            instanceCreateInfo.enabledLayerCount = 0;
        }


        if (auto r = vkCreateInstance(&instanceCreateInfo, nullptr, &instance); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create a Vulkan instance: {}", string_VkResult(r));
            return false;
        }

        return true;
    }

    bool VulkanSubsystem::CreateDebugMessenger() {
        auto createInfo = CreateInfo::ForDebugMessenger(DefaultDebugCallback);
        createInfo.pUserData = GetSubsystem<LogSubsystem>().get();

        // TODO: Replace this shit(KIWI_VK_CALL_) with more adequate code
        if (auto r = KIWI_VK_CALL_INST_EXT_FN(vkCreateDebugUtilsMessengerEXT, instance, &createInfo, nullptr, &debugMessenger); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create debug messenger: {}", string_VkResult(r));
            return false;
        }

        return true;
    }

    bool VulkanSubsystem::CreateSurface() {
        auto expectedSurface = CreateWindowSurface(
            instance,
            GetSubsystem<WindowSubsystem>()->GetMainWindow()
        );
        if (!expectedSurface) {
            KIWI_CTX_LOG(CRITICAL, "Failed to create a window surface: {}", string_VkResult(expectedSurface.error()));
            return false;
        }

        surface = *expectedSurface;
        return true;
    }

    bool VulkanSubsystem::CreateVulkanDevice() {
        device = MakeShared<Device>();

        return device->Init(TypeTags::UseVulkanSubsystemForInit{});
    }

    bool VulkanSubsystem::CreateSwapChain() {
        swapChain = MakeShared<SwapChain>();

        return swapChain->Init(TypeTags::UseVulkanSubsystemForInit{});
    }

    Vector<VkLayerProperties> VulkanSubsystem::GetAvailableValidationLayers() {
        if (!s_availableValidationLayers.empty()) {
            return s_availableValidationLayers;
        }

        u32 availableLayersCount = 0;
        vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

        s_availableValidationLayers.resize(availableLayersCount);
        vkEnumerateInstanceLayerProperties(&availableLayersCount, s_availableValidationLayers.data());

        return s_availableValidationLayers;
    }

    Status<Vector<String>> VulkanSubsystem::CheckRequiredValidationLayersForSupport() {
        const Vector<VkLayerProperties> availableLayers = GetAvailableValidationLayers();

        Set<StringView> availableLayersNamesSet;
        for (const auto& layer : availableLayers) {
            availableLayersNamesSet.emplace(layer.layerName);
        }

        Vector<String> unsupportedLayers;
        for (auto requiredLayer : REQUIRED_VALIDATION_LAYERS) {
            if (!availableLayersNamesSet.contains(requiredLayer)) {
                unsupportedLayers.emplace_back(requiredLayer);
            }
        }

        if (!unsupportedLayers.empty()) {
            return Unexpected(unsupportedLayers);
        }
        return {};
    }

    void VulkanSubsystem::DeInit() {
        Super::DeInit();

        // SwapChain
        swapChain.reset();

        // Surface
        vkDestroySurfaceKHR(instance, surface, nullptr);

        // Physical & Logical devices
        device.reset();

        // Debug utils
        // TODO: EXT
        KIWI_VK_CALL_INST_EXT_FN(vkDestroyDebugUtilsMessengerEXT, instance, debugMessenger, nullptr);

        // Instance
        vkDestroyInstance(instance, nullptr);
    }
}
