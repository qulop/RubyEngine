#include "Window.hpp"


namespace Ruby
{
    // public:
    Window::Window(VideoAttr& va)
    { 
        Init(va);

        glfwSetWindowUserPointer(m_window, this); 

        SetupGLFWCallbacks();
    }


    bool Window::Update(void)
    {
        glfwPollEvents();
        
        glClearColor(0.4f, 0.63f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(m_window);

        return glfwWindowShouldClose(m_window);
    }


    SizeStruct Window::GetSize(void) const
    { 
        SizeStruct out;
        glfwGetWindowSize(m_window, &out.width, &out.height);

        return out; 
    }


    SizeStruct Window::GetRealSize(void) const
    {
        SizeStruct out;
        glfwGetFramebufferSize(m_window, &out.width, &out.height);

        return out; 
    }

    void Window::DrawTriangle(const std::array<int, 6>& coords)
    {
        // auto ndcCoords = toNDC(coords, GetRealSize());
        std::array<GLfloat, 9> coords = { 
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, coords.size(), coords.data(), GL_STATIC_DRAW);

        const GLchar* vertexShader =    "#version 330 core \n"
                                        "layout (location = 0) in vec3 position; \n"
                                        "void main() { \n"
                                        "gl_Position = vec4(position.x, position.y, position.z, 1.0); }";
        buildOpenglShader(GL_VERTEX_SHADER, vertexShader);

        const GLchar* fragmentShader =  "#version 330 core \n"
                                        "out vec4 color; \n"
                                        "void main() { \n"
                                        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f); }";
        buildOpenglShader(GL_FRAGMENT_SHADER, fragmentShader);
            
        

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
            CORE_CRITICAL("GLFW error: failed to intialize GLFW");
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
            CORE_CRITICAL("GLFW error: failed to initialize window");
            return;
        }
        glfwMakeContextCurrent(m_window);    

        glViewport(0, 0, va.width, va.height); 

        if (!gladLoadGL())
        {
            CORE_CRITICAL("Glad error: failed to load OpenGL");
            fprintf(stderr, "failed glad\n");
            return;
        }   
    }


    void Window::SetupGLFWCallbacks(void)
    {
        glfwSetErrorCallback([](int err, const char* desc)
        { 
            CORE_ERROR("GLFW {} error: {}", err, desc); 
            fprintf_s(stderr, "GLFW %d error: %s", err, desc); 
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods)
        {
            // if (action == GLFW_PRESS)
                // GetManager().Excite()
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods)
        { 
            if (action == GLFW_PRESS)
                GetManager().Excite(MousePressEvent{ button });
            else
                GetManager().Excite(MouseReleaseEvent{ button }); 
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
        { 
            GetManager().Excite(MouseMoveEvent{ xpos, ypos }); 
        });


        glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
        {
            GetManager().Excite(MouseScrollEvent{ xpos, ypos });
        });
    }


}