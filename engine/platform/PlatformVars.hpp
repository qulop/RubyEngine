#pragma once

#include <sync/Mutex.hpp>


namespace Ruby::Globals::Platform {
    extern Sync::Mutex g_consoleIOMutex;

    // Note: Call Platform::GetApplicationArguments() instead of directly use this variable
    extern Vector<String> g_applicationArguments;
}