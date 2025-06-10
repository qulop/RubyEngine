// Use content of this header only for implementing API for win32
// Include this header only in platform/win32/api_impl module and nowhere else

#pragma once

#include <types/StdInc.hpp>

#include <Windows.h>

namespace Ruby::Platform::Win32 {
    struct LastErrorStruct {
        DWORD code = ERROR_SUCCESS;
        std::string_view strCode;
        std::string_view description;
    };

    LastErrorStruct getLastError();
    HANDLE getStdHandle(DWORD stdHnd, bool abortOnError=false);
}

