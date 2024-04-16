#pragma once

#include <utility/StdInc.hpp>
#include <utility/Definitions.hpp>
#include <Windows.h>


namespace Ruby::Win32
{
    std::pair<i32, i32> getScreenResolution() noexcept;
}
