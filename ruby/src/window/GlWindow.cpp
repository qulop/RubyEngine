#include <window/GlWindow.hpp>

#include <utility/Definitions.hpp>
#include <utility/Logger.hpp>
#include <event/RubyEvents.hpp>


namespace Ruby::WinAgents
{
	GLWindow::GLWindow(VideoStruct&& vs)
	{
		Init(std::move(vs));

		glfwSetWindowUserPointer(m_window, this);

		SetupCallbacks();
	}
	

	bool GLWindow::Update(void)
	{
        glfwSwapBuffers(m_window);

        return true;
	}


	SizeStruct GLWindow::GetSize(bool isReal)
	{
       	SizeStruct out;
	   	if (isReal)
			glfwGetFramebufferSize(m_window, &out.width, &out.height);
		else
    		glfwGetWindowSize(m_window, &out.width, &out.height);

       	return out; 
	}

	
	GLWindow::~GLWindow()
	{
        glfwDestroyWindow(m_window); 
        glfwTerminate();
	}


	void GLWindow::PollEvents(void)
	{ glfwPollEvents(); }


	SizeStruct GLWindow::GetScreenResolution(void)
	{
		const GLFWvidmode* tmp = glfwGetVideoMode(glfwGetPrimaryMonitor());

		return SizeStruct{ tmp->height, tmp->width };
	}


// private
	void GLWindow::Init(VideoStruct&& vs)
	{
		RUBY_ASSERT(vs.width > 0 && vs.height > 0 && "Width and(or) height cannot be least or equal zero!");
		RUBY_INFO("GLWindow::Init: width({}), height({}), isFullScreened({})",
					vs.width, vs.height, vs.isFullScreened);

		if (!glfwInit())
		{
			RUBY_CRITICAL("GLWindow::Init: GLFW critical error: failed to intialize GLFW -> !glfwInit()");
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
			RUBY_CRITICAL("GLWindow::Init: GLFW critical error: failed to create window -> !m_window");
			return;
		}

		glfwMakeContextCurrent(m_window);    

		if (!gladLoadGL())
		{
			RUBY_CRITICAL("GLWindow::Init: Glad criritical error: failed to load OpenGL -> !gladLoadGl()");
			return;
		}   

		glViewport(0, 0, vs.width, vs.height); 
		RUBY_INFO("Window::Init() - OK.");
	}


	void GLWindow::SetupCallbacks()
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
}