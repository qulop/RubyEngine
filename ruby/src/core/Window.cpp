#include "Window.hpp"


namespace Ruby
{
    // public:
    Window::Window(VideoAttr& va)
    { 
        Init(va);

        glfwSetWindowUserPointer(m_window.get(), this); 

        SetupCallbacks();
    }


    bool Window::Update(void)
    {        
        glClearColor(0.4f, 0.63f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window.get());

        return glfwWindowShouldClose(m_window.get());
    }


    void Window::PollEvents(void)
    { glfwPollEvents(); }


    SizeStruct Window::GetSize(void) const
    { 
        SizeStruct out;
        glfwGetWindowSize(m_window.get(), &out.width, &out.height);

        return out; 
    }


    inline SizeStruct Window::GetRealSize(void) const
    {
        SizeStruct out;
        glfwGetFramebufferSize(m_window.get(), &out.width, &out.height);

        return out; 
    }


    // private:
    void Window::Init(VideoAttr& va)
    {
        RUBY_ASSERT(va.width > 0 && va.height > 0 && "Width and(or) height cannot be least or equal zero!");
        RUBY_INFO("Window::Init: width({}), height({}), isFullScreened({}), isResizable({})",
                    va.width, va.height, va.isFullScreened, va.isResizable);

        if (!glfwInit())
        {
            RUBY_CRITICAL("GLFW error: failed to intialize GLFW -> !glfwInit()");
            return;
        }

        // Hints for GLFW windows
        if (!va.isResizable)
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // ------------------
        
        GLFWwindow* wnd = glfwCreateWindow(va.width, va.height, va.title.c_str(), nullptr, nullptr); 

        if (!m_window)
        {
            RUBY_CRITICAL("GLFW error: failed to create window");
            return;
        }

        m_window = std::shared_ptr<GLFWwindow>{ wnd, [](GLFWwindow* ptr)
                                                { 
                                                    glfwDestroyWindow(ptr); 
                                                    glfwTerminate(); 
                                                } };

        glfwMakeContextCurrent(m_window.get());    

        glViewport(0, 0, va.width, va.height); 

        if (!gladLoadGL())
        {
            RUBY_CRITICAL("Glad error: failed to load OpenGL -> !gladLoadGl()");
            return;
        }   

        RUBY_INFO("Window::Init() - OK");
    }


    void Window::SetupCallbacks(void)
    {
        glfwSetErrorCallback([](int err, const char* desc)
        { 
            RUBY_ERROR("GLFW {} error: {}", err, desc); 
        });
        

        glfwSetKeyCallback(m_window.get(), [](GLFWwindow*, int key, int scancode, int action, int mods)
        {
            // TODO
        });

        glfwSetMouseButtonCallback(m_window.get(), [](GLFWwindow*, int button, int action, int mods)
        { 
            if (action == GLFW_PRESS)
                getEventManager().Excite(MousePressEvent{ button });
            else
                getEventManager().Excite(MouseReleaseEvent{ button }); 
        });

        glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow*, double xpos, double ypos)
        { 
            getEventManager().Excite(MouseMoveEvent{ xpos, ypos }); 
        });


        glfwSetScrollCallback(m_window.get(), [](GLFWwindow*, double xpos, double ypos)
        {
            getEventManager().Excite(MouseScrollEvent{ xpos, ypos });
        });
    }


}