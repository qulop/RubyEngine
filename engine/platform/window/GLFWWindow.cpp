#include "GLFWWindow.hpp"

#include <utility/Definitions.hpp>
#include <types/Logger.hpp>
#include <events/EventManager.hpp>
#include <graphics/Texture2D.hpp>
#include <platform/Platform.hpp>
#include <utility/Assert.hpp>


namespace Ruby {
	GLFWWindow::GLFWWindow(VideoStruct vs) {
        glfwSetErrorCallback([](int err, const char* desc) {
            RUBY_ASSERT(Logger::GetInstance().IsInitialized(), "Logger should be initialized before window creation!");

            RUBY_ERROR("glfwSetErrorCallback(): {} ... {}", err, desc);
        });

		Init(std::move(vs));

        glfwSetWindowUserPointer(m_window, this);
        SetupCallbacks();
	}


    void GLFWWindow::ChangePosition(i32 x, i32 y) const {
        glfwSetWindowPos(m_window, x, y);
    }


    void GLFWWindow::Resize(i32 width, i32 height) {
        RUBY_ASSERT_BASIC(width > 0 && height > 0);
        glViewport(0, 0, width, height);
    }


    void GLFWWindow::ToCenter() const {
	    // TODO: Rework this!
        Platform::DisplayInfo primaryDisplay = Platform::GetPrimaryDisplay().value();
        auto [winX, winY] = GetSizes(/*framebufferSizes = */ false);

        i32 cx = (primaryDisplay.resolution.x / 2) - (winX / 2);
        i32 cy = (primaryDisplay.resolution.y / 2) - (winY / 2);

        ChangePosition(cx, cy);
    }


    void GLFWWindow::SetIcon(const String& path) {
        Texture2D texture{ path };

        GLFWimage ico {
            .width = texture.GetWidth(),
            .height = texture.GetHeight(),
            .pixels = const_cast<u8*>(texture.GetData())
        };
        glfwSetWindowIcon(m_window, 1, &ico);
    }


    void GLFWWindow::SetTitle(const String& title) {
        glfwSetWindowTitle(m_window, title.c_str());
    }


    void GLFWWindow::SetInnerCursor(const String& path) {
        Texture2D texture{ path };

        GLFWimage cur {
            .width = texture.GetWidth(),
            .height = texture.GetHeight(),
            .pixels = const_cast<u8*>(texture.GetData())
        };

        m_cursor = glfwCreateCursor(&cur, 0, 0);
        glfwSetCursor(m_window, m_cursor);
    }


    void GLFWWindow::ResetInnerCursor() {
        glfwSetCursor(m_window, nullptr);
    }


    void GLFWWindow::PollEvents() {
        glfwPollEvents();
    }

    RUBY_NODISCARD EWindowVendor GLFWWindow::GetVendor() const {
        return EWindowVendor::VENDOR_GLFW;
    }

    void* GLFWWindow::GetNativeWindowPtr() const {
        return m_window;
    }


	bool GLFWWindow::Update() const {
        glfwSwapBuffers(m_window);

        return !glfwWindowShouldClose(m_window);
	}


    bool GLFWWindow::IsWindowClosed() const {
        return glfwWindowShouldClose(m_window) == GLFW_TRUE;
    }

    RUBY_NODISCARD SizeStruct GLFWWindow::GetWindowSizes() const {
        return GetSizes(/*framebufferSizes=*/ false);
    }

    RUBY_NODISCARD SizeStruct GLFWWindow::GetFramebufferSizes() const {
        return GetSizes(/*framebufferSizes=*/ true);
    }

    RUBY_NODISCARD typename SizeStruct::SizeType GLFWWindow::GetWidth() const {
        return GetWindowSizes().width;
    }

    RUBY_NODISCARD typename SizeStruct::SizeType GLFWWindow::GetFramebufferWidth() const {
        return GetFramebufferSizes().width;
    }

    RUBY_NODISCARD typename SizeStruct::SizeType GLFWWindow::GetHeight() const {
        return GetWindowSizes().height;
    }

    RUBY_NODISCARD typename SizeStruct::SizeType GLFWWindow::GetFramebufferHeight() const {
        return GetFramebufferSizes().height;
    }



	GLFWWindow::~GLFWWindow() {
        EventManager::Clear();
        
        glfwDestroyWindow(m_window); 
        glfwTerminate();

        if (m_cursor) {
            glfwDestroyCursor(m_cursor);
        }
	}


	void GLFWWindow::Init(VideoStruct vs) {
		RUBY_ASSERT(vs.width > 0 && vs.height > 0, "Width and/or height cannot be least or equal zero!");
		RUBY_DEBUG("GLFWWindow::Init() : width({}), height({}), isFullScreened({})",
					vs.width, vs.height, vs.isFullScreened);

        if (!glfwInit()) {
            RUBY_CRITICAL("GLFWWindow::Init() : Failed to initialize GLFW(!glfwInit())");
            return;
        }


        if (!vs.isResizable)
		    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWmonitor* monitor = (vs.isFullScreened) ? glfwGetPrimaryMonitor() : nullptr;
		m_window = glfwCreateWindow(vs.width, vs.height, vs.title.c_str(), monitor, nullptr);
		if (!m_window) {
			RUBY_CRITICAL("GLFWWindow::Init() : Failed to create a window(!m_window)");
			return;
		}

		glfwMakeContextCurrent(m_window);
	}

	void GLFWWindow::SetupCallbacks() {
		glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
                exciteEvent(KeyboardKeyPressed{ key, action });
            }
            else {
                exciteEvent(KeyboardKeyReleased{ key, action });
            }
        });


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
                exciteEvent(MousePressEvent{ button });
            }
			else {
                exciteEvent(MouseReleaseEvent{ button });
            }
		});


		glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos) {
            exciteEvent(MouseMoveEvent{ xpos, ypos });
        });


		glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos) {
            exciteEvent(MouseScrollEvent{ xpos, ypos });
        });
	}

    SizeStruct GLFWWindow::GetSizes(bool framebufferSizes) const {
        SizeStruct out;
        if (framebufferSizes) {
            glfwGetFramebufferSize(m_window, &out.width, &out.height);
        }
        else {
            glfwGetWindowSize(m_window, &out.width, &out.height);
        }

        return out;
    }
}