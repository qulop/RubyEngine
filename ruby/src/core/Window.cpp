#include <core/Window.hpp>


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h)
    {
        const GLFWvidmode* tmp = glfwGetVideoMode(glfwGetPrimaryMonitor());
        w = tmp->width;
        h = tmp->height;

        delete tmp;
    }


    void setGlfwErrCallback(int err, const char* desc)
    {
        fprintf_s(stderr, "GLFW %d error: %s\n", err, desc);
    }


    Window::Window(void)
    {
        WindowAttrubutes wa;
        init(wa);
    }


    Window::Window(WindowAttrubutes& wa)
    { init(wa); }


    void Window::init(WindowAttrubutes& wa)
    {
        auto err = glfwInit();
        if (err != GLFW_TRUE)
        {
            fprintf_s(stderr, "GLFW error: failed to intialize GLFW.\n");
            return;
        }
        glfwSetErrorCallback(setGlfwErrCallback);


        if (wa.width == -1 && wa.height == -1)
            getScreenResolution(wa.width, wa.height);

        m_window = glfwCreateWindow(wa.width, wa.height, wa.title, wa.monitor, nullptr);
        if (!m_window)
        {
            fprintf_s(stderr, "GLFW error: failed to initialize window\n");
            return;
        }

        glfwMakeContextCurrent(m_window);
    }


    void Window::showWindow(void)
    {
        while (!glfwWindowShouldClose(m_window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
    }


    Window& Window::operator=(WindowAttrubutes& wa)
    {
        init(wa);

        return *this;
    }


    Window::~Window(void)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

}