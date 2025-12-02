#include "RenderInstanceVK.hpp"

#include <backends/vulkan/core/ValidationLayers.hpp>

#include <core/EngineConfig.hpp>

#include <misc/WindowSubsystem.hpp>

#include <types/Logger.hpp>
#include <types/String.hpp>

#include <vulkan/vk_enum_string_helper.h>



namespace Kiwi::Vulkan {
    bool RenderInstanceVK::Init() {
        m_vkCore = MakeShared<VulkanCore>();
        if (!m_vkCore) {
            KIWI_ERROR("RenderInstanceVK::Init() : Failed to allocate VulkanCore instance");
            return false;
        }

        const auto requiredValidationLayers = m_vkCore->GetRequiredValidationLayers();
        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            auto checkRes = ValidationLayers::CheckForSupport(requiredValidationLayers);
            if (!checkRes.has_value()) {
                KIWI_ERROR("RenderInstanceVK::Init(): These layers aren't supported, but required: ( {} )",
                    StringUtils::Join(checkRes.error(), /*sep = */ ',')
                );
                return false;
            }
        }

        auto&& [engineName, engineVersion] = EngineConfig::GetDefaultInfo();
        auto engineVersionVk = VK_MAKE_VERSION(engineVersion.GetMajor(), engineVersion.GetMinor(), engineVersion.GetPatch());

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = engineName.c_str();
        appInfo.applicationVersion = engineVersionVk;
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = engineVersionVk;
        appInfo.apiVersion = VulkanCore::VULKAN_API_VERSION;

        auto windowSubsystem = GetSubsystem<WindowSubsystem>();
        Vector<const char*> extensions = windowSubsystem->GetVulkanExtensionsForWindow(windowSubsystem->GetMainWindow());

        VkInstanceCreateInfo instanceCreateInfo = {};
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pNext = nullptr;
        instanceCreateInfo.flags = 0;
        instanceCreateInfo.pApplicationInfo = &appInfo;
        instanceCreateInfo.ppEnabledExtensionNames = extensions.data();
        instanceCreateInfo.enabledExtensionCount = extensions.size();

        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
        auto requiredLayersRaw = requiredValidationLayers
                | std::views::transform([](auto const& s) { return s.c_str(); })
                | std::ranges::to<Vector<const char*>>();

        if constexpr (ENABLE_DEBUG_CAPABILITIES) {
            debugMessengerCreateInfo = ValidationLayers::GetDefaultMessengerCreateInfo();

            instanceCreateInfo.ppEnabledExtensionNames = requiredLayersRaw.data();
            instanceCreateInfo.enabledLayerCount = requiredValidationLayers.size();
            instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugMessengerCreateInfo;
        }
        else {
            instanceCreateInfo.ppEnabledExtensionNames = nullptr;
            instanceCreateInfo.enabledLayerCount = 0;
        }


        if (VkResult r = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkInstance); r != VK_SUCCESS) {
            KIWI_ERROR("RenderInstanceVK::Init(): Failed to create a Vulkan instance: {}", string_VkResult(r));
            return false;
        }

        return true;
    }

    EGraphicAPI RenderInstanceVK::GetUsedAPI() const {
        return EGraphicAPI::Vulkan;
    }
}
