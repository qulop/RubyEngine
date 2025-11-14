#include "IWindow.hpp"

#include <platform/window/GLFWWindow.hpp>
#include <types/Logger.hpp>


namespace Ruby {
    SharedPtr<IWindow> IWindow::CreateWindowImpl() {
        // At the moment we have only implementation for GLFW 🥲
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return MakeShared<GLFWWindow>();
        }

        RUBY_CRITICAL("IWindow::CreateWindowImpl() : Failed to create a window implementation - your platform is not supported");
        return nullptr;
    }
}
