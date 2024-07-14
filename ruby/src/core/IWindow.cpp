#include <core/IWindow.hpp>
#include "GLFWWindow.hpp"


namespace Ruby
{
    Ptr<IWindow> IWindow::Create(VideoStruct vs) {
        return MakePtr<GLFWWindow>(std::move(vs));
    }
}
