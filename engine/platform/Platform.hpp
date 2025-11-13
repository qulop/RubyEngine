#pragma once

#include <utility/Definitions.hpp>
#include <math/vec/Vec2.hpp>
#include <sync/Mutex.hpp>


namespace Ruby {
    enum class ECurrentPlatform {
        PLATFORM_UNKNOWN,
        PLATFORM_WINDOWS,
        PLATFORM_LINUX
    };

    consteval ECurrentPlatform GetCurrentPlatform() noexcept {
        #if defined(RUBY_WIN32_USED)
            return ECurrentPlatform::PLATFORM_WINDOWS;
        #elif defined(RUBY_LINUX_USED)
            return ECurrentPlatform::PLATFORM_LINUX;
        #else
            return ECurrentPlatform::PLATFORM_UNKNOWN;
        #endif
    }
}

namespace Ruby::Platform::Globals {
    extern Sync::Mutex g_writeConsoleMutex;
}


namespace Ruby::Platform {
    struct DisplayInfo {
        void* nativeHandle = nullptr;
        bool isPrimary = false;
        String name;    // A display(monitor) system name
        String model;   // TODO: Now this field is empty. Win32: via registry
        u16 refreshRate = 0;
        UVec2 resolution;
    };

    RUBY_NODISCARD Vector<DisplayInfo> EnumerateDisplays() noexcept;
    RUBY_NODISCARD Opt<DisplayInfo> GetPrimaryDisplay() noexcept;
    RUBY_NODISCARD size_t GetDisplaysCount() noexcept;
}

namespace Ruby::Platform::Memory {
    RUBY_NODISCARD void* NativeHeapAlloc(size_t sz);
    void NativeHeapFree(void* addr, size_t sz);

    RUBY_NODISCARD void* CreateMemoryMapping();
}