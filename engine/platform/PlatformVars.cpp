#include "PlatformVars.hpp"


namespace Kiwi::Globals::Platform {
    Sync::Mutex g_consoleIOMutex = Sync::Mutex();

    Vector<String> g_applicationArguments = Vector<String>();
}