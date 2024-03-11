#pragma once

#include "WindowProps.hpp"


namespace Ruby::WinAgents
{
	class GLWindow
	{
	public:
		explicit GLWindow(VideoStruct&& vs);

		bool Update(void);

		SizeStruct GetSize(bool isReal=false);

		~GLWindow();

		static void PollEvents(void);

		static SizeStruct GetScreenResolution(void);

	private:
		void Init(VideoStruct&& vs);

		void SetupCallbacks(void);

	private:
		GLFWwindow* m_window = nullptr;
	};
}