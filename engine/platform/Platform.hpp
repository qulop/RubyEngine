#pragma once

#include <utility/Definitions.hpp>
#include <math/vec/Vec2.hpp>
#include <sync/Mutex.hpp>


namespace Kiwi {
    enum class ECurrentPlatform {
        UNKNOWN,
        WINDOWS,
        LINUX
    };

    consteval ECurrentPlatform GetCurrentPlatform() noexcept {
        #if defined(KIWI_WIN32_USED)
            return ECurrentPlatform::WINDOWS;
        #elif defined(KIWI_LINUX_USED)
            return ECurrentPlatform::LINUX;
        #else
            return ECurrentPlatform::UNKNOWN;
        #endif
    }
}


namespace Kiwi::Platform {
    struct DisplayInfo {
        void* nativeHandle = nullptr;
        bool isPrimary = false;
        String name;    // A display(monitor) system name
        String model;   // TODO: Now this field is empty. Win32: via registry
        u16 refreshRate = 0;
        UVec2 resolution;
        UVec2 displayPosition;
    };

    KIWI_NODISCARD bool CreateDebugConsole() noexcept;
    KIWI_NODISCARD bool CreateConsole() noexcept;
    void DestroyConsole() noexcept;

    KIWI_NODISCARD Vector<DisplayInfo> EnumerateDisplays() noexcept;
    KIWI_NODISCARD Opt<DisplayInfo> GetPrimaryDisplay() noexcept;
    KIWI_NODISCARD size_t GetDisplaysCount() noexcept;
    KIWI_NODISCARD bool IsDisplayCurrentlyActive(const DisplayInfo& info) noexcept;
    KIWI_NODISCARD bool IsUnderDebug() noexcept;

    KIWI_NODISCARD Vector<String> GetApplicationArguments() noexcept;

    KIWI_NODISCARD Path GetApplicationPath() noexcept;
    KIWI_NODISCARD Path GetTemporaryDirectoryPath() noexcept;
}

namespace Kiwi::Platform::Memory {
    KIWI_NODISCARD void* NativeHeapAlloc(size_t sz);
    void NativeHeapFree(void* addr, size_t sz);

    KIWI_NODISCARD void* CreateMemoryMapping();
}