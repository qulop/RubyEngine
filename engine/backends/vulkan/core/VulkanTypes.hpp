#pragma once

#include <types/TypeTraits.hpp>

#include <vulkan/vulkan.h>


#define KIWI_VK_UNDEFINED_ID    (-1)


#define KIWI_VK_CALL_INST_EXT_FN(FnName, instance, ...)    \
    Kiwi::Vulkan::CallInstanceExtFunction<PFN_##FnName>(instance, KIWI_MAKE_STRING(FnName), __VA_ARGS__)


namespace Kiwi::Vulkan {
    VkBool32 VKAPI_ATTR VKAPI_CALL DefaultDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT severity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData  // Pointer to the LogSubsystem
    );


    template<typename TPfn, typename... Args>
    VkResult CallInstanceExtFunction(VkInstance instance, const char* funcName, Args&&... args) {
        auto pfnTarget = (TPfn)vkGetInstanceProcAddr(instance, funcName);
        if (!pfnTarget) {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }

        if constexpr (std::is_same_v<std::invoke_result_t<TPfn, VkInstance, Args...>, void>) {
            pfnTarget(instance, std::forward<Args>(args)...);
            return VK_SUCCESS;
        }
        else {
            return pfnTarget(instance, std::forward<Args>(args)...);
        }
    }
}