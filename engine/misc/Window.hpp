#pragma once

#include <platform/Platform.hpp>
#include <math/Rect.hpp>


namespace Ruby {
    enum class EWindowVendor {
        UNKNOWN,
        GLFW,
        WIN32_NATIVE,
        X11
    };


    RUBY_ABSTRACT class AWindow {
    public:
        RUBY_NODISCARD static SharedPtr<AWindow> CreateWindowImpl();

    public:
        RUBY_NODISCARD virtual bool Init(StringView windowName, const Platform::DisplayInfo& display) { return true; }

        virtual void ChangePosition(i32 x, i32 y) const = 0;
        virtual void Resize(i32 width, i32 height) = 0;
        virtual void ToCenter() const;
        virtual void SetIcon(const String& path) = 0;
        virtual void SetTitle(const String& title) = 0;
        virtual void SetInnerCursor(const String& path) = 0;
        virtual void ResetInnerCursor() = 0;

        virtual void SwapBuffers() = 0;
        virtual void PollEvents() = 0;

        RUBY_NODISCARD virtual EWindowVendor GetVendor() const = 0;
        RUBY_NODISCARD virtual void* GetNativeWindowPtr() const = 0;

        virtual void MaximizeWindow(bool val) = 0;

        RUBY_NODISCARD virtual bool IsMaximized() const;

        RUBY_NODISCARD virtual bool Update();
        RUBY_NODISCARD virtual bool IsWindowClosed() const = 0;

        virtual void SetVSyncEnable(bool val) = 0;

        RUBY_NODISCARD virtual IRect GetWindowSizes() const = 0;
        RUBY_NODISCARD virtual IRect GetFramebufferSizes() const = 0;

        RUBY_NODISCARD virtual size_t GetWidth() const;
        RUBY_NODISCARD virtual size_t GetFramebufferWidth() const;

        RUBY_NODISCARD virtual size_t GetHeight() const;
        RUBY_NODISCARD virtual size_t GetFramebufferHeight() const;

        virtual ~AWindow() = default;

        protected:
            std::atomic<bool> m_isMaximized = false;
            std::atomic<bool> m_isResizable = false;
    };
}