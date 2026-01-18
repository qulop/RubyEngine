#include <backends/vulkan/core/Surface.hpp>
#include <backends/vulkan/core/CreateInfo.hpp>

#include <misc/Window.hpp>
#include <platform/Platform.hpp>

#include <GLFW/glfw3.h>

#include <vulkan/vulkan_win32.h>
#include <Windows.h>



namespace Kiwi::Vulkan::Win32 {
    Expected<VkSurfaceKHR, VkResult> CreateWindowSurface(VkInstance instance, SharedPtr<AWindow> wnd) {
        VkSurfaceKHR surface = VK_NULL_HANDLE;

        if (wnd->GetVendor() == EWindowVendor::GLFW) {
            auto* glfwWindow = (GLFWwindow*)wnd->GetNativeWindowPtr();

            if (auto r = glfwCreateWindowSurface(instance, glfwWindow, nullptr, &surface); r != VK_SUCCESS) {
                return Unexpected(r);
            }
        }
        else {
            auto createInfo = GetBasicCreateInfo<VkWin32SurfaceCreateInfoKHR>(VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR);
            createInfo.hwnd = wnd->GetNativeWindowHandle().handle;
            createInfo.hinstance = GetModuleHandle(nullptr);

            if (auto r = vkCreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface); r != VK_SUCCESS) {
                return Unexpected(r);
            }
        }

        return surface;
    }
}
