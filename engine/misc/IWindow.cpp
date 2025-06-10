#include "IWindow.hpp"

#include <platform/window/GLFWWindow.hpp>


namespace Ruby {
    SharedPtr<IWindow> IWindow::Create(VideoStruct vs) {
        return makeShared<GLFWWindow>(std::move(vs));
    }
}
