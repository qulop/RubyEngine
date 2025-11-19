#pragma once

#include <misc/Window.hpp>


struct GLFWwindow;
struct GLFWcursor;
struct GLFWmonitor;


namespace Ruby {
	class GLFWWindow : public AWindow {
	public:
		using Super = AWindow;

	public:
		GLFWWindow() = default;

	public:
        RUBY_NODISCARD bool Init(StringView windowName, const Platform::DisplayInfo& display);


        void ChangePosition(i32 x, i32 y) const override;
        void Resize(i32 width, i32 height) override;
        void SetIcon(const String& path) override;
        void SetTitle(const String& title) override;
        void SetInnerCursor(const String& path) override;
        void ResetInnerCursor() override;
        void PollEvents() override;

        RUBY_NODISCARD EWindowVendor GetVendor() const override;
        RUBY_NODISCARD void* GetNativeWindowPtr() const override;

		void MaximizeWindow(bool val) override;

		RUBY_NODISCARD bool Update() const override;
        RUBY_NODISCARD bool IsWindowClosed() const override;

		void SetVSyncEnable(bool val) override;

        RUBY_NODISCARD IRect GetWindowSizes() const override;
        RUBY_NODISCARD IRect GetFramebufferSizes() const override;

		~GLFWWindow() override;

    private:
		RUBY_NODISCARD GLFWmonitor* MapToGLFWmonitor(const Platform::DisplayInfo& display) const;

		void SetupCallbacks();

	private:
        GLFWcursor* m_cursor = nullptr;
		GLFWwindow* m_window = nullptr;
	};
}