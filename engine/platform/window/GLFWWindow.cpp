#include "GLFWWindow.hpp"

#include <utility/Definitions.hpp>
#include <types/Logger.hpp>
#include <types/CString.hpp>
#include <events/EventManager.hpp>
#include <graphics/Texture2D.hpp>
#include <platform/Platform.hpp>
#include <utility/Assert.hpp>

#include "GLFW/glfw3native.h"


namespace Ruby {
    bool GLFWWindow::Init(StringView windowName, const Platform::DisplayInfo& display) {
	    RUBY_ASSERT(display.resolution.x && display.resolution.y, "Width and/or height cannot be least or equal zero!");

	    if (!Super::Init(windowName, display)) {
            return false;
        }

	    glfwSetErrorCallback([](int err, const char* desc) {
            RUBY_ERROR("glfwSetErrorCallback(): {} ... {}", err, desc);
        });


	    if (!glfwInit()) {
	        RUBY_CRITICAL("GLFWWindow::Init() : Failed to initialize the GLFW library");
	        return false;
	    }

	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	    // TODO: Replace it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ... !!!!
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	    GLFWmonitor* monitor = MapToGLFWmonitor(display);
        if (!monitor) {
            RUBY_ERROR("GLFWWindow::Init() : Failed to map our DisplayInfo(with name {}) to GLFWmonitor*", display.name);
            return false;
        }

	    m_window = glfwCreateWindow(display.resolution.x, display.resolution.y, windowName.data(), monitor, nullptr);
	    if (!m_window) {
	        RUBY_CRITICAL("GLFWWindow::Init() : Failed to create the main window");
	        return false;
	    }

	    glfwMakeContextCurrent(m_window);

	    glfwSetWindowUserPointer(m_window, this);
	    SetupCallbacks();

        return true;
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

    void GLFWWindow::SetVSyncEnable(bool val) {
       glfwSwapInterval(val ? 1 : 0);
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

    GLFWmonitor* GLFWWindow::MapToGLFWmonitor(const Platform::DisplayInfo& display) const {
        i32 count = 0;
	    GLFWmonitor** monitors = glfwGetMonitors(&count);
	    for (i32 i = 0; i < count; ++i) {
            i32 x = 0, y = 0;
	        glfwGetMonitorPos(monitors[i], &x, &y);

	        if (display.displayPosition.x == x && display.displayPosition.y == y) {
	            return monitors[i];
	        }
	    }

	    return nullptr;
	}

	void GLFWWindow::SetupCallbacks() {
		glfwSetKeyCallback(m_window, [](GLFWwindow*, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
                ExciteEvent(KeyboardKeyPressed{ key, action });
            }
            else {
                ExciteEvent(KeyboardKeyReleased{ key, action });
            }
        });


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow*, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
                ExciteEvent(MousePressEvent{ button });
            }
			else {
                ExciteEvent(MouseReleaseEvent{ button });
            }
		});


		glfwSetCursorPosCallback(m_window, [](GLFWwindow*, double xpos, double ypos) {
            ExciteEvent(MouseMoveEvent{ xpos, ypos });
        });


		glfwSetScrollCallback(m_window, [](GLFWwindow*, double xpos, double ypos) {
            ExciteEvent(MouseScrollEvent{ xpos, ypos });
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
