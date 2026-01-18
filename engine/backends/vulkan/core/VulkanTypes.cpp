#include "VulkanTypes.hpp"

#include <core/LogSubsystem.hpp>

#include <vulkan/vk_enum_string_helper.h>



namespace Kiwi::Vulkan {
    VkBool32 VKAPI_ATTR VKAPI_CALL DefaultDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData  // Pointer to the LogSubsystem
    )
    {
        const auto* logSubsystem = static_cast<LogSubsystem*>(userData);
        logSubsystem->Log(ELogLevel::WARNING_LOG, "Vulkan Validation Layers:\n\tSeverity: {}\n\tType: {}\n\tMessage: {}",
            string_VkDebugUtilsMessageSeverityFlagsEXT(severity),
            string_VkDebugUtilsMessageTypeFlagsEXT(messageType),
            callbackData->pMessage
        );

        return VK_FALSE;
    }
}
