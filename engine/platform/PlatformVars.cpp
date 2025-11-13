#include "PlatformVars.hpp"


namespace Ruby::Globals::Platform {
    Sync::Mutex g_consoleIOMutex = Sync::Mutex();
}