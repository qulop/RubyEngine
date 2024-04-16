#pragma once

#include <core/WindowProps.hpp>
#include <core/IWindow.hpp>


namespace Ruby::WinAgents
{
	class GLWindow : public IWindow
	{
	public:
		explicit GLWindow(VideoStruct&& vs);

		RUBY_NODISCARD bool Update() const override;
		RUBY_NODISCARD SizeStruct GetSizes(bool isReal) const override;

		void PollEvents() override;

		~GLWindow() override;

    private:
		void Init(VideoStruct&& vs);

		void SetupCallbacks();

	private:
		GLFWwindow* m_window = nullptr;
	};
}