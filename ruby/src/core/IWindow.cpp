#include <core/IWindow.hpp>
#include <window/GLFWWindow.hpp>


namespace Ruby
{
    Ptr<IWindow> IWindow::Create(const Ruby::VideoStruct& vs)
    {
        return std::make_shared<GLFWWindow>(vs);
    }

}
