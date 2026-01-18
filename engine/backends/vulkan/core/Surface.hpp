#pragma once

#include <backends/vulkan/core/VulkanSubsystem.hpp>


namespace Kiwi {
    KIWI_ABSTRACT class AWindow;
}


namespace Kiwi::Vulkan {
    Expected<VkSurfaceKHR, VkResult> CreateWindowSurface(VkInstance instance, SharedPtr<AWindow> wnd);


    class Surface : public AObject {
        KIWI_CREATE_OBJECT(Surface)

    public:
        KIWI_NODISCARD bool CreateSurface(VkInstance instance);

        KIWI_NODISCARD VkBool32 DoesQueueSupportPresentation(VkPhysicalDevice physicalDevice, u32 queueIdx) const;

        KIWI_NODISCARD VkSurfaceKHR GetSurface() const;
        explicit operator VkSurfaceKHR() const;

    private:
        VkSurfaceKHR m_vkSurface = VK_NULL_HANDLE;
    };
}