#include <platform/Platform.hpp>
#include <types/cast/Cast.hpp>
#include <types/Logger.hpp>


#ifdef RUBY_DEBUG_BUILD
    #define RUBY_HEAP_ALLOC_FLAGS HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY
#else
    #define RUBY_HEAP_ALLOC_FLAGS HEAP_ZERO_MEMORY
#endif



namespace Ruby::Platform {
    Vector<DisplayInfo> EnumerateDisplays() noexcept {
        Vector<DisplayInfo> result;

        auto&& callback = [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL {
            auto* res = BasicCast::UnsafeCast<Vector<DisplayInfo>*>(lParam);

            MONITORINFOEX info;
            info.cbSize = sizeof(info);
            if (!GetMonitorInfo(hMonitor, &info)) {
                RUBY_WARNING("EnumerateMonitors() : Failed to GetMonitorInfo()");
                return TRUE;
            }

            DisplayInfo props;
            props.nativeHandle = hMonitor;
            props.isPrimary = info.dwFlags & MONITORINFOF_PRIMARY;
            props.name = info.szDevice;

            DEVMODE dm;
            dm.dmSize = sizeof(dm);
            if (EnumDisplaySettings(props.name.c_str(), ENUM_CURRENT_SETTINGS, &dm)) {
                props.resolution = UVec2(dm.dmPelsWidth, dm.dmPelsHeight);
                props.refreshRate = dm.dmDisplayFrequency;
            }

            res->push_back(props);
            return TRUE;
        };


        EnumDisplayMonitors(NULL, NULL, callback, BasicCast::UnsafeCast<LPARAM>(&result));

        return result;
    }

    Opt<DisplayInfo> GetPrimaryDisplay() noexcept {
        Vector<DisplayInfo> monitors = EnumerateDisplays();

        auto it = std::ranges::find_if(monitors, [](DisplayInfo& m) {
            return m.isPrimary;;
        });

        return (it == monitors.end()) ? nullopt : Opt{ *it };
    }

    size_t GetDisplaysCount() noexcept {
        return EnumerateDisplays().size();
    }
}


namespace Ruby::Platform::Memory {
    void* NativeHeapAlloc(size_t sz) {
        HANDLE heap = GetProcessHeap();
        if (heap == BasicCast::UnsafeCast<HANDLE>(NULL)) {
            return nullptr;
        }

        return HeapAlloc(heap, RUBY_HEAP_ALLOC_FLAGS, sz);
    }
    
    void NativeHeapFree(void* addr, RUBY_MAYBE_UNUSED size_t sz) {
        HANDLE heap = GetProcessHeap();
        if (heap == BasicCast::UnsafeCast<HANDLE>(NULL)) {
            return;
        }

        HeapFree(heap, NULL, addr);
    }

    void* CreateMemoryMapping() {
        return nullptr;
    }
}

#undef RUBY_HEAP_ALLOC_FLAGS