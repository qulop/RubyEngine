#pragma once

#include "general_api/IO.hpp"
#include "general_api/Locale.hpp"
#include "general_api/Memory.hpp"
#include "general_api/Screen.hpp"


namespace Ruby {
    enum CurrentPlatform {
        PLATFORM_UNKNOWN,
        PLATFORM_WINDOWS,
        PLATFORM_LINUX
    };

    enum WindowVendor {
        VENDOR_UNKNOWN,
        VENDOR_GLFW,
        VENDOR_WIN32
    };

    consteval CurrentPlatform getPlatform() noexcept {
        #if defined(RUBY_WIN32_USED)
            return PLATFORM_WINDOWS;
        #elif defined(RUBY_LINUX_USED)
            return PLATFORM_LINUX;
        #else
            return PLATFORM_UNKNOWN;
        #endif
    }

    template<typename... Args>
    void errorBoxF(std::format_string<Args...> fmt, std::string_view title, Args&&... args) noexcept {
        auto&& msg = std::format(std::move(fmt), std::forward<Args>(args)...);

        Platform::errorBox(msg, title);
    }

    template<typename... Args>
    void writeInConsoleF(std::format_string<Args...> fmt, Args&&... args) {
        String msg = std::format(std::move(fmt), std::forward<Args>(args)...);

        Platform::writeInConsole(msg);
    }
}