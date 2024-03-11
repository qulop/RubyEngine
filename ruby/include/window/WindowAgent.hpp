#pragma once

#include "GlWindow.hpp"
#include "WindowProps.hpp"

namespace Ruby
{

#if defined(RUBY_GLFW_BUILD)
	using WindowAgent = Ruby::WinAgents::GLWindow;
#endif
}