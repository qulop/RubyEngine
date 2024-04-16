#pragma once

#include "GlWindow.hpp"
#include <core/WindowProps.hpp>

namespace Ruby
{
#if defined(RUBY_OPENGL_USED)
	using Window = Ruby::WinAgents::GLWindow;
#endif
}