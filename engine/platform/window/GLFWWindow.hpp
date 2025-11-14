#pragma once

#include <misc/WindowProps.hpp>
#include <misc/IWindow.hpp>


namespace Ruby {
	class GLFWWindow : public IWindow {
	public:
		using Super = IWindow;

	public:
		GLFWWindow() = default;

	public:
        RUBY_NODISCARD bool Init(StringView windowName, const Platform::DisplayInfo& display);


        void ChangePosition(i32 x, i32 y) const override;
        void Resize(i32 width, i32 height) override;
        void ToCenter() const override;
        void SetIcon(const String& path) override;
        void SetTitle(const String& title) override;
        void SetInnerCursor(const String& path) override;
        void ResetInnerCursor() override;
        void PollEvents() override;

        RUBY_NODISCARD EWindowVendor GetVendor() const override;
        RUBY_NODISCARD void* GetNativeWindowPtr() const override;

		RUBY_NODISCARD bool Update() const override;
        RUBY_NODISCARD bool IsWindowClosed() const override;

		void SetVSyncEnable(bool val) override;

        RUBY_NODISCARD SizeStruct GetWindowSizes() const override;
        RUBY_NODISCARD SizeStruct GetFramebufferSizes() const override;

        RUBY_NODISCARD typename SizeStruct::SizeType GetWidth() const override;
        RUBY_NODISCARD typename SizeStruct::SizeType GetFramebufferWidth() const override;

        RUBY_NODISCARD typename SizeStruct::SizeType GetHeight() const override;
        RUBY_NODISCARD typename SizeStruct::SizeType GetFramebufferHeight() const override;

		~GLFWWindow() override;

    private:
		RUBY_NODISCARD GLFWmonitor* MapToGLFWmonitor(const Platform::DisplayInfo& display) const;

		void SetupCallbacks();

        RUBY_NODISCARD SizeStruct GetSizes(bool framebufferSizes) const;

	private:
        GLFWcursor* m_cursor = nullptr;
		GLFWwindow* m_window = nullptr;
	};
}