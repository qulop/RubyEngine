#include <platform/Platform.hpp>
#include <platform/PlatformVars.hpp>

#include <common/cast/Cast.hpp>
#include <common/types/String.hpp>

#include <math/vec/Vec.hpp>

#include <shellapi.h>
#include <cstdio>


#ifdef KIWI_DEBUG_BUILD
    #define KIWI_HEAP_ALLOC_FLAGS HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY
#else
    #define KIWI_HEAP_ALLOC_FLAGS HEAP_ZERO_MEMORY
#endif



namespace Kiwi::Platform {
    bool CreateDebugConsole() noexcept {
        return (AttachConsole(ATTACH_PARENT_PROCESS) == TRUE) || CreateConsole();
    }

    bool CreateConsole() noexcept {
        if (AllocConsole() == FALSE) {
            return false;
        }

        // Redirect the STD strems to the new console
        FILE* cOut;
        freopen_s(&cOut, "CONOUT$", "w", stdout);

        FILE* cErr;
        freopen_s(&cErr, "CONOUT$", "w", stderr);

        return true;
    }

    void DestroyConsole() noexcept {
        FreeConsole();
    }

    Vector<DisplayInfo> EnumerateDisplays() noexcept {
        Vector<DisplayInfo> result;

        auto&& callback = [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL {
            auto* res = BasicCast::UnsafeCast<Vector<DisplayInfo>*>(lParam);

            MONITORINFOEX info;
            info.cbSize = sizeof(info);
            if (!GetMonitorInfo(hMonitor, &info)) {
                return TRUE;
            }

            DisplayInfo props;
            props.nativeHandle = hMonitor;
            props.isPrimary = info.dwFlags & MONITORINFOF_PRIMARY;
            props.name = info.szDevice;
            props.displayPosition = U32Vec2(info.rcMonitor.left, info.rcMonitor.top);

            DEVMODE dm;
            dm.dmSize = sizeof(dm);
            if (EnumDisplaySettings(props.name.ToCString(), ENUM_CURRENT_SETTINGS, &dm)) {
                props.resolution = U32Vec2(dm.dmPelsWidth, dm.dmPelsHeight);
                props.refreshRate = dm.dmDisplayFrequency;
            }

            res->push_back(props);
            return TRUE;
        };


        EnumDisplayMonitors(nullptr, nullptr, callback, BasicCast::UnsafeCast<LPARAM>(&result));

        return result;
    }

    Opt<DisplayInfo> GetPrimaryDisplay() noexcept {
        Vector<DisplayInfo> monitors = EnumerateDisplays();

        auto it = std::ranges::find_if(monitors, [](DisplayInfo& m) {
            return m.isPrimary;
        });

        return (it == monitors.end()) ? nullopt : Opt{ *it };
    }

    size_t GetDisplaysCount() noexcept {
        return EnumerateDisplays().size();
    }

    bool IsDisplayCurrentlyActive(const DisplayInfo& info) noexcept {
        HWND hForegroundWindow = GetForegroundWindow();
        if (!hForegroundWindow) {
            return false;
        }

        HMONITOR hCurrentMonitor = MonitorFromWindow(hForegroundWindow, MONITOR_DEFAULTTONEAREST);
        if (!hCurrentMonitor) {
            return false;
        }

        HMONITOR hReceivedMonitor = BasicCast::UnsafeCast<HMONITOR>(info.nativeHandle);

        return hCurrentMonitor == hReceivedMonitor;
    }

    bool IsUnderDebug() noexcept {
        return IsDebuggerPresent();
    }

    Vector<String> GetApplicationArguments() noexcept {
        if (!Globals::Platform::g_applicationArguments.empty()) {
            return Globals::Platform::g_applicationArguments;
        }

        i32 argc = 0;
        LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

        // Skip the executable path - we can obtain it by GetApplicationPath()
        for (i32 i = 1; i < argc; i++) {
            String arg = String::FromWideCharPtr(argv[i]);
            Globals::Platform::g_applicationArguments.emplace_back(std::move(arg));
        }

        return Globals::Platform::g_applicationArguments;
    }

    Path GetApplicationPath() noexcept {
        TCHAR* path = nullptr;
        GetModuleFileName(nullptr, path, MAX_PATH);
        KIWI_ASSERT(GetLastError() != ERROR_INSUFFICIENT_BUFFER, "Failed to get application path buffer: ERROR_INSUFFICIENT_BUFFER");

        return Path{ path };
    }

    Path GetTemporaryDirectoryPath() noexcept {
        wchar_t path[MAX_PATH];
        GetTempPathW(MAX_PATH, path);

        return Path{ path };
    }

    void Breakpoint() {
        DebugBreak();
    }

    void CriticalShutdown() {
        TerminateProcess(GetCurrentProcess(), KIWI_EXIT_FAILURE);
    }
}


namespace Kiwi::Platform::Memory {
    void* NativeHeapAlloc(size_t sz) {
        HANDLE heap = GetProcessHeap();
        if (heap == BasicCast::UnsafeCast<HANDLE>(NULL)) {
            return nullptr;
        }

        return HeapAlloc(heap, KIWI_HEAP_ALLOC_FLAGS, sz);
    }
    
    void NativeHeapFree(void* addr, KIWI_MAYBE_UNUSED size_t sz) {
        HANDLE heap = GetProcessHeap();
        if (heap == BasicCast::UnsafeCast<HANDLE>(NULL)) {
            return;
        }

        HeapFree(heap, 0, addr);
    }

    void* CreateMemoryMapping() {
        return nullptr;
    }
}

#undef KIWI_HEAP_ALLOC_FLAGS