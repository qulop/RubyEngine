#pragma once

#include <types/TypeTraits.hpp>
#include <types/cast/Cast.hpp>

#include <math/Rect.hpp>

#include <vulkan/vulkan.h>


#define KIWI_VK_UNDEFINED_ID    (-1)


#define KIWI_VK_CALL_INST_EXT_FN(FnName, instance, ...)    \
    Kiwi::Vulkan::CallInstanceExtFunction<PFN_##FnName>(instance, KIWI_MAKE_STRING(FnName), __VA_ARGS__)


namespace Kiwi {
    template<>
    struct CastTraits<U32Rect> {
        KIWI_NODISCARD static VkViewport ToVkViewport(U32Rect rect) {
            VkViewport viewport = {};
            viewport.x = rect.topLeft.x;
            viewport.y = rect.topLeft.y;
            viewport.width = rect.Width();
            viewport.height = rect.Height();
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            return viewport;
        }

        KIWI_NODISCARD static VkRect2D ToVkRect2D(U32Rect rect) {
            VkRect2D rect2D = {};
            rect2D.offset.x = (f32)rect.topLeft.x;
            rect2D.offset.y = (f32)rect.topLeft.y;
            rect2D.extent.width = (f32)rect.Width();
            rect2D.extent.height = (f32)rect.Height();

            return rect2D;
        }
    };
}


namespace Kiwi::Vulkan::TypeTags {
    struct UseVulkanSubsystemForInit {};
}


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


    template<typename TResult, std::invocable<u32*, TResult*> TFunction>
    KIWI_NODISCARD Vector<TResult> EnumerateVulkanArray(TFunction&& fn) {
        u32 c = 0;
        std::invoke(std::forward<TFunction>(fn), &c, nullptr);

        Vector<TResult> r(c);
        std::invoke(std::forward<TFunction>(fn), &c, r.data());

        return r;
    }
}