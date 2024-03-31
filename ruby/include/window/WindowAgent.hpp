#pragma once

#include "GlWindow.hpp"
#include "WindowProps.hpp"

namespace Ruby
{
#if defined(RUBY_OPENGL)
	using WindowAgent = Ruby::WinAgents::GLWindow;
#endif
}