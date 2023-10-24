#include "Window.hpp"


namespace Ruby
{
    void RUBY_API getScreenResolution(int& w, int& h)
    {
        const GLFWvidmode* tmp = glfwGetVideoMode(glfwGetPrimaryMonitor()); 
        
        w = tmp->width;
        h = tmp->height;
    }

    Window::Window(WindowAttributes& wa)
    { 
        Init(wa);
        glfwSetWindowUserPointer(m_window, this); 

        // EventManager::Get().AddListener(EventType::MOUSE_MOVED_EVENT, std::bind_front(Window::OnEvent));

        glfwSetErrorCallback([](int err, const char* desc)
        { 
            CORE_ERROR("GLFW {} error: {}", err, desc); 
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
        { 
            EventManager::Get().Excite(MousePressEvent{ button }); 
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
        { 
            EventManager::Get().Excite(MouseMoveEvent{ xpos, ypos }); 
        });
    }


    void Window::Init(WindowAttributes& wa)
    {
        if (!glfwInit())
        {
            CORE_CRITICAL("GLFW error: failed to intialize GLFW");
            return;
        }

        if (wa.width == -1 || wa.height == -1)
            getScreenResolution(wa.width, wa.height);

        m_window = glfwCreateWindow(wa.width, wa.height, wa.title.c_str(), wa.monitor, nullptr);
        if (!m_window)
        {
            CORE_CRITICAL("GLFW error: failed to initialize window");
            return;
        }
        glfwMakeContextCurrent(m_window);        
    }


    void Window::Update(void)
    {
        printf("OpenGL ver: %s", glGetString(GL_VERSION));

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(m_window);
    }


    void Window::OnEvent(MouseMoveEvent& event)
    {
        if (event.GetType() == EventType::MOUSE_MOVED_EVENT)
            fprintf_s(stdout, "Window::OnEvent(Event&) worked!\n");
    }



    Window::~Window(void)
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

}