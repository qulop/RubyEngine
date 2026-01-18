#include "RenderInstanceVK.hpp"

#include <backends/vulkan/core/VulkanSubsystem.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>
#include <backends/vulkan/core/VulkanTypes.hpp>

#include <core/EngineConfig.hpp>
#include <core/LogSubsystem.hpp>

#include <misc/WindowSubsystem.hpp>

#include <types/String.hpp>


#include <vulkan/vk_enum_string_helper.h>



namespace Kiwi::Vulkan {
    bool RenderInstanceVK::Init() {
        RegisterSubsystem<VulkanSubsystem>();

        return CreateInstance() && CreateDebugMessenger();
    }

    EGraphicAPI RenderInstanceVK::GetUsedAPI() const {
        return EGraphicAPI::Vulkan;
    }

    bool RenderInstanceVK::SetupDebugLayerCallback(const PFN_DebugCallback &debugCallback) {
        return true;
    }

    void RenderInstanceVK::Destroy() {
        Super::Destroy();

        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            KIWI_VK_CALL_INST_EXT_FN(vkDestroyDebugUtilsMessengerEXT, m_vkInstance, m_vkDebugMessenger, nullptr);
        }

        vkDestroyInstance(m_vkInstance, nullptr);
    }

    VkInstance RenderInstanceVK::GetVulkanInstance() const {
        return m_vkInstance;
    }

    bool RenderInstanceVK::CreateInstance() {
        auto vulkanSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vulkanSubsystem);

        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            auto checkRes = vulkanSubsystem->CheckRequiredValidationLayersForSupport();
            if (!checkRes.has_value()) {
                KIWI_CTX_LOG(ERROR, "These layers aren't supported, but required: ( {} )",
                    StringUtils::Join(checkRes.error(), /*sep = */ ',')
                );
                return false;
            }
        }

        const char* engineName = EngineConfig::ENGINE_NAME.c_str();
        constexpr u32 engineVersionFlags = EngineConfig::ENGINE_VERSION.GetFlags();

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = engineName;
        appInfo.applicationVersion = engineVersionFlags;
        appInfo.pEngineName = engineName;
        appInfo.engineVersion = engineVersionFlags;
        appInfo.apiVersion = VulkanSubsystem::VULKAN_API_VERSION;

        SharedPtr windowSubsystem = GetSubsystem<WindowSubsystem>();

        Vector<const char*> extensions = windowSubsystem->GetMainWindow()->GetVulkanExtensions();
        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        auto requiredLayersRaw = vulkanSubsystem->GetRequiredValidationLayersRaw();

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
        instanceCreateInfo.enabledExtensionCount = extensions.size();


        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            debugMessengerCreateInfo = CreateInfoFor<EVulkanCreateInfo::DEBUG_UTILS_MESSENGER>::Get(
                DefaultDebugCallback
            );
            debugMessengerCreateInfo.pUserData = GetSubsystem<LogSubsystem>().get();

            instanceCreateInfo.ppEnabledLayerNames = requiredLayersRaw.data();
            instanceCreateInfo.enabledLayerCount = requiredLayersRaw.size();
            instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerCreateInfo;
        }
        else {
            instanceCreateInfo.ppEnabledLayerNames = nullptr;
            instanceCreateInfo.enabledLayerCount = 0;
        }


        if (auto r = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkInstance); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create a Vulkan instance: {}", string_VkResult(r));
            return false;
        }

        return true;
    }

    bool RenderInstanceVK::CreateDebugMessenger() {
        auto vulkanSubsystem = GetSubsystem<VulkanSubsystem>();
        KIWI_ENSURE(vulkanSubsystem);

        auto createInfo = CreateInfoFor<EVulkanCreateInfo::DEBUG_UTILS_MESSENGER>::Get(
            DefaultDebugCallback
        );
        createInfo.pUserData = GetSubsystem<LogSubsystem>().get();


        if (auto r = KIWI_VK_CALL_INST_EXT_FN(vkCreateDebugUtilsMessengerEXT, m_vkInstance, &createInfo, nullptr, &m_vkDebugMessenger); r != VK_SUCCESS) {
            KIWI_CTX_LOG(ERROR, "Failed to create debug messenger: {}", string_VkResult(r));
            return false;
        }
        
        return true;
    }
}
