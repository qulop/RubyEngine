#include "Win32Window.hpp"


namespace Ruby::Win32 {
    Win32Window::Win32Window(VideoStruct vs) {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::ChangePosition(i32 x, i32 y) const {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::Resize(i32 width, i32 height) {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::ToCenter() const {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::SetIcon(const RubyString& path) {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::SetTitle(const RubyString& title) {
        RUBY_NOT_IMPLEMENTED;
	}

    void Win32Window::PollEvents() {
        RUBY_NOT_IMPLEMENTED;
	}

    RUBY_NODISCARD bool Win32Window::Update() const {
        RUBY_NOT_IMPLEMENTED;
	}
    RUBY_NODISCARD bool Win32Window::IsWindowClosed() const {
        RUBY_NOT_IMPLEMENTED;
	}

    RUBY_NODISCARD SizeStruct Win32Window::GetSizes(bool isReal) const {
        RUBY_NOT_IMPLEMENTED;
	}
}