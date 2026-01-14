#include "Window.hpp"

#include <platform/window/GLFWWindow.hpp>
#include <platform/Platform.hpp>


namespace Kiwi {
    SharedPtr<AWindow> AWindow::CreateWindowImpl() {
        // At the moment we have only implementation for GLFW 🥲
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return MakeShared<GLFWWindow>();
        }

        std::unreachable();
    }

    void AWindow::ToCenter() const {
        if (auto primaryDisplay = Platform::GetPrimaryDisplay()) {
            const I32Vec2 centerVec = GetWindowSizes().Center();

            const i32 cx = (CastTo<i32>(primaryDisplay->resolution.x) / 2) - centerVec.x;
            const i32 cy = (CastTo<i32>(primaryDisplay->resolution.y) / 2) - centerVec.y;

            ChangePosition(cx, cy);
        }
        else {
            KIWI_CTX_LOG(ERROR, "Failed to get window size");
        }
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
