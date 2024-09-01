#pragma once

#if defined(RUBY_WIN32_USED)
    #include "win32/Win32.hpp"
#elif defined(RUBY_LINUX_USED)
    #include "linux/Linux.hpp"
#endif


namespace Ruby {
    enum CurrentPlatform {
        PLATFORM_UNKNOWN,
        PLATFORM_WINDOWS,
        PLATFORM_LINUX
    };

    constexpr CurrentPlatform getPlatform() noexcept {
        #ifdef RUBY_WIN32_USED
            return PLATFORM_WINDOWS;
        #elif defined(RUBY_LINUX_USED)
            return PLATFORM_LINUX;
        #else
            return PLATFORM_UNKNOWN;
        #endif
    }

    template<typename... Args>
    void errorBoxF(const char* fmt, const char* title, Args&&... args) noexcept {
        auto&& msg = std::format(fmt, std::forward<Args>(args)...);

        Platform::errorBox(msg.c_str(), title);
    }
}