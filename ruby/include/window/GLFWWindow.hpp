#pragma once

#include <core/WindowProps.hpp>
#include <core/IWindow.hpp>


namespace Ruby::WinAgents
{
	class GLFWWindow : public IWindow
	{
	public:
		explicit GLFWWindow(const VideoStruct& vs);

        void ChangePosition(i32 x, i32 y) override;
        void Resize(u32 x, u32 y) override;
        void ToCenter() override;
        void SetIcon(const RubyString& path) override;
        void SetTitle(const RubyString& title) override;
		void PollEvents() override;

		RUBY_NODISCARD bool Update() const override;

		RUBY_NODISCARD SizeStruct GetSizes(bool isReal) const override;

		~GLFWWindow() override;

    private:
		void Init(const VideoStruct& vs);

		void SetupCallbacks();

	private:
		GLFWwindow* m_window = nullptr;
	};
}