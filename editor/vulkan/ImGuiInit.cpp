#include <gui/ImGuiSubsystem.hpp>

#include <misc/Window.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>



namespace Kiwi::Vulkan::Editor {
    ExpectedStatus<Error<EGeneralError>> InitPlatformForImGui(SharedPtr<AWindow> mainWindow) {
        KIWI_ASSERT_BASIC(mainWindow);

        if (mainWindow->GetVendor() == EWindowVendor::GLFW) {
            ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)mainWindow->GetNativeWindowPtr(), true);
        }
        else {
            std::unreachable();
        }


        ImGui_ImplVulkan_InitInfo initInfo = {

        };
    }

}
