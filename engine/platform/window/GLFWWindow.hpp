#pragma once

#include <misc/Window.hpp>


struct GLFWwindow;
struct GLFWcursor;
struct GLFWmonitor;


namespace Kiwi {
	class GLFWWindow : public AWindow {
		KIWI_CREATE_OBJECT(GLFWWindow);

	public:
		using Super = AWindow;

	public:
		GLFWWindow() = default;

	public:
        KIWI_NODISCARD bool Init(StringView windowName, const Platform::DisplayInfo& display) override;


        void ChangePosition(i32 x, i32 y) const override;
        void Resize(i32 width, i32 height) override;
        void SetIcon(const String& path) override;
        void SetTitle(const String& title) override;
        void SetInnerCursor(const String& path) override;
        void ResetInnerCursor() override;

        void SwapBuffers() override;
        void PollEvents() override;

        KIWI_NODISCARD EWindowVendor GetVendor() const override;
        KIWI_NODISCARD void* GetNativeWindowPtr() const override;

		void MaximizeWindow(bool val) override;

		KIWI_NODISCARD bool Update() override;
        KIWI_NODISCARD bool IsWindowClosed() const override;

		void SetVSyncEnable(bool val) override;

        KIWI_NODISCARD IRect GetWindowSizes() const override;
        KIWI_NODISCARD IRect GetFramebufferSizes() const override;

		~GLFWWindow() override;

    private:
		KIWI_NODISCARD GLFWmonitor* MapToGLFWmonitor(const Platform::DisplayInfo& display) const;

		void SetupCallbacks();

	private:
        GLFWcursor* m_cursor = nullptr;
		GLFWwindow* m_window = nullptr;
	};
}