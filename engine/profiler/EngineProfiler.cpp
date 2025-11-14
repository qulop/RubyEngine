#include "EngineProfiler.hpp"


namespace Ruby {
    bool EngineProfiler::IsConnectedToServer() {
    #ifdef TRACY_ENABLE
        return tracy::GetProfiler().IsConnected();
    #else
        return false;
    #endif
    }
}
