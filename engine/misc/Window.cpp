#include "Window.hpp"

#include <platform/window/GLFWWindow.hpp>
#include <platform/Platform.hpp>
#include <types/Logger.hpp>


namespace Kiwi {
    SharedPtr<AWindow> AWindow::CreateWindowImpl() {
        // At the moment we have only implementation for GLFW 🥲
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return MakeShared<GLFWWindow>();
        }

        KIWI_CRITICAL("IWindow::CreateWindowImpl() : Failed to create a window implementation - your platform is not supported");
        return nullptr;
    }

    void AWindow::ToCenter() const {
        // TODO: Rework this!
        Platform::DisplayInfo primaryDisplay = Platform::GetPrimaryDisplay().value();
        auto centerVec = GetWindowSizes().Center();

        i32 cx = (primaryDisplay.resolution.x / 2) - centerVec.x;
        i32 cy = (primaryDisplay.resolution.y / 2) - centerVec.y;

        ChangePosition(cx, cy);
    }

    bool AWindow::Update() {
        PollEvents();
        SwapBuffers();

        return !IsWindowClosed();
    }

    bool AWindow::IsMaximized() const {
        return m_isMaximized.load();
    }

    size_t AWindow::GetWidth() const {
        return GetWindowSizes().Width();
    }

    size_t AWindow::GetFramebufferWidth() const {
        return GetFramebufferSizes().Width();
    }

    size_t AWindow::GetHeight() const {
        return GetWindowSizes().Height();
    }

    size_t AWindow::GetFramebufferHeight() const {
        return GetFramebufferSizes().Height();
    }
}
