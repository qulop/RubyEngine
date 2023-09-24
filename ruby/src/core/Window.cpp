#include <core/Window.hpp>


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h)
    {
        const GLFWvidmode* tmp = glfwGetVideoMode(glfwGetPrimaryMonitor()); 
        
        w = tmp->width;
        h = tmp->height;
    }


    void setGlfwErrCallback(int err, const char* desc)
    { CORE_ERROR("GLFW {} error: {}", err, desc); }


    Window::Window(void)
    {
        WindowAttributes wa;
        Init(wa);
    }


    Window::Window(WindowAttributes& wa)
    { Init(wa); }


    void Window::Init(WindowAttributes& wa)
    {
        if (!glfwInit())
        {
            CORE_CRITICAL("GLFW error: failed to intialize GLFW");
            return;
        }
        glfwSetErrorCallback(setGlfwErrCallback);

        if (wa.width == -1 && wa.height == -1)
            getScreenResolution(wa.width, wa.height);

        m_window = glfwCreateWindow(wa.width, wa.height, wa.title.c_str(), wa.monitor, nullptr);
        if (!m_window)
        {
            CORE_CRITICAL("GLFW error: failed to initialize window");
            return;
        }
        glfwMakeContextCurrent(m_window);
    }


    void Window::ShowWindow(void)
    {
        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }


    Window& Window::operator=(WindowAttributes& wa)
    {
        Init(wa);

        return *this;
    }


    Window::~Window(void)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

}