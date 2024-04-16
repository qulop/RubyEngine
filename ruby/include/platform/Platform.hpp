#pragma once

#if defined(RUBY_WIN32_USED)
    #include "win32/Win32.hpp"
#elif defined(RUBY_LINUX_USED)
    #include "linux/Linux.hpp"
#endif


namespace Ruby
{
#if defined(RUBY_WIN32_USED)
    namespace Platform = Win32;
#elif defined(RUBY_LINUX_USED)
    namespace Plaform = Linux;
#endif
}