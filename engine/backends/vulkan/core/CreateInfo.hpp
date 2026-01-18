#pragma once

#include <utility/Definitions.hpp>

#include <types/Concepts.hpp>

#include <vulkan/vulkan.h>


namespace Kiwi::Vulkan {
    template<typename T>
    KIWI_NODISCARD T GetBasicCreateInfo(VkStructureType type) {
        T createInfo = {};
        createInfo.sType = type;
        createInfo.pNext = nullptr;

        return createInfo;
    }


    enum class EVulkanCreateInfo {
        DEBUG_UTILS_MESSENGER,
        DEVICE,
        DEVICE_QUEUE
    };


    template<EVulkanCreateInfo T>
    struct CreateInfoFor;


    template<>
    struct CreateInfoFor<EVulkanCreateInfo::DEBUG_UTILS_MESSENGER> {
        KIWI_NODISCARD static VkDebugUtilsMessengerCreateInfoEXT Get(PFN_vkDebugUtilsMessengerCallbackEXT callback) {
            auto severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            auto msgType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;


            VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            createInfo.pNext = nullptr;
            createInfo.messageSeverity = severity;
            createInfo.messageType = msgType;
            createInfo.pfnUserCallback = callback;
            createInfo.pUserData = nullptr;

            return createInfo;
        }
    };



}