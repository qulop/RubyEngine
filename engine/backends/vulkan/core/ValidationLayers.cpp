#include "ValidationLayers.hpp"

#include <types/TypeTraits.hpp>
#include <types/Logger.hpp>
#include <vulkan/vk_enum_string_helper.h>


namespace Kiwi::Vulkan {
    VkBool32 DefaultDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        KIWI_MAYBE_UNUSED void* userData
    )
    {


        KIWI_WARNING("Vulkan Validation Layers:\n\tSeverity: {}\n\tType: {}\n\tMessage: {}",
            string_VkDebugUtilsMessageSeverityFlagsEXT(severity),
            string_VkDebugUtilsMessageTypeFlagsEXT(messageType),
            callbackData->pMessage
        );

        return VK_FALSE;
    }



    Vector<VkLayerProperties> ValidationLayers::GetAvailableLayers() {
        u32 availableLayersCount = 0;
        vkEnumerateInstanceLayerProperties(&availableLayersCount, nullptr);

        Vector<VkLayerProperties> layers(availableLayersCount);
        vkEnumerateInstanceLayerProperties(&availableLayersCount, layers.data());

        return layers;
    }

    std::expected<void, Vector<String>> ValidationLayers::CheckForSupport(const std::span<const String> requiredLayers) {
        const auto availableLayers = GetAvailableLayers();

        Set<StringView> availableLayersNamesSet;
        for (const auto& layer : availableLayers) {
            availableLayersNamesSet.emplace(StringView{ layer.layerName });
        }

        Vector<String> unsupportedLayers;
        for (auto requiredLayer : requiredLayers) {
            if (!availableLayersNamesSet.contains(requiredLayer)) {
                unsupportedLayers.emplace_back(requiredLayer);
            }
        }

        if (!unsupportedLayers.empty()) {
            return std::unexpected(unsupportedLayers);
        }
        return {};
    }

    VkDebugUtilsMessengerCreateInfoEXT ValidationLayers::GetDefaultMessengerCreateInfo() {
        auto severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        auto msgType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;


        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.pNext = nullptr;
        createInfo.messageSeverity = severity;
        createInfo.messageType = msgType;
        createInfo.pfnUserCallback = DefaultDebugCallback;
        createInfo.pUserData = nullptr;

        return createInfo;
    }
}
