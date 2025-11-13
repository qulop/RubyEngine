#include "PlatformVars.hpp"


namespace Ruby::Globals::Platform {
    Sync::Mutex g_consoleIOMutex = Sync::Mutex();

    Vector<String> g_applicationArguments = Vector<String>();
}