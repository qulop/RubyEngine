#pragma once

#include "GLFWWindow.hpp"
#include <core/WindowProps.hpp>

namespace Ruby
{
#if defined(RUBY_OPENGL_USED)
	using Window = Ruby::WinAgents::GLFWWindow;
#endif
}