#include "GLFWWindow.hpp"

#include <utility/Definitions.hpp>
#include <common/CString.hpp>
#include <events/EventManager.hpp>
#include <graphics/Texture2D.hpp>
#include <platform/Platform.hpp>
#include <utility/Assert.hpp>

#ifdef KIWI_WIN32_USED
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Kiwi {
    bool GLFWWindow::Init(StringView windowName, const Platform::DisplayInfo& display) {
	    KIWI_ASSERT(display.resolution.x && display.resolution.y, "Width and/or height cannot be least or equal zero!");

	    if (!Super::Init(windowName, display)) {
            return false;
        }

	    if (!glfwInit()) {
	        KIWI_CTX_LOG(CRITICAL, "Failed to initialize the GLFW library");
	        return false;
	    }

        // TODO: resizability should be configurable from the command line
	    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	    GLFWmonitor* monitor = MapToGLFWmonitor(display);
        if (!monitor) {
            KIWI_CTX_LOG(ERROR, "Failed to map our DisplayInfo(with name {}) to GLFWmonitor*", display.name);
            return false;
        }

        i32 monitorX = 0, monitorY = 0;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);

	    m_window = glfwCreateWindow(display.resolution.x, display.resolution.y, windowName.data(), nullptr, nullptr);
	    if (!m_window) {
	        KIWI_CTX_LOG(CRITICAL, "Failed to create the main window");
	        return false;
	    }

        glfwSetWindowPos(m_window, monitorX, monitorY);

	    glfwSetWindowUserPointer(m_window, this);
	    SetupCallbacks();

        return true;
    }

    void GLFWWindow::ChangePosition(i32 x, i32 y) const {
        glfwSetWindowPos(m_window, x, y);
    }

    void GLFWWindow::Resize(i32 width, i32 height) {
        KIWI_ASSERT_BASIC(width > 0 && height > 0);
        KIWI_ASSERT(false, "Implement this");
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

    void GLFWWindow::SwapBuffers() {
        glfwSwapBuffers(m_window);
    }

    void GLFWWindow::PollEvents() {
        glfwPollEvents();
    }

    Vector<const char*> GLFWWindow::GetVulkanExtensions() const {
        u32 extCount = 0;
        const char** extensions = glfwGetRequiredInstanceExtensions(&extCount);

        Vector<const char*> res(extensions, extensions + extCount);
        return res;
    }

    KIWI_NODISCARD EWindowVendor GLFWWindow::GetVendor() const {
        return EWindowVendor::GLFW;
    }

    void* GLFWWindow::GetNativeWindowPtr() const {
        return m_window;
    }

    Platform::NativeWindowHandle GLFWWindow::GetNativeWindowHandle() const {
        if constexpr (GetCurrentPlatform() == ECurrentPlatform::WINDOWS) {
            return {
                .handle = glfwGetWin32Window(m_window)
            };
        }
        else {
            std::unreachable();
        }
    }

    void GLFWWindow::MaximizeWindow(bool val) {
        m_isMaximized.store(val);
        if (m_isMaximized) {
            glfwMaximizeWindow(m_window);
        }
        else {
            glfwRestoreWindow(m_window);
        }
    }

    bool GLFWWindow::Update() {
        return Super::Update();
	}

    bool GLFWWindow::IsWindowClosed() const {
        return glfwWindowShouldClose(m_window) == GLFW_TRUE;
    }

    void GLFWWindow::SetVSyncEnable(bool val) {
       glfwSwapInterval(val ? 1 : 0);
    }

    KIWI_NODISCARD I32Rect GLFWWindow::GetWindowSizes() const {
        i32 width = 0, height = 0;
        glfwGetWindowSize(m_window, &width, &height);

        return I32Rect(0, 0, width, height);
    }

    KIWI_NODISCARD U32Rect GLFWWindow::GetFramebufferSizes() const {
        i32 width = 0, height = 0;
        glfwGetFramebufferSize(m_window, &width, &height);

        return U32Rect(0u, 0u, width, height);
    }

	GLFWWindow::~GLFWWindow() {
        GetSubsystem<EventSubsystem>()->DeInit();

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
        // TODO
        // glfwSetErrorCallback([](int err, const char* desc) {
        //     KIWI_CTX_LOG(ERROR, "The error code: {}, description: {}", err, desc);
        // });

		glfwSetKeyCallback(m_window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
            auto* window = (GLFWWindow*)glfwGetWindowUserPointer(glfwWindow);
            auto eventSubsystem = window->GetSubsystem<EventSubsystem>();

			if (action == GLFW_PRESS) {
                eventSubsystem->Excite(KeyboardKeyPressed{ key, action });
            }
            else {
                eventSubsystem->Excite(KeyboardKeyReleased{ key, action });
            }
        });


		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* glfwWindow, int button, int action, int mods) {
		    auto* window = (GLFWWindow*)glfwGetWindowUserPointer(glfwWindow);
            auto eventSubsystem = window->GetSubsystem<EventSubsystem>();

			if (action == GLFW_PRESS) {
                eventSubsystem->Excite(MousePressEvent{ button });
            }
			else {
                eventSubsystem->Excite(MouseReleaseEvent{ button });
            }
		});


		glfwSetCursorPosCallback(m_window, [](GLFWwindow* glfwWindow, double xpos, double ypos) {
            auto eventSubsystem = ((GLFWWindow*)glfwGetWindowUserPointer(glfwWindow))->GetSubsystem<EventSubsystem>();

            eventSubsystem->Excite(MouseMoveEvent{ xpos, ypos });
        });


		glfwSetScrollCallback(m_window, [](GLFWwindow* glfwWindow, double xpos, double ypos) {
		    auto eventSubsystem = ((GLFWWindow*)glfwGetWindowUserPointer(glfwWindow))->GetSubsystem<EventSubsystem>();

            eventSubsystem->Excite(MouseScrollEvent{ xpos, ypos });
        });
	}
}
