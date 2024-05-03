#pragma once

#if defined(RUBY_WIN32_USED)
    #include "win32/Win32.hpp"
#elif defined(RUBY_LINUX_USED)
    #include "linux/Linux.hpp"
#endif

#include <utility/RubyUtility.hpp>


namespace Ruby
{
    #if defined(RUBY_WIN32_USED)
        namespace Platform = Win32;
    #elif defined(RUBY_LINUX_USED)
        namespace Plaform = Linux;
    #endif

    RUBY_ENUM(RunningPlatform,
        PLATFORM_UNKNOWN,
        PLATFORM_WINDOWS,
        PLATFORM_LINUX
    );

    constexpr RunningPlatform getPlatform()
    {
    #if defined(RUBY_WIN32_USED)
        return PLATFORM_WINDOWS;
    #elif defined(RUBY_LINUX_USED)
        return PLATFORM_LINUX;
    #else
        return PLATFORM_UNKNOWN;
    #endif
    }
}