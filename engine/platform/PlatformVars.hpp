#pragma once

#include <sync/Mutex.hpp>


namespace Ruby::Globals::Platform {
    extern Sync::Mutex g_consoleIOMutex;
}