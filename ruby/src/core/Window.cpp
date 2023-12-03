#include "Window.hpp"


namespace Ruby
{
    // public:
    Window::Window(VideoAttr& va)
    { 
        Init(va);

        glfwSetWindowUserPointer(m_window, this); 

        // SetupGLFWCallbacks();
    }


    bool Window::Update(void)
    {
        glfwPollEvents();
        
        glClearColor(0.4f, 0.63f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shaderProgram);
        glBindVertexArray(m_vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(m_vao);

        glfwSwapBuffers(m_window);

        return glfwWindowShouldClose(m_window);
    }


    SizeStruct Window::GetSize(void) const
    { 
        SizeStruct out;
        glfwGetWindowSize(m_window, &out.width, &out.height);

        return out; 
    }


    inline SizeStruct Window::GetRealSize(void) const
    {
        SizeStruct out;
        glfwGetFramebufferSize(m_window, &out.width, &out.height);

        return out; 
    }


    Window::~Window(void)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }




    // private:
    void Window::Init(VideoAttr& va)
    {
        RUBY_ASSERT(va.width > 0 && va.height > 0 && "Width and(or) height cannot be least or equal zero!");

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
        
        m_window = glfwCreateWindow(va.width, va.height, va.title.c_str(), nullptr, nullptr);

        if (!m_window)
        {
            RUBY_CRITICAL("GLFW error: failed to initialize window -> glfwCreateWindow({}, {}, \"{}\", ...)",
                            va.width, va.height, va.title);
            return;
        }
        glfwMakeContextCurrent(m_window);    

        glViewport(0, 0, va.width, va.height); 

        if (!gladLoadGL())
        {
            RUBY_CRITICAL("Glad error: failed to load OpenGL -> !gladLoadGl()");
            return;
        }   

        RUBY_INFO("Window::Init() - OK");

        DrawTriangle();
    }


    // void Window::SetupGLFWCallbacks(void)
    // {
    //     glfwSetErrorCallback([](int err, const char* desc)
    //     { 
    //         CORE_ERROR("GLFW {} error: {}", err, desc); 
    //         fprintf_s(stderr, "GLFW %d error: %s", err, desc); 
    //     });

    //     glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods)
    //     {
    //         // if (action == GLFW_PRESS)
    //             // GetManager().Excite()
    //     });

    //     glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods)
    //     { 
    //         if (action == GLFW_PRESS)
    //             GetManager().Excite(MousePressEvent{ button });
    //         else
    //             GetManager().Excite(MouseReleaseEvent{ button }); 
    //     });

    //     glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
    //     { 
    //         GetManager().Excite(MouseMoveEvent{ xpos, ypos }); 
    //     });


    //     glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
    //     {
    //         GetManager().Excite(MouseScrollEvent{ xpos, ypos });
    //     });
    // }


}