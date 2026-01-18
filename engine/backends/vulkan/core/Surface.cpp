#include "Surface.hpp"

#include <misc/WindowSubsystem.hpp>
#include <platform/Platform.hpp>

#include <vulkan/vk_enum_string_helper.h>


namespace Kiwi::Vulkan {
    bool Surface::CreateSurface(VkInstance instance) {
        auto expectedSurface = CreateWindowSurface(
            instance,
            GetSubsystem<WindowSubsystem>()->GetMainWindow()
        );
        if (!expectedSurface) {
            KIWI_CTX_LOG(CRITICAL, "Failed to create a window surface: {}", string_VkResult(expectedSurface.error()));
            return false;
        }

        return true;
    }

    VkBool32 Surface::DoesQueueSupportPresentation(VkPhysicalDevice physicalDevice, u32 queueIdx) const {
        VkBool32 result = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueIdx, m_vkSurface, &result);

        return result;
    }

    VkSurfaceKHR Surface::GetSurface() const {
        return m_vkSurface;
    }

    Surface::operator VkSurfaceKHR() const {
        return GetSurface();
    }
}
