#pragma once

#include <utility/Definitions.hpp>

#include <vulkan/vulkan.h>



namespace Kiwi::Vulkan {
    VkBool32 VKAPI_ATTR VKAPI_CALL DefaultDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData
    );


    class ValidationLayers {
    public:
    #ifdef KIWI_DEBUG_BUILD
        static constexpr bool ENABLE_LAYERS = true;
    #else
        static constexpr bool ENABLE_LAYERS = false;
    #endif

    public:
        KIWI_NODISCARD static Vector<VkLayerProperties> GetAvailableLayers();

        // @return Nothing(just a `has_value()` flag) **on success** or vector of unsupported **required** layer names **on failure**
        KIWI_NODISCARD static std::expected<void, Vector<String>> CheckForSupport(std::span<const String> requiredLayers);

        KIWI_NODISCARD static VkDebugUtilsMessengerCreateInfoEXT GetDefaultMessengerCreateInfo();

    };
}
