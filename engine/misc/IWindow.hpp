#pragma once

#include "WindowProps.hpp"


namespace Ruby {
    enum class EWindowVendor {
        VENDOR_UNKNOWN,
        VENDOR_GLFW,
        VENDOR_WIN32
    };


    RUBY_INTERFACE IWindow {
    public:
        virtual void ChangePosition(i32 x, i32 y) const = 0;
        virtual void Resize(i32 width, i32 height) = 0;
        virtual void ToCenter() const = 0;
        virtual void SetIcon(const String& path) = 0;
        virtual void SetTitle(const String& title) = 0;
        virtual void SetInnerCursor(const String& path) = 0;
        virtual void ResetInnerCursor() = 0;
        virtual void PollEvents() = 0;

        RUBY_NODISCARD virtual EWindowVendor GetVendor() const = 0;
        RUBY_NODISCARD virtual void* GetNativeWindowPtr() const = 0;

        RUBY_NODISCARD virtual bool Update() const = 0;
        RUBY_NODISCARD virtual bool IsWindowClosed() const = 0;

        RUBY_NODISCARD virtual SizeStruct GetWindowSizes() const = 0;
        RUBY_NODISCARD virtual SizeStruct GetFramebufferSizes() const = 0;

        RUBY_NODISCARD virtual typename SizeStruct::SizeType GetWidth() const = 0;
        RUBY_NODISCARD virtual typename SizeStruct::SizeType GetFramebufferWidth() const = 0;

        RUBY_NODISCARD virtual typename SizeStruct::SizeType GetHeight() const = 0;
        RUBY_NODISCARD virtual typename SizeStruct::SizeType GetFramebufferHeight() const = 0;

        virtual ~IWindow() = default;

    public:
        static SharedPtr<IWindow> Create(VideoStruct vs);
    };
}