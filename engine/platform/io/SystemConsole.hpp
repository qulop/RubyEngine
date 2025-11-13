#pragma once

#ifdef RUBY_WIN32_USED
    #include <win32/io/SystemConsoleWin32.hpp>
#endif

#include <types/TypeTraits.hpp>


namespace Ruby::Platform {
#ifdef RUBY_WIN32_USED
    using SystemConsole = Win32::SystemConsoleWin32;
#endif
}

namespace Ruby {
    using Console = Platform::SystemConsole;
}