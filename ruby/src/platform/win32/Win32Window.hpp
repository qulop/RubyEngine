#pragma once

#include <core/IWindow.hpp>


namespace Ruby::Win32 {
    class Win32Window : IWindow {
    public:
        Win32Window(VideoStruct vs); // NOLINT

        void ChangePosition(i32 x, i32 y) const override;
        void Resize(i32 width, i32 height) override;
        void ToCenter() const override;
        void SetIcon(const RubyString& path) override;
        void SetTitle(const RubyString& title) override;
        void PollEvents() override;

        RUBY_NODISCARD bool Update() const override;
        RUBY_NODISCARD bool IsWindowClosed() const override;

        RUBY_NODISCARD SizeStruct GetSizes(bool isReal) const override;

        ~Win32Window() override = default;
    };
}