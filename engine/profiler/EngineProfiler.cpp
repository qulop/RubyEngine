#include "EngineProfiler.hpp"


namespace Ruby {
    constexpr bool EngineProfiler::IsEnabled() {
    #ifdef TRACY_ENABLE
        return true;
    #else
        return false;
    #endif
    }

    constexpr bool EngineProfiler::IsConnectedToServer() {
    #ifdef TRACY_ENABLE
        return tracy::GetProfiler().IsConnected();
    #else
        return false;
    #endif
    }
}
