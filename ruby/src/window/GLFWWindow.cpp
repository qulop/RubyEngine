#include <window/GLFWWindow.hpp>

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <events/EventManager.hpp>
#include <graphics/Texture2D.hpp>


namespace Ruby::WinAgents
{
	GLFWWindow::GLFWWindow(const VideoStruct& vs)
	{
		Init(vs);

		glfwSetWindowUserPointer(m_window, this);

		SetupCallbacks();
	}

    void GLFWWindow::ChangePosition(i32 x, i32 y)
    {

    }

    void GLFWWindow::Resize(u32 x, u32 y)
    {

    }

    void GLFWWindow::ToCenter()
    {

    }

    void GLFWWindow::SetIcon(const Ruby::RubyString& path)
    {
        GLFWimage ico[1];
        ico[0].pixels = stbi_load(path.c_str(),
                                  &ico[0].width,
                                  &ico[0].height,
                                  nullptr,
                                  TextureParams::ImageFormat::DEFAULT);
        glfwSetWindowIcon(m_window, 1, ico);

        stbi_image_free(ico[0].pixels);
    }

    void GLFWWindow::SetTitle(const RubyString& title)
    { glfwSetWindowTitle(m_window, title.c_str()); }

    void GLFWWindow::PollEvents()
    { glfwPollEvents(); }

	bool GLFWWindow::Update() const
	{
        glfwSwapBuffers(m_window);

        return true;
	}

	SizeStruct GLFWWindow::GetSizes(bool isReal) const
	{
        SizeStruct out;
        if (isReal)
            glfwGetFramebufferSize(m_window, &out.width, &out.height);
        else
            glfwGetWindowSize(m_window, &out.width, &out.height);

       	return out; 
	}

	GLFWWindow::~GLFWWindow()
	{
        glfwDestroyWindow(m_window); 
        glfwTerminate();
	}



	void GLFWWindow::Init(const VideoStruct& vs)
	{
		RUBY_ASSERT(vs.width > 0 && vs.height > 0, "Width and(or) height cannot be least or equal zero!");
		RUBY_INFO("GLFWWindow::Init() : width({}), height({}), isFullScreened({})",
					vs.width, vs.height, vs.isFullScreened);

		if (!glfwInit())
		{
			RUBY_CRITICAL("GLFWWindow::Init() : GLFW critical error: failed to initialize GLFW -> !glfwInit()");
			return;
		}

		// Hints for GLFW windows
		// if (!va.isResizable)
		//     glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// ------------------

		GLFWmonitor* monitor = (vs.isFullScreened) ? glfwGetPrimaryMonitor() : nullptr;
		m_window = glfwCreateWindow(vs.width, vs.height, vs.title.c_str(), monitor, nullptr); 
		if (!m_window)
		{
			RUBY_CRITICAL("GLFWWindow::Init() : GLFW critical error: failed to create window -> !m_window");
			return;
		}

		glfwMakeContextCurrent(m_window);    

		if (!gladLoadGL())
		{
			RUBY_CRITICAL("GLFWWindow::Init() : Glad critical error: failed to load OpenGL -> !gladLoadGl()");
			return;
		}   

		glViewport(0, 0, vs.width, vs.height); 
		RUBY_INFO("GLFWWindow::Init() : OK.");
	}

	void GLFWWindow::SetupCallbacks()
	{
		glfwSetErrorCallback([](int err, const char* desc)
		{ 
			RUBY_ERROR("GLFW {} error: {}", err, desc); 
		});


		glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
                exciteEvent(KeyboardKeyPressed{ key, action });
            else
                exciteEvent(KeyboardKeyReleased{ key, action });
        });


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods)
		{ 
			if (action == GLFW_PRESS)
                exciteEvent(MousePressEvent{ button });
			else
                exciteEvent(MouseReleaseEvent{ button });
		});


		glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
		{  exciteEvent(MouseMoveEvent{ xpos, ypos });  });


		glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos)
		{  exciteEvent(MouseScrollEvent{ xpos, ypos });  });
	}
}