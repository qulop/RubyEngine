#pragma once

#include <core/WindowProps.hpp>
#include <core/IWindow.hpp>


namespace Ruby
{
	class GLFWWindow : public IWindow
	{
	public:
		explicit GLFWWindow(VideoStruct vs);

        void ChangePosition(i32 x, i32 y) override;
        void Resize(i32 width, i32 height) override;
        void ToCenter() override;
        void SetIcon(const RubyString& path) override;
        void SetTitle(const RubyString& title) override;
		void PollEvents() override;

		RUBY_NODISCARD bool Update() const override;
        RUBY_NODISCARD bool IsWindowClosed() const override;

		RUBY_NODISCARD SizeStruct GetSizes(bool isReal) const override;

		~GLFWWindow() override;

    private:
		void Init(VideoStruct vs);

		void SetupCallbacks();

	private:
		GLFWwindow* m_window = nullptr;
	};
}