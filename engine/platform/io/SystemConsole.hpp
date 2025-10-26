#pragma once

#ifdef RUBY_WIN32_USED
    #include <win32/io/Win32SystemConsole.hpp>
#endif

#include <types/TypeTraits.hpp>


namespace Ruby::Platform {
#ifdef RUBY_WIN32_USED
    using SystemConsole = Win32::Win32SystemConsole;
#endif
}

namespace Ruby {
    using Console = Platform::SystemConsole;
}