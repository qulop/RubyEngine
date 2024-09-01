#pragma once

#include <platform/api/PlatformAPI.hpp>

#undef interface    // Warning C4005 in MSVC: "interface" macro redefinition in "combaseapi.h"
#include <Windows.h>
#undef interface
#define interface struct

#include "audio/WaveOutAudioOutputStream.hpp"
