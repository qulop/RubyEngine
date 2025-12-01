#pragma once

#ifdef KIWI_WIN32_USED
    #include <win32/io/SystemConsoleWin32.hpp>
#endif

#include <types/TypeTraits.hpp>


namespace Kiwi::Platform {
#ifdef KIWI_WIN32_USED
    using SystemConsole = Win32::SystemConsoleWin32;
#endif
}

namespace Kiwi {
    using Console = Platform::SystemConsole;
}