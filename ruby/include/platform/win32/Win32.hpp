#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>


#undef interface    // Warning C4005 in MSVC: "interface" macro redefinition in "combaseapi.h"
#include <Windows.h>
#undef interface
#define interface struct

namespace Ruby::Win32
{
    std::pair<i32, i32> getScreenResolution() noexcept;
}
