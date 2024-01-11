#include "Window.hpp"


namespace Ruby
{
// public:
    Window::Window(VideoAttr& va)
    { 
        Init(va);

        glfwSetWindowUserPointer(m_window, this); 

        SetupCallbacks();

        Test();
    }


    bool Window::Update(void)
    {        
        glClearColor(0.4f, 0.63f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(m_window);

        return true;
    }


    void Window::PollEvents(void)
    { glfwPollEvents(); }


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


    Window::~Window()
    {
        glfwDestroyWindow(m_window); 
        glfwTerminate();
    } 



// private:
    void Window::Init(VideoAttr& va)
    {
        RUBY_ASSERT(va.width > 0 && va.height > 0 && "Width and(or) height cannot be least or equal zero!");
        RUBY_INFO("Window::Init: width({}), height({}), isFullScreened({})",
                    va.width, va.height, va.isFullScreened);

        if (!glfwInit())
        {
            RUBY_CRITICAL("GLFW critical error: failed to intialize GLFW -> !glfwInit()");
            return;
        }

        // Hints for GLFW windows
        // if (!va.isResizable)
        //     glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // ------------------
        
        GLFWmonitor* monitor = (va.isFullScreened) ? glfwGetPrimaryMonitor() : nullptr;
        m_window = glfwCreateWindow(va.width, va.height, va.title.c_str(), monitor, nullptr); 
        if (!m_window)
        {
            RUBY_CRITICAL("GLFW critical error: failed to create window -> !m_window");
            return;
        }

        glfwMakeContextCurrent(m_window);    

        if (!gladLoadGL())
        {
            RUBY_CRITICAL("Glad criritical error: failed to load OpenGL -> !gladLoadGl()");
            return;
        }   

        glViewport(0, 0, va.width, va.height); 
        RUBY_INFO("Window::Init() - OK.");

    }


    void Window::SetupCallbacks(void)
    {
        glfwSetErrorCallback([](int err, const char* desc)
        { 
            RUBY_ERROR("GLFW {} error: {}", err, desc); 
        });
        

        glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods)
        {
            // TODO
        });


        glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods)
        { 
            if (action == GLFW_PRESS)
                 getEventManager().Excite(MousePressEvent{ button });
            else
                getEventManager().Excite(MouseReleaseEvent{ button }); 
        });


        glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
        { 
            getEventManager().Excite(MouseMoveEvent{ xpos, ypos }); 
        });


        glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
        {
            getEventManager().Excite(MouseScrollEvent{ xpos, ypos });
        });
    }


    void Window::Test(void)
    {
        // mng.EmplaceShader(RubyString{ "shaders/Vertex.glsl" }, GL_VERTEX_SHADER);
        // mng.EmplaceShader(RubyString{ "shaders/Fragment.glsl" }, GL_FRAGMENT_SHADER);

        mng.CreateProgram();

        constexpr GLfloat vert[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), static_cast<GLvoid*>(0));
        glEnableVertexAttribArray(0);

        mng.UseProgram();
    }
}