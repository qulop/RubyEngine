#pragma once

#include <platform/win32/Win32.hpp>


namespace Ruby::Win32
{
    std::pair<i32, i32> getScreenResolution() noexcept
    {
        i32 width = GetSystemMetrics(SM_CXSCREEN);
        i32 height = GetSystemMetrics(SM_CYSCREEN);

        return std::make_pair(width, height);
    }

}
